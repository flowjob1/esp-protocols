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

} // namespace

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

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::edrx_get(EDrxActType &act_type, std::string &req_val)
{
    return dte->command("AT+CEDRXS?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CEDRXS:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CEDRXS:").size()));
            int act_value = 0;
            if (fields.empty() || !detail::parse_integer(fields[0], act_value)) {
                return CR::FAIL;
            }
            act_type = static_cast<EDrxActType>(act_value);
            req_val = fields.size() > 1 ? detail::unquote(fields[1]) : "";
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::edrx_rdp(EDrxParams &params)
{
    return dte->command("AT+CEDRXRDP\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CEDRXRDP:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CEDRXRDP:").size()));
            int act_value = 0;
            if (fields.empty() || !detail::parse_integer(fields[0], act_value)) {
                return CR::FAIL;
            }
            params.act_type = static_cast<EDrxActType>(act_value);
            params.requested_value = fields.size() > 1 ? detail::unquote(fields[1]) : "";
            params.nw_provided_value = fields.size() > 2 ? detail::unquote(fields[2]) : "";
            params.paging_time_window = fields.size() > 3 ? detail::unquote(fields[3]) : "";
        }
        return ok_or_error(response);
    }, 9000);
}
