#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 18. MQTT(S) ──────────────────────────────────────────────────────────────

CR A7670E::mqtt_start(int cid)
{
    std::string cmd;
    if (cid >= 0) {
        cmd = "AT+CMQTTSTART=" + std::to_string(cid) + "\r";
    } else {
        cmd = "AT+CMQTTSTART\r";
    }

    int err = -1;
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMQTTSTART:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CMQTTSTART: %d", &err);
            return (err == 0) ? CR::OK : CR::FAIL;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::AGAIN;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 12000);
}

CR A7670E::mqtt_stop(int cid)
{
    std::string cmd;
    if (cid >= 0) {
        cmd = "AT+CMQTTSTOP=" + std::to_string(cid) + "\r";
    } else {
        cmd = "AT+CMQTTSTOP\r";
    }

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMQTTSTOP:");
        if (pos != std::string_view::npos) {
            int err;
            sscanf(r.data() + pos, "+CMQTTSTOP: %d", &err);
            return CR::OK;  // Accept regardless of err
        }
        if (r.find("OK")    != std::string_view::npos) return CR::AGAIN;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 12000);
}

CR A7670E::mqtt_accq(int client_index, const std::string &client_id, MqttServerType type)
{
    std::string cmd = "AT+CMQTTACCQ=" + std::to_string(client_index) + ",\"" + client_id +
                      "\"," + std::to_string(static_cast<int>(type)) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_rel(int client_index)
{
    std::string cmd = "AT+CMQTTREL=" + std::to_string(client_index) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_ssl_cfg(int session_id, int ssl_ctx_index)
{
    std::string cmd = "AT+CMQTTSSLCFG=" + std::to_string(session_id) + "," +
                      std::to_string(ssl_ctx_index) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_connect(int client_index, const std::string &server_addr,
                         int keepalive_sec, bool clean_session,
                         const std::string &user, const std::string &pass)
{
    std::string cmd = "AT+CMQTTCONNECT=" + std::to_string(client_index) +
                      ",\"" + server_addr + "\"," + std::to_string(keepalive_sec) +
                      "," + (clean_session ? "1" : "0");
    if (!user.empty()) {
        cmd += ",\"" + user + "\",\"" + pass + "\"";
    }
    cmd += "\r";

    int err = -1;
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMQTTCONNECT:");
        if (pos != std::string_view::npos) {
            int recv_idx;
            sscanf(r.data() + pos, "+CMQTTCONNECT: %d,%d", &recv_idx, &err);
            return (err == 0) ? CR::OK : CR::FAIL;
        }
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 60000);
}

CR A7670E::mqtt_disconnect(int client_index, int timeout_sec)
{
    std::string cmd = "AT+CMQTTDISC=" + std::to_string(client_index) + "," +
                      std::to_string(timeout_sec) + "\r";

    int err = -1;
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMQTTDISC:");
        if (pos != std::string_view::npos) {
            int recv_idx;
            sscanf(r.data() + pos, "+CMQTTDISC: %d,%d", &recv_idx, &err);
            return (err == 0) ? CR::OK : CR::FAIL;
        }
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, (timeout_sec + 10) * 1000);
}

CR A7670E::mqtt_cfg_argtopic(int index, int show_len_flag, int payload_len_flag)
{
    std::string cmd = "AT+CMQTTCFG=\"argtopic\"," + std::to_string(index) + "," +
                      std::to_string(show_len_flag) + "," + std::to_string(payload_len_flag) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_cfg_check_utf8(int index, bool enable)
{
    std::string cmd = "AT+CMQTTCFG=\"checkUTF8\"," + std::to_string(index) + "," +
                      std::to_string(enable ? 1 : 0) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_cfg_optimeout(int index, int timeout_sec)
{
    std::string cmd = "AT+CMQTTCFG=\"optimeout\"," + std::to_string(index) + "," +
                      std::to_string(timeout_sec) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_cfg_version(int index, int version)
{
    std::string cmd = "AT+CMQTTCFG=\"version\"," + std::to_string(index) + "," +
                      std::to_string(version) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_cfg_cid(int cid)
{
    std::string cmd = "AT+CMQTTCFG=\"CID\"," + std::to_string(cid) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_cfg_scid(int index, int cid)
{
    std::string cmd = "AT+CMQTTCFG=\"SCID\"," + std::to_string(index) + "," +
                      std::to_string(cid) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::mqtt_publish(int client_index, const std::string &topic,
                         const std::string &payload, MqttQos qos,
                         int timeout_sec, bool retained, bool dup)
{
    std::string cmd = "AT+CMQTTPUB=" + std::to_string(client_index) + ",\"" + topic +
                      "\"," + std::to_string(static_cast<int>(qos)) + "," +
                      std::to_string(payload.size()) + "," + (retained ? "1" : "0");
    if (dup) {
        cmd += "," + std::to_string(dup ? 1 : 0);
    }
    cmd += "\r";

    // Send command and payload in two phases
    auto r = command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view resp(reinterpret_cast<char*>(d), l);
        if (resp.find(">") != std::string_view::npos) return CR::OK;
        if (resp.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);

    if (r != CR::OK) return CR::FAIL;

    // Send payload without \r
    std::string out;
    auto res = at_raw(payload, out, "+CMQTTPUB:", "ERROR", (timeout_sec + 10) * 1000);

    // Check result
    if (res == CR::OK && out.find("+CMQTTPUB:") != std::string::npos) {
        int err;
        if (sscanf(out.c_str(), "+CMQTTPUB: %*d,%d", &err) == 1) {
            return (err == 0) ? CR::OK : CR::FAIL;
        }
    }
    return res;
}

CR A7670E::mqtt_subscribe(int client_index, const std::string &topic, MqttQos qos)
{
    std::string cmd = "AT+CMQTTSUB=" + std::to_string(client_index) + ",\"" + topic +
                      "\"," + std::to_string(static_cast<int>(qos)) + "\r";

    int sub_err = -1;
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMQTTSUB:");
        if (pos != std::string_view::npos) {
            int recv_idx;
            sscanf(r.data() + pos, "+CMQTTSUB: %d,%d", &recv_idx, &sub_err);
            return (sub_err == 0) ? CR::OK : CR::FAIL;
        }
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 30000);
}


