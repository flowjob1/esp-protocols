#include "a7670e_urc_handler.hpp"
#include "a7670e_parse_utils.hpp"

using namespace a7670e;

namespace {

std::string_view payload_after_prefix(std::string_view line, std::string_view prefix)
{
    if (!detail::starts_with(line, prefix)) {
        return {};
    }
    return detail::trim_ascii(line.substr(prefix.size()));
}

bool parse_http_action(std::string_view line, HttpActionResult &result)
{
    const auto fields = detail::split_csv(line);
    if (fields.size() < 3) {
        return false;
    }

    int method = 0;
    int status = 0;
    int length = 0;
    if (!detail::parse_integer(fields[0], method) ||
            !detail::parse_integer(fields[1], status) ||
            !detail::parse_integer(fields[2], length)) {
        return false;
    }

    result.method = static_cast<HttpMethod>(method);
    result.status_code = status;
    result.data_len = length;
    return true;
}

} // namespace

void A7670eUrcHandler::handle(uint8_t *data, size_t len)
{
    if (!data || len == 0) {
        return;
    }
    handle_buffer(std::string_view(reinterpret_cast<char *>(data), len), false);
}

size_t A7670eUrcHandler::handle_buffer(std::string_view buffer, bool command_active)
{
    size_t consumed = 0;

    while (consumed < buffer.size()) {
        const auto remaining = buffer.substr(consumed);
        const auto line_end = remaining.find('\n');
        if (line_end == std::string_view::npos) {
            break;
        }

        const auto raw_size = line_end + 1;
        const auto line = detail::trim_ascii(remaining.substr(0, raw_size));
        if (line.empty()) {
            consumed += raw_size;
            continue;
        }

        if (command_active && !is_async_only_urc(line)) {
            break;
        }

        if (!handle_line(line)) {
            break;
        }

        consumed += raw_size;
    }

    return consumed;
}

bool A7670eUrcHandler::is_async_only_urc(std::string_view line) const
{
    return detail::starts_with(line, "+CMQTTRECV:") ||
           detail::starts_with(line, "+CMQTTCONNLOST:") ||
           detail::starts_with(line, "+CMQTTNONET") ||
           detail::starts_with(line, "+CGNSSPWR: READY!") ||
           detail::starts_with(line, "+CGNSSINFO:") ||
           detail::starts_with(line, "+HTTP_PEER_CLOSED") ||
           detail::starts_with(line, "+HTTP_NONET_EVENT") ||
           detail::starts_with(line, "+CGEV:") ||
           detail::starts_with(line, "+NETOPEN:");
}

