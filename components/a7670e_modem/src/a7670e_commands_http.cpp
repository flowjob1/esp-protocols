#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 16. HTTP(S) ──────────────────────────────────────────────────────────────

CR A7670E::http_init(int cid)
{
    std::string cmd;
    if (cid >= 0) {
        cmd = "AT+HTTPINIT=" + std::to_string(cid) + "\r";
    } else {
        cmd = "AT+HTTPINIT\r";
    }

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("+HTTPINIT:") != std::string_view::npos) {
            // Success with parameter
            return CR::OK;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) {
            // Ignore ERROR - might be from previous session
            if (r.find("OK") != std::string_view::npos) return CR::OK;
            return CR::FAIL;
        }
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_term(int cid)
{
    std::string cmd;
    if (cid >= 0) {
        cmd = "AT+HTTPTERM=" + std::to_string(cid) + "\r";
    } else {
        cmd = "AT+HTTPTERM\r";
    }

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_url(const std::string &url)
{
    std::string cmd = "AT+HTTPPARA=\"URL\",\"" + url + "\"\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_connect_timeout(int sec)
{
    std::string cmd = "AT+HTTPPARA=\"CONNECTTO\"," + std::to_string(sec) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_recv_timeout(int sec)
{
    std::string cmd = "AT+HTTPPARA=\"RECVTO\"," + std::to_string(sec) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_content_type(const std::string &ct)
{
    std::string cmd = "AT+HTTPPARA=\"CONTENT\",\"" + ct + "\"\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_accept(const std::string &accept)
{
    std::string cmd = "AT+HTTPPARA=\"ACCEPT\",\"" + accept + "\"\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_ssl_cfg(int sslcfg_id)
{
    std::string cmd = "AT+HTTPPARA=\"SSLCFG\"," + std::to_string(sslcfg_id) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_user_data(const std::string &data)
{
    std::string cmd = "AT+HTTPPARA=\"USERDATA\",\"" + data + "\"\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_set_read_mode(int mode)
{
    std::string cmd = "AT+HTTPPARA=\"READMODE\"," + std::to_string(mode) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_action(HttpMethod method, HttpActionResult &result)
{
    std::string cmd = "AT+HTTPACTION=" + std::to_string(static_cast<int>(method)) + "\r";

    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+HTTPACTION:");
        if (pos != std::string_view::npos) {
            int method_int, status, len;
            sscanf(r.data() + pos, "+HTTPACTION: %d,%d,%d", &method_int, &status, &len);
            result.method = static_cast<HttpMethod>(method_int);
            result.status_code = status;
            result.data_len = len;
            return CR::OK;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::AGAIN;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_head(std::string &header_data)
{
    header_data.clear();
    return command("AT+HTTPHEAD\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+HTTPHEAD:");
        if (pos != std::string_view::npos) {
            int len = 0;
            sscanf(r.data() + pos, "+HTTPHEAD: %d", &len);
            // TODO: implement header data extraction
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_read(int start_offset, int byte_size, std::string &data)
{
    std::string cmd = "AT+HTTPREAD=" + std::to_string(start_offset) + "," +
                      std::to_string(byte_size) + "\r";
    data.clear();

    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+HTTPREAD:");
        if (pos != std::string_view::npos) {
            int len = 0;
            sscanf(r.data() + pos, "+HTTPREAD: %d", &len);
            // Extract data (simplified - actual implementation depends on response format)
            auto data_start = r.find('\n', pos);
            if (data_start != std::string_view::npos) {
                data_start++;
                auto data_end = r.find("+HTTPREAD: 0", data_start);
                if (data_end != std::string_view::npos) {
                    data.append(r.data() + data_start, data_end - data_start);
                }
            }
        }
        if (r.find("+HTTPREAD: 0") != std::string_view::npos) {
            if (r.find("OK") != std::string_view::npos) return CR::OK;
        }
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_read_len(int &total_len)
{
    return command("AT+HTTPREAD?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+HTTPREAD: LEN,");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+HTTPREAD: LEN,%d", &total_len);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_data_input(const std::string &data, int timeout_sec)
{
    std::string cmd = "AT+HTTPDATA=" + std::to_string(data.size()) + "," +
                      std::to_string(timeout_sec * 1000) + "\r";

    return send_data_after_prompt(cmd, data, "OK", (timeout_sec + 10) * 1000);
}

CR A7670E::http_post_file(const std::string &filename, int path,
                           std::optional<HttpMethod> method, bool send_header)
{
    std::string cmd = "AT+HTTPPOSTFILE=\"" + filename + "\"," + std::to_string(path);
    if (method.has_value()) {
        cmd += "," + std::to_string(static_cast<int>(method.value()));
        if (send_header) {
            cmd += "," + std::to_string(send_header ? 1 : 0);
        }
    }
    cmd += "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("+HTTPPOSTFILE:") != std::string_view::npos) {
            return CR::OK;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::AGAIN;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::http_read_file(const std::string &filename, int path)
{
    std::string cmd = "AT+HTTPREADFILE=\"" + filename + "\"";
    if (path > 0) {
        cmd += "," + std::to_string(path);
    }
    cmd += "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("+HTTPREADFILE:") != std::string_view::npos) {
            return CR::OK;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::AGAIN;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

