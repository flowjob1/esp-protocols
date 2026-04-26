#include "a7670e_module.hpp"
#include "a7670e_parse_utils.hpp"

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

namespace {

bool parse_gnss_info_line(std::string_view response, GnssPosition &pos)
{
    const auto line = detail::find_line(response, "+CGNSSINFO:");
    if (line.empty()) {
        return false;
    }

    pos = GnssPosition{};
    const auto fields = detail::split_csv(line.substr(std::string_view("+CGNSSINFO:").size()));
    if (fields.empty() || detail::trim_ascii(fields[0]).empty()) {
        return true;
    }

    int mode = 0;
    if (!detail::parse_integer(fields[0], mode)) {
        return false;
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
    return true;
}

} // namespace

CR A7670E::gnss_power(int power, int ap_flash, int dynamic_load)
{
    std::string cmd = "AT+CGNSSPWR=" + std::to_string(power);
    if (ap_flash >= 0) {
        cmd += "," + std::to_string(ap_flash);
        if (dynamic_load >= 0) {
            cmd += "," + std::to_string(dynamic_load);
        }
    }
    cmd += "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::gnss_mode_set(GnssMode mode)
{
    const std::string cmd = "AT+CGNSSMODE=" + std::to_string(static_cast<int>(mode)) + "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::gnss_mode_get(GnssMode &mode)
{
    return dte->command("AT+CGNSSMODE?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CGNSSMODE:");
        if (!line.empty()) {
            int mode_int = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+CGNSSMODE:").size()), mode_int)) {
                return CR::FAIL;
            }
            mode = static_cast<GnssMode>(mode_int);
        }
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::gnss_nmea_set(int gga, int gll, int gsa, int gsv, int rmc, int vtg, int zda, int gst)
{
    const std::string cmd = "AT+CGNSSNMEA=" + std::to_string(gga) + "," + std::to_string(gll) + "," +
                            std::to_string(gsa) + "," + std::to_string(gsv) + "," +
                            std::to_string(rmc) + "," + std::to_string(vtg) + "," +
                            std::to_string(zda) + "," + std::to_string(gst) + "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::gnss_nmea_get(int &gga, int &gll, int &gsa, int &gsv, int &rmc, int &vtg, int &zda, int &gst)
{
    return dte->command("AT+CGNSSNMEA?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CGNSSNMEA:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CGNSSNMEA:").size()));
            if (fields.size() < 8 ||
                    !detail::parse_integer(fields[0], gga) ||
                    !detail::parse_integer(fields[1], gll) ||
                    !detail::parse_integer(fields[2], gsa) ||
                    !detail::parse_integer(fields[3], gsv) ||
                    !detail::parse_integer(fields[4], rmc) ||
                    !detail::parse_integer(fields[5], vtg) ||
                    !detail::parse_integer(fields[6], zda) ||
                    !detail::parse_integer(fields[7], gst)) {
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
    }, 9000);
}

CR A7670E::gnss_info(GnssPosition &pos)
{
    return dte->command("AT+CGNSSINFO\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("+CGNSSINFO:") != std::string_view::npos && !parse_gnss_info_line(response, pos)) {
            return CR::FAIL;
        }
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::gnss_info_periodic(int time_sec)
{
    const std::string cmd = "AT+CGNSSINFO=" + std::to_string(time_sec) + "\r";

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
    }, 9000);
}