bool A7670eUrcHandler::handle_line(std::string_view line)
{
    if (detail::starts_with(line, "+CMQTTRECV:")) {
        if (on_mqtt_message) {
            const auto fields = detail::split_csv(payload_after_prefix(line, "+CMQTTRECV:"));
            if (fields.size() >= 3) {
                MqttMessage msg{};
                if (detail::parse_integer(fields[0], msg.client_index) &&
                        detail::parse_integer(fields[2], msg.qos)) {
                    msg.topic = detail::unquote(fields[1]);
                    if (fields.size() >= 4) {
                        msg.payload = detail::unquote(fields[3]);
                    }
                    on_mqtt_message(msg);
                }
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+CMQTTSTART:")) {
        if (on_mqtt_start) {
            int err = 0;
            const auto fields = detail::split_csv(payload_after_prefix(line, "+CMQTTSTART:"));
            if (!fields.empty() && detail::parse_integer(fields[0], err)) {
                on_mqtt_start(err);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+CMQTTSTOP:")) {
        return true;
    }

    if (detail::starts_with(line, "+CMQTTCONNECT:")) {
        if (on_mqtt_connect) {
            const auto fields = detail::split_csv(payload_after_prefix(line, "+CMQTTCONNECT:"));
            int idx = 0;
            int err = 0;
            if (fields.size() >= 2 &&
                    detail::parse_integer(fields[0], idx) &&
                    detail::parse_integer(fields[1], err)) {
                on_mqtt_connect(idx, err);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+CMQTTDISC:")) {
        if (on_mqtt_disconnect) {
            const auto fields = detail::split_csv(payload_after_prefix(line, "+CMQTTDISC:"));
            int idx = 0;
            int err = 0;
            if (fields.size() >= 2 &&
                    detail::parse_integer(fields[0], idx) &&
                    detail::parse_integer(fields[1], err)) {
                on_mqtt_disconnect(idx, err);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+CMQTTCONNLOST:")) {
        if (on_mqtt_conn_lost) {
            const auto fields = detail::split_csv(payload_after_prefix(line, "+CMQTTCONNLOST:"));
            int idx = 0;
            int cause = 0;
            if (fields.size() >= 2 &&
                    detail::parse_integer(fields[0], idx) &&
                    detail::parse_integer(fields[1], cause)) {
                on_mqtt_conn_lost(idx, cause);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+CMQTTNONET")) {
        if (on_mqtt_conn_lost) {
            on_mqtt_conn_lost(-1, 3);
        }
        return true;
    }

    if (detail::starts_with(line, "+CGNSSPWR: READY!")) {
        if (on_gnss_ready) {
            on_gnss_ready();
        }
        return true;
    }

    if (detail::starts_with(line, "+CGNSSINFO:")) {
        if (on_gnss_info) {
            on_gnss_info(parse_gnss_info(std::string(line)));
        }
        return true;
    }

    if (detail::starts_with(line, "+HTTPACTION:")) {
        if (on_http_action) {
            HttpActionResult result{};
            if (parse_http_action(payload_after_prefix(line, "+HTTPACTION:"), result)) {
                on_http_action(result);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+HTTPPOSTFILE:")) {
        if (on_http_action) {
            HttpActionResult result{};
            if (parse_http_action(payload_after_prefix(line, "+HTTPPOSTFILE:"), result)) {
                on_http_action(result);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+HTTPREADFILE:")) {
        if (on_http_read_file) {
            int errcode = 0;
            const auto fields = detail::split_csv(payload_after_prefix(line, "+HTTPREADFILE:"));
            if (!fields.empty() && detail::parse_integer(fields[0], errcode)) {
                on_http_read_file(errcode);
            }
        }
        return true;
    }

    if (detail::starts_with(line, "+HTTP_PEER_CLOSED") ||
            detail::starts_with(line, "+HTTP_NONET_EVENT") ||
            detail::starts_with(line, "+CGEV:") ||
            detail::starts_with(line, "+NETOPEN:")) {
        return true;
    }

    return false;
}

GnssPosition A7670eUrcHandler::parse_gnss_info(const std::string &payload)
{
    GnssPosition pos{};
    const auto fields = detail::split_csv(payload_after_prefix(payload, "+CGNSSINFO:"));
    if (fields.empty() || detail::trim_ascii(fields[0]).empty()) {
        return pos;
    }

    int mode = 0;
    if (!detail::parse_integer(fields[0], mode)) {
        return pos;
    }
    pos.mode = mode;

    auto parse_int_field = [&](size_t index, int &value) {
        if (index < fields.size()) {
            detail::parse_integer(fields[index], value);
        }
    };
    auto parse_double_field = [&](size_t index, double &value) {
        if (index < fields.size()) {
            detail::parse_double(fields[index], value);
        }
    };

    parse_int_field(1, pos.gps_svs);
    parse_int_field(2, pos.beidou_svs);
    parse_int_field(3, pos.glonass_svs);
    parse_int_field(4, pos.galileo_svs);
    parse_double_field(5, pos.lat);
    parse_double_field(7, pos.lon);
    parse_double_field(11, pos.alt_m);
    parse_double_field(12, pos.speed_knots);
    parse_double_field(13, pos.course_deg);
    parse_double_field(14, pos.pdop);
    parse_double_field(15, pos.hdop);
    parse_double_field(16, pos.vdop);
    parse_int_field(17, pos.num_sv);

    if (fields.size() > 6 && !detail::trim_ascii(fields[6]).empty()) {
        const auto ns = detail::unquote(fields[6]);
        if (!ns.empty()) {
            pos.ns = ns.front();
        }
    }
    if (fields.size() > 8 && !detail::trim_ascii(fields[8]).empty()) {
        const auto ew = detail::unquote(fields[8]);
        if (!ew.empty()) {
            pos.ew = ew.front();
        }
    }
    if (fields.size() > 9) {
        pos.date = detail::unquote(fields[9]);
    }
    if (fields.size() > 10) {
        pos.utc = detail::unquote(fields[10]);
    }

    pos.valid = fields.size() > 8 &&
                !detail::trim_ascii(fields[5]).empty() &&
                !detail::trim_ascii(fields[6]).empty() &&
                !detail::trim_ascii(fields[7]).empty() &&
                !detail::trim_ascii(fields[8]).empty();
    return pos;
}
