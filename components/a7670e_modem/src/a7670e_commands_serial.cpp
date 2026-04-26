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

CR A7670E::set_baud_temp(BaudRate speed)
{
    return dte->command("AT+IPR=" + std::to_string(static_cast<uint32_t>(speed)) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_baud_temp(BaudRate &speed)
{
    return dte->command("AT+IPR?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+IPR:");
        if (!line.empty()) {
            uint32_t speed_value = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+IPR:").size()), speed_value)) {
                return CR::FAIL;
            }
            speed = static_cast<BaudRate>(speed_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_baud_permanent(BaudRate speed)
{
    return dte->command("AT+IPREX=" + std::to_string(static_cast<uint32_t>(speed)) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_baud_permanent(BaudRate &speed)
{
    return dte->command("AT+IPREX?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+IPREX:");
        if (!line.empty()) {
            uint32_t speed_value = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+IPREX:").size()), speed_value)) {
                return CR::FAIL;
            }
            speed = static_cast<BaudRate>(speed_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_icf(IcfFormat format, IcfParity parity)
{
    return dte->command("AT+ICF=" + std::to_string(static_cast<int>(format)) + "," + std::to_string(static_cast<int>(parity)) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_icf(IcfFormat &format, IcfParity &parity)
{
    return dte->command("AT+ICF?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+ICF:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+ICF:").size()));
            int format_value = 0;
            int parity_value = 0;
            if (fields.size() < 2 ||
                    !detail::parse_integer(fields[0], format_value) ||
                    !detail::parse_integer(fields[1], parity_value)) {
                return CR::FAIL;
            }
            format = static_cast<IcfFormat>(format_value);
            parity = static_cast<IcfParity>(parity_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_ifc(IfcMode dce_flow, IfcMode dte_flow)
{
    return dte->command("AT+IFC=" + std::to_string(static_cast<int>(dce_flow)) + "," + std::to_string(static_cast<int>(dte_flow)) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_ifc(IfcMode &dce_flow, IfcMode &dte_flow)
{
    return dte->command("AT+IFC?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+IFC:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+IFC:").size()));
            int dce_value = 0;
            int dte_value = 0;
            if (fields.size() < 2 ||
                    !detail::parse_integer(fields[0], dce_value) ||
                    !detail::parse_integer(fields[1], dte_value)) {
                return CR::FAIL;
            }
            dce_flow = static_cast<IfcMode>(dce_value);
            dte_flow = static_cast<IfcMode>(dte_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_uart_sleep(UartSleep mode)
{
    return dte->command("AT+CSCLK=" + std::to_string(static_cast<int>(mode)) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_uart_sleep(UartSleep &mode)
{
    return dte->command("AT+CSCLK?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CSCLK:");
        if (!line.empty()) {
            int mode_value = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+CSCLK:").size()), mode_value)) {
                return CR::FAIL;
            }
            mode = static_cast<UartSleep>(mode_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::enable_cmux(int port_speed_index, int n1, int t2)
{
    std::string cmd = "AT+CMUX=0,,";
    cmd += port_speed_index >= 0 ? std::to_string(port_speed_index) : "5";
    cmd += ",";
    if (n1 > 0) {
        cmd += std::to_string(n1);
    }
    cmd += ",,";
    if (t2 > 0) {
        cmd += std::to_string(t2);
    }
    cmd += "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cmux(int &speed_idx, int &n1, int &t2)
{
    return dte->command("AT+CMUX?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CMUX:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CMUX:").size()));
            int speed_value = 0;
            int n1_value = 0;
            int t2_value = 0;
            if (fields.size() < 6 ||
                    !detail::parse_integer(fields[2], speed_value) ||
                    !detail::parse_integer(fields[3], n1_value) ||
                    !detail::parse_integer(fields[5], t2_value)) {
                return CR::FAIL;
            }
            speed_idx = speed_value;
            n1 = n1_value;
            t2 = t2_value;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_urc_port(UrcPort port)
{
    return dte->command("AT+CATR=" + std::to_string(static_cast<int>(port)) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_urc_port(UrcPort &port)
{
    return dte->command("AT+CATR?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CATR:");
        if (!line.empty()) {
            int port_value = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+CATR:").size()), port_value)) {
                return CR::FAIL;
            }
            port = static_cast<UrcPort>(port_value);
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_cfgri(bool enabled, int urc_time_ms, int sms_time_ms)
{
    const std::string cmd = "AT+CFGRI=" + std::to_string(enabled ? 1 : 0) + "," + std::to_string(urc_time_ms) + "," +
                            std::to_string(sms_time_ms) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cfgri(bool &enabled, int &urc_ms, int &sms_ms)
{
    return dte->command("AT+CFGRI?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CFGRI:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CFGRI:").size()));
            int enabled_value = 0;
            if (fields.size() < 3 ||
                    !detail::parse_integer(fields[0], enabled_value) ||
                    !detail::parse_integer(fields[1], urc_ms) ||
                    !detail::parse_integer(fields[2], sms_ms)) {
                return CR::FAIL;
            }
            enabled = enabled_value != 0;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_curcd(int delay_ms, int cache_size)
{
    return dte->command("AT+CURCD=" + std::to_string(delay_ms) + "," + std::to_string(cache_size) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_curcd(int &delay_ms, int &cache_size)
{
    return dte->command("AT+CURCD?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CURCD:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CURCD:").size()));
            if (fields.size() < 2 ||
                    !detail::parse_integer(fields[0], delay_ms) ||
                    !detail::parse_integer(fields[1], cache_size)) {
                return CR::FAIL;
            }
        }
        return ok_or_error(response);
    }, 9000);
}
