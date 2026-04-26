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

bool parse_mqtt_status(std::string_view response, std::string_view prefix, int &index, int &errcode)
{
    const auto line = detail::find_line(response, prefix);
    if (line.empty()) {
        return false;
    }

    const auto fields = detail::split_csv(line.substr(prefix.size()));
    if (fields.size() < 2) {
        return false;
    }

    return detail::parse_integer(fields[0], index) && detail::parse_integer(fields[1], errcode);
}

bool parse_mqtt_single_code(std::string_view response, std::string_view prefix, int &errcode)
{
    const auto line = detail::find_line(response, prefix);
    if (line.empty()) {
        return false;
    }
    const auto fields = detail::split_csv(line.substr(prefix.size()));
    return !fields.empty() && detail::parse_integer(fields[0], errcode);
}

} // namespace

CR A7670E::mqtt_start(int cid)
{
    const std::string cmd = cid >= 0 ? "AT+CMQTTSTART=" + std::to_string(cid) + "\r" : "AT+CMQTTSTART\r";

    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        int errcode = -1;
        if (parse_mqtt_single_code(response, "+CMQTTSTART:", errcode)) {
            return errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 12000);
}

CR A7670E::mqtt_stop(int cid)
{
    const std::string cmd = cid >= 0 ? "AT+CMQTTSTOP=" + std::to_string(cid) + "\r" : "AT+CMQTTSTOP\r";

    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        int errcode = -1;
        if (parse_mqtt_single_code(response, "+CMQTTSTOP:", errcode)) {
            return errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 12000);
}

CR A7670E::mqtt_accq(int client_index, const std::string &client_id, MqttServerType type)
{
    const std::string cmd = "AT+CMQTTACCQ=" + std::to_string(client_index) + ",\"" + client_id +
                            "\"," + std::to_string(static_cast<int>(type)) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_rel(int client_index)
{
    const std::string cmd = "AT+CMQTTREL=" + std::to_string(client_index) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_ssl_cfg(int session_id, int ssl_ctx_index)
{
    const std::string cmd = "AT+CMQTTSSLCFG=" + std::to_string(session_id) + "," +
                            std::to_string(ssl_ctx_index) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_connect(int client_index, const std::string &server_addr, int keepalive_sec, bool clean_session,
                        const std::string &user, const std::string &pass)
{
    std::string cmd = "AT+CMQTTCONNECT=" + std::to_string(client_index) + ",\"" + server_addr + "\"," +
                      std::to_string(keepalive_sec) + "," + (clean_session ? "1" : "0");
    if (!user.empty()) {
        cmd += ",\"" + user + "\",\"" + pass + "\"";
    }
    cmd += "\r";

    return dte->command(cmd, [client_index](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        int recv_idx = -1;
        int errcode = -1;
        if (parse_mqtt_status(response, "+CMQTTCONNECT:", recv_idx, errcode)) {
            return recv_idx == client_index && errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 60000);
}

CR A7670E::mqtt_disconnect(int client_index, int timeout_sec)
{
    const std::string cmd = "AT+CMQTTDISC=" + std::to_string(client_index) + "," + std::to_string(timeout_sec) + "\r";

    return dte->command(cmd, [client_index](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        int recv_idx = -1;
        int errcode = -1;
        if (parse_mqtt_status(response, "+CMQTTDISC:", recv_idx, errcode)) {
            return recv_idx == client_index && errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, (timeout_sec + 10) * 1000);
}

CR A7670E::mqtt_cfg_argtopic(int index, int show_len_flag, int payload_len_flag)
{
    const std::string cmd = "AT+CMQTTCFG=\"argtopic\"," + std::to_string(index) + "," +
                            std::to_string(show_len_flag) + "," + std::to_string(payload_len_flag) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_cfg_check_utf8(int index, bool enable)
{
    const std::string cmd = "AT+CMQTTCFG=\"checkUTF8\"," + std::to_string(index) + "," +
                            std::to_string(enable ? 1 : 0) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_cfg_optimeout(int index, int timeout_sec)
{
    const std::string cmd = "AT+CMQTTCFG=\"optimeout\"," + std::to_string(index) + "," + std::to_string(timeout_sec) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_cfg_version(int index, int version)
{
    const std::string cmd = "AT+CMQTTCFG=\"version\"," + std::to_string(index) + "," + std::to_string(version) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_cfg_cid(int cid)
{
    const std::string cmd = "AT+CMQTTCFG=\"CID\"," + std::to_string(cid) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_cfg_scid(int index, int cid)
{
    const std::string cmd = "AT+CMQTTCFG=\"SCID\"," + std::to_string(index) + "," + std::to_string(cid) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 5000);
}

CR A7670E::mqtt_publish(int client_index, const std::string &topic, const std::string &payload, MqttQos qos,
                        int timeout_sec, bool retained, bool dup)
{
    std::string cmd = "AT+CMQTTPUB=" + std::to_string(client_index) + ",\"" + topic + "\"," +
                      std::to_string(static_cast<int>(qos)) + "," + std::to_string(payload.size()) + "," +
                      (retained ? "1" : "0");
    if (dup) {
        cmd += ",1";
    }
    cmd += "\r";

    const auto prompt_result = dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find('>') != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 5000);
    if (prompt_result != CR::OK) {
        return prompt_result;
    }

    std::string out;
    const auto publish_result = at_raw(payload, out, "+CMQTTPUB:", "ERROR", (timeout_sec + 10) * 1000);
    if (publish_result != CR::OK) {
        return publish_result;
    }

    const auto line = detail::find_line(out, "+CMQTTPUB:");
    if (line.empty()) {
        return CR::FAIL;
    }

    const auto fields = detail::split_csv(line.substr(std::string_view("+CMQTTPUB:").size()));
    int recv_idx = -1;
    int errcode = -1;
    if (fields.size() < 2 ||
            !detail::parse_integer(fields[0], recv_idx) ||
            !detail::parse_integer(fields[1], errcode)) {
        return CR::FAIL;
    }
    return recv_idx == client_index && errcode == 0 ? CR::OK : CR::FAIL;
}

CR A7670E::mqtt_subscribe(int client_index, const std::string &topic, MqttQos qos)
{
    const std::string cmd = "AT+CMQTTSUB=" + std::to_string(client_index) + ",\"" + topic + "\"," +
                            std::to_string(static_cast<int>(qos)) + "\r";

    return dte->command(cmd, [client_index](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        int recv_idx = -1;
        int errcode = -1;
        if (parse_mqtt_status(response, "+CMQTTSUB:", recv_idx, errcode)) {
            return recv_idx == client_index && errcode == 0 ? CR::OK : CR::FAIL;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 30000);
}
