#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 23. GNSS ─────────────────────────────────────────────────────────────────

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

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_mode_set(GnssMode mode)
{
    std::string cmd = "AT+CGNSSMODE=" + std::to_string(static_cast<int>(mode)) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_mode_get(GnssMode &mode)
{
    return command("AT+CGNSSMODE?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGNSSMODE:");
        if (pos != std::string_view::npos) {
            int mode_int;
            sscanf(r.data() + pos, "+CGNSSMODE: %d", &mode_int);
            mode = static_cast<GnssMode>(mode_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_nmea_set(int gga, int gll, int gsa, int gsv, int rmc, int vtg, int zda, int gst)
{
    std::string cmd = "AT+CGNSSNMEA=" + std::to_string(gga) + "," + std::to_string(gll) + "," +
                      std::to_string(gsa) + "," + std::to_string(gsv) + "," +
                      std::to_string(rmc) + "," + std::to_string(vtg) + "," +
                      std::to_string(zda) + "," + std::to_string(gst) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_nmea_get(int &gga, int &gll, int &gsa, int &gsv, int &rmc, int &vtg, int &zda, int &gst)
{
    return command("AT+CGNSSNMEA?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGNSSNMEA:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CGNSSNMEA: %d,%d,%d,%d,%d,%d,%d,%d",
                   &gga, &gll, &gsa, &gsv, &rmc, &vtg, &zda, &gst);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_info(GnssPosition &pos)
{
    return command("AT+CGNSSINFO\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos_marker = r.find("+CGNSSINFO:");
        if (pos_marker != std::string_view::npos) {
            pos = GnssPosition();  // Reset

            char ns_ch = 'N', ew_ch = 'E';
            char date_buf[32] = {0};
            char utc_buf[32] = {0};

            int n = sscanf(r.data() + pos_marker,
                          "+CGNSSINFO: %d,%d,%d,%d,%d,%lf,%c,%lf,%c,%31[^,],%31[^,],"
                          "%lf,%lf,%lf,%lf,%lf,%lf,%d",
                          &pos.mode, &pos.gps_svs, &pos.beidou_svs, &pos.glonass_svs,
                          &pos.galileo_svs, &pos.lat, &ns_ch, &pos.lon, &ew_ch,
                          date_buf, utc_buf, &pos.alt_m, &pos.speed_knots,
                          &pos.course_deg, &pos.pdop, &pos.hdop, &pos.vdop,
                          &pos.num_sv);

            if (n >= 18 && pos.lat > 0.0) {
                pos.valid = true;
                pos.ns = ns_ch;
                pos.ew = ew_ch;
                pos.date = date_buf;
                pos.utc = utc_buf;
            } else {
                pos.valid = false;
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::gnss_info_periodic(int time_sec)
{
    std::string cmd = "AT+CGNSSINFO=" + std::to_string(time_sec) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

