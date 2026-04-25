#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 10. Serial Interface ─────────────────────────────────────────────────────

CR A7670E::set_baud_temp(BaudRate speed)
{
    std::string cmd = "AT+IPR=" + std::to_string(static_cast<uint32_t>(speed)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_baud_temp(BaudRate &speed)
{
    return command("AT+IPR?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+IPR:");
        if (pos != std::string_view::npos) {
            uint32_t speed_val;
            sscanf(r.data() + pos, "+IPR: %u", &speed_val);
            speed = static_cast<BaudRate>(speed_val);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_baud_permanent(BaudRate speed)
{
    std::string cmd = "AT+IPREX=" + std::to_string(static_cast<uint32_t>(speed)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_baud_permanent(BaudRate &speed)
{
    return command("AT+IPREX?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+IPREX:");
        if (pos != std::string_view::npos) {
            uint32_t speed_val;
            sscanf(r.data() + pos, "+IPREX: %u", &speed_val);
            speed = static_cast<BaudRate>(speed_val);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_icf(IcfFormat format, IcfParity parity)
{
    std::string cmd = "AT+ICF=" + std::to_string(static_cast<int>(format)) + "," +
                      std::to_string(static_cast<int>(parity)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_icf(IcfFormat &format, IcfParity &parity)
{
    return command("AT+ICF?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+ICF:");
        if (pos != std::string_view::npos) {
            int fmt_int, par_int;
            sscanf(r.data() + pos, "+ICF: %d,%d", &fmt_int, &par_int);
            format = static_cast<IcfFormat>(fmt_int);
            parity = static_cast<IcfParity>(par_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_ifc(IfcMode dce_flow, IfcMode dte_flow)
{
    std::string cmd = "AT+IFC=" + std::to_string(static_cast<int>(dce_flow)) + "," +
                      std::to_string(static_cast<int>(dte_flow)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_ifc(IfcMode &dce_flow, IfcMode &dte_flow)
{
    return command("AT+IFC?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+IFC:");
        if (pos != std::string_view::npos) {
            int dce_int, dte_int;
            sscanf(r.data() + pos, "+IFC: %d,%d", &dce_int, &dte_int);
            dce_flow = static_cast<IfcMode>(dce_int);
            dte_flow = static_cast<IfcMode>(dte_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_uart_sleep(UartSleep mode)
{
    std::string cmd = "AT+CSCLK=" + std::to_string(static_cast<int>(mode)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_uart_sleep(UartSleep &mode)
{
    return command("AT+CSCLK?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CSCLK:");
        if (pos != std::string_view::npos) {
            int mode_int;
            sscanf(r.data() + pos, "+CSCLK: %d", &mode_int);
            mode = static_cast<UartSleep>(mode_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::enable_cmux(int port_speed_index, int n1, int t2)
{
    std::string cmd = "AT+CMUX=0,,";
    if (port_speed_index >= 0) cmd += std::to_string(port_speed_index);
    else cmd += "5";
    cmd += ",";
    if (n1 > 0) cmd += std::to_string(n1);
    cmd += ",,";
    if (t2 > 0) cmd += std::to_string(t2);
    cmd += "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cmux(int &speed_idx, int &n1, int &t2)
{
    return command("AT+CMUX?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CMUX:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CMUX: %*d,%*d,%d,%d,%*d,%d", &speed_idx, &n1, &t2);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_urc_port(UrcPort port)
{
    std::string cmd = "AT+CATR=" + std::to_string(static_cast<int>(port)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_urc_port(UrcPort &port)
{
    return command("AT+CATR?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CATR:");
        if (pos != std::string_view::npos) {
            int port_int;
            sscanf(r.data() + pos, "+CATR: %d", &port_int);
            port = static_cast<UrcPort>(port_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_cfgri(bool enabled, int urc_time_ms, int sms_time_ms)
{
    std::string cmd = "AT+CFGRI=" + std::to_string(enabled ? 1 : 0) + "," +
                      std::to_string(urc_time_ms) + "," +
                      std::to_string(sms_time_ms) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cfgri(bool &enabled, int &urc_ms, int &sms_ms)
{
    return command("AT+CFGRI?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CFGRI:");
        if (pos != std::string_view::npos) {
            int enabled_int;
            sscanf(r.data() + pos, "+CFGRI: %d,%d,%d", &enabled_int, &urc_ms, &sms_ms);
            enabled = (enabled_int != 0);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_curcd(int delay_ms, int cache_size)
{
    std::string cmd = "AT+CURCD=" + std::to_string(delay_ms) + "," +
                      std::to_string(cache_size) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_curcd(int &delay_ms, int &cache_size)
{
    return command("AT+CURCD?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CURCD:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CURCD: %d,%d", &delay_ms, &cache_size);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

