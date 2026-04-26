#include "a7670e_module.hpp"
#include "a7670e_parse_utils.hpp"

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

namespace {

CR ok_or_error(std::string_view response)
{
    if (response.find("OK") != std::string_view::npos) {
        return CR::OK;
    }
    if (response.find("ERROR") != std::string_view::npos) {
        return CR::FAIL;
    }
    return CR::TIMEOUT;
}

bool parse_http_action_line(std::string_view line, HttpActionResult &result)
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

bool parse_http_errcode(std::string_view line, int &errcode)
{
    const auto fields = detail::split_csv(line);
    return !fields.empty() && detail::parse_integer(fields[0], errcode);
}

bool parse_http_init_term(std::string_view response, std::string_view prefix, int expected_cid, int &errcode)
{
    const auto line = detail::find_line(response, prefix);
    if (line.empty()) {
        return false;
    }

    const auto fields = detail::split_csv(line.substr(prefix.size()));
    if (fields.size() < 2) {
        return false;
    }

    int cid = -1;
    return detail::parse_integer(fields[0], errcode) &&
           detail::parse_integer(fields[1], cid) &&
           cid == expected_cid;
}

} // namespace

CR A7670E::http_init(int cid)
{
    const std::string cmd = cid >= 0 ? "AT+HTTPINIT=" + std::to_string(cid) + "\r" : "AT+HTTPINIT\r";

    return dte->command(cmd, [cid](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (cid >= 0) {
            int errcode = -1;
            if (parse_http_init_term(response, "+HTTPINIT:", cid, errcode)) {
                return errcode == 0 ? CR::OK : CR::FAIL;
            }
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        if (cid < 0 && response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_term(int cid)
{
    const std::string cmd = cid >= 0 ? "AT+HTTPTERM=" + std::to_string(cid) + "\r" : "AT+HTTPTERM\r";

    return dte->command(cmd, [cid](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (cid >= 0) {
            int errcode = -1;
            if (parse_http_init_term(response, "+HTTPTERM:", cid, errcode)) {
                return errcode == 0 ? CR::OK : CR::FAIL;
            }
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        if (cid < 0 && response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_set_url(const std::string &url)
{
    return dte->command("AT+HTTPPARA=\"URL\",\"" + url + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_connect_timeout(int sec)
{
    return dte->command("AT+HTTPPARA=\"CONNECTTO\"," + std::to_string(sec) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_recv_timeout(int sec)
{
    return dte->command("AT+HTTPPARA=\"RECVTO\"," + std::to_string(sec) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_content_type(const std::string &ct)
{
    return dte->command("AT+HTTPPARA=\"CONTENT\",\"" + ct + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_accept(const std::string &accept)
{
    return dte->command("AT+HTTPPARA=\"ACCEPT\",\"" + accept + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_ssl_cfg(int sslcfg_id)
{
    return dte->command("AT+HTTPPARA=\"SSLCFG\"," + std::to_string(sslcfg_id) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_user_data(const std::string &data)
{
    return dte->command("AT+HTTPPARA=\"USERDATA\",\"" + data + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_set_read_mode(int mode)
{
    return dte->command("AT+HTTPPARA=\"READMODE\"," + std::to_string(mode) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::http_action(HttpMethod method, HttpActionResult &result)
{
    const std::string cmd = "AT+HTTPACTION=" + std::to_string(static_cast<int>(method)) + "\r";

    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+HTTPACTION:");
        if (!line.empty()) {
            if (!parse_http_action_line(line.substr(std::string_view("+HTTPACTION:").size()), result)) {
                return CR::FAIL;
            }
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_head(std::string &header_data)
{
    header_data.clear();
    int expected_len = -1;
    size_t payload_start = std::string_view::npos;
    bool payload_ready = false;

    return dte->command("AT+HTTPHEAD\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);

        if (expected_len < 0) {
            const auto marker_pos = response.find("+HTTPHEAD:");
            if (marker_pos != std::string_view::npos) {
                const auto marker_end = response.find('\n', marker_pos);
                if (marker_end == std::string_view::npos) {
                    return CR::TIMEOUT;
                }
                const auto line = detail::trim_ascii(response.substr(marker_pos, marker_end - marker_pos));
                if (!detail::parse_integer(line.substr(std::string_view("+HTTPHEAD:").size()), expected_len)) {
                    return CR::FAIL;
                }
                payload_start = marker_end + 1;
            }
        }

        if (expected_len >= 0 && !payload_ready) {
            if (response.size() < payload_start + static_cast<size_t>(expected_len)) {
                return CR::TIMEOUT;
            }
            header_data.assign(response.data() + payload_start, static_cast<size_t>(expected_len));
            payload_ready = true;
        }

        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        if (payload_ready && response.find("OK", payload_start + static_cast<size_t>(expected_len)) != std::string_view::npos) {
            return CR::OK;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_read(int start_offset, int byte_size, std::string &data)
{
    const std::string cmd = "AT+HTTPREAD=" + std::to_string(start_offset) + "," + std::to_string(byte_size) + "\r";
    data.clear();

    int expected_len = -1;
    size_t payload_start = std::string_view::npos;
    bool payload_ready = false;

    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);

        if (expected_len < 0) {
            const auto marker_pos = response.find("+HTTPREAD:");
            if (marker_pos != std::string_view::npos) {
                const auto marker_end = response.find('\n', marker_pos);
                if (marker_end == std::string_view::npos) {
                    return CR::TIMEOUT;
                }
                const auto line = detail::trim_ascii(response.substr(marker_pos, marker_end - marker_pos));
                if (!detail::parse_integer(line.substr(std::string_view("+HTTPREAD:").size()), expected_len)) {
                    return CR::FAIL;
                }
                payload_start = marker_end + 1;
            }
        }

        if (expected_len >= 0 && !payload_ready) {
            if (response.size() < payload_start + static_cast<size_t>(expected_len)) {
                return CR::TIMEOUT;
            }
            data.assign(response.data() + payload_start, static_cast<size_t>(expected_len));
            payload_ready = true;
        }

        const auto done_pos = response.find("+HTTPREAD: 0", payload_ready ? payload_start + static_cast<size_t>(expected_len) : 0);
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        if (payload_ready && expected_len == 0 && response.find("OK", payload_start) != std::string_view::npos) {
            return CR::OK;
        }
        if (payload_ready && done_pos != std::string_view::npos && response.find("OK", done_pos) != std::string_view::npos) {
            return CR::OK;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_read_len(int &total_len)
{
    return dte->command("AT+HTTPREAD?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+HTTPREAD:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+HTTPREAD:").size()));
            if (fields.size() < 2 || fields[0] != "LEN" || !detail::parse_integer(fields[1], total_len)) {
                return CR::FAIL;
            }
        }
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_data_input(const std::string &data, int timeout_ms)
{
    const std::string cmd = "AT+HTTPDATA=" + std::to_string(data.size()) + "," + std::to_string(timeout_ms) + "\r";
    return send_data_after_prompt(cmd, data, "OK", static_cast<uint32_t>(timeout_ms + 10000));
}

CR A7670E::http_post_file(const std::string &filename, int path, std::optional<HttpMethod> method, bool send_header)
{
    std::string cmd = "AT+HTTPPOSTFILE=\"" + filename + "\"," + std::to_string(path);
    if (method.has_value()) {
        cmd += "," + std::to_string(static_cast<int>(method.value()));
        if (send_header) {
            cmd += "," + std::to_string(send_header ? 1 : 0);
        }
    }
    cmd += "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+HTTPPOSTFILE:");
        if (!line.empty()) {
            HttpActionResult result{};
            return parse_http_action_line(line.substr(std::string_view("+HTTPPOSTFILE:").size()), result) ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 120000);
}

CR A7670E::http_read_file(const std::string &filename, int path)
{
    std::string cmd = "AT+HTTPREADFILE=\"" + filename + "\"";
    if (path >= 0) {
        cmd += "," + std::to_string(path);
    }
    cmd += "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+HTTPREADFILE:");
        if (!line.empty()) {
            int errcode = -1;
            if (!parse_http_errcode(line.substr(std::string_view("+HTTPREADFILE:").size()), errcode)) {
                return CR::FAIL;
            }
            return errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 120000);
}
