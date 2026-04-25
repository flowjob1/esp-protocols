#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 34. eDRX ─────────────────────────────────────────────────────────────────

CR A7670E::edrx_set(int mode, EDrxActType act_type, const std::string &req_value)
{
    std::string cmd = "AT+CEDRXS=" + std::to_string(mode);
    if (act_type != EDrxActType::NOT_USING || !req_value.empty()) {
        cmd += "," + std::to_string(static_cast<int>(act_type));
        if (!req_value.empty()) {
            cmd += ",\"" + req_value + "\"";
        }
    }
    cmd += "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::edrx_get(EDrxActType &act_type, std::string &req_val)
{
    return command("AT+CEDRXS?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CEDRXS:");
        if (pos != std::string_view::npos) {
            int act_int;
            char val_buf[64] = {0};
            int n = sscanf(r.data() + pos, "+CEDRXS: %d,\"%63[^\"]\"", &act_int, val_buf);
            if (n >= 1) {
                act_type = static_cast<EDrxActType>(act_int);
                if (n >= 2) {
                    req_val = val_buf;
                }
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::edrx_rdp(EDrxParams &params)
{
    return command("AT+CEDRXRDP\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CEDRXRDP:");
        if (pos != std::string_view::npos) {
            int act_int;
            char req_buf[64] = {0};
            char nw_buf[64] = {0};
            char ptw_buf[64] = {0};

            int n = sscanf(r.data() + pos,
                          "+CEDRXRDP: %d,\"%63[^\"]\",\"%63[^\"]\",\"%63[^\"]\"",
                          &act_int, req_buf, nw_buf, ptw_buf);

            if (n >= 1) {
                params.act_type = static_cast<EDrxActType>(act_int);
                if (n >= 2) params.requested_value = req_buf;
                if (n >= 3) params.nw_provided_value = nw_buf;
                if (n >= 4) params.paging_time_window = ptw_buf;
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

