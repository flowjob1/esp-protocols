#include "a7670e_module.hpp"
#include <cstring>
#include <cctype>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 4. Network ───────────────────────────────────────────────────────────────

CR A7670E::set_creg(int n)
{
    std::string cmd = "AT+CREG=" + std::to_string(n) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_creg(int &n, RegStat &stat, std::string &lac, std::string &ci)
{
    return command("AT+CREG?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CREG:");
        if (pos != std::string_view::npos) {
            int stat_int;
            char lac_buf[32] = {0};
            char ci_buf[32] = {0};
            int parsed = sscanf(r.data() + pos, "+CREG: %d,%d,\"%31[^\"]\",\"%31[^\"]\"", &n, &stat_int, lac_buf, ci_buf);
            if (parsed >= 2) {
                stat = static_cast<RegStat>(stat_int);
                if (parsed >= 4) {
                    lac = lac_buf;
                    ci = ci_buf;
                }
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::scan_operators(std::vector<OperatorInfo> &ops)
{
    ops.clear();
    return command("AT+COPS=?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+COPS:");
        if (pos != std::string_view::npos) {
            // Parse CSV list: (stat,"long","short","numeric",act)[,(stat,"long",...)]...
            // Simplified parsing: just collect all matches
            const char *p = r.data() + pos;
            while ((p = strchr(p, '(')) != nullptr) {
                int stat_val, act_val;
                char long_name[256] = {0};
                char short_name[256] = {0};
                char numeric[256] = {0};

                int n = sscanf(p, "(%d,\"%255[^\"]\",\"%255[^\"]\",\"%255[^\"]\",%d",
                               &stat_val, long_name, short_name, numeric, &act_val);
                if (n == 5) {
                    OperatorInfo info;
                    info.stat = stat_val;
                    info.long_name = long_name;
                    info.short_name = short_name;
                    info.numeric = numeric;
                    info.act = static_cast<AccessTech>(act_val);
                    ops.push_back(info);
                }
                p++;
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 60000);  // 60 second timeout for operator scan
}

CR A7670E::get_operator(OperatorMode &mode, OperatorFormat &fmt,
                        std::string &oper, AccessTech &act)
{
    return command("AT+COPS?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+COPS:");
        if (pos != std::string_view::npos) {
            int mode_int, fmt_int, act_int;
            char oper_buf[256] = {0};

            // Try parsing with all fields
            int n = sscanf(r.data() + pos, "+COPS: %d,%d,\"%255[^\"]\"%*c%d",
                           &mode_int, &fmt_int, oper_buf, &act_int);
            if (n >= 1) {
                mode = static_cast<OperatorMode>(mode_int);
                if (n >= 2) fmt = static_cast<OperatorFormat>(fmt_int);
                if (n >= 3) oper = oper_buf;
                if (n >= 4) act = static_cast<AccessTech>(act_int);
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_operator(OperatorMode mode,
                        std::optional<OperatorFormat> fmt,
                        std::optional<std::string> oper,
                        std::optional<AccessTech> act)
{
    std::string cmd = "AT+COPS=" + std::to_string(static_cast<int>(mode));
    if (fmt.has_value()) {
        cmd += "," + std::to_string(static_cast<int>(fmt.value()));
        if (oper.has_value()) {
            cmd += ",\"" + oper.value() + "\"";
            if (act.has_value()) {
                cmd += "," + std::to_string(static_cast<int>(act.value()));
            }
        }
    }
    cmd += "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 60000);
}

// ── 5. Packet Domain ─────────────────────────────────────────────────────────

CR A7670E::set_cgreg(int n)
{
    std::string cmd = "AT+CGREG=" + std::to_string(n) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cgreg(int &n, RegStat &stat)
{
    return command("AT+CGREG?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGREG:");
        if (pos != std::string_view::npos) {
            int stat_int;
            sscanf(r.data() + pos, "+CGREG: %d,%d", &n, &stat_int);
            stat = static_cast<RegStat>(stat_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_cereg(int n)
{
    std::string cmd = "AT+CEREG=" + std::to_string(n) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cereg(int &n, RegStat &stat, std::string &tac, std::string &ci)
{
    return command("AT+CEREG?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CEREG:");
        if (pos != std::string_view::npos) {
            int stat_int;
            char tac_buf[32] = {0};
            char ci_buf[32] = {0};
            int parsed = sscanf(r.data() + pos, "+CEREG: %d,%d,\"%31[^\"]\",\"%31[^\"]\"", &n, &stat_int, tac_buf, ci_buf);
            if (parsed >= 2) {
                stat = static_cast<RegStat>(stat_int);
                if (parsed >= 4) {
                    tac = tac_buf;
                    ci = ci_buf;
                }
            }
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_cgatt(int state)
{
    std::string cmd = "AT+CGATT=" + std::to_string(state) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cgatt(int &state)
{
    return command("AT+CGATT?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGATT:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CGATT: %d", &state);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::set_cgerep(CgerepMode mode, CgerepBfr bfr)
{
    std::string cmd = "AT+CGEREP=" + std::to_string(static_cast<int>(mode)) + "," +
                      std::to_string(static_cast<int>(bfr)) + "\r";
    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::get_cgerep(CgerepMode &mode, CgerepBfr &bfr)
{
    return command("AT+CGEREP?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGEREP:");
        if (pos != std::string_view::npos) {
            int mode_int, bfr_int;
            sscanf(r.data() + pos, "+CGEREP: %d,%d", &mode_int, &bfr_int);
            mode = static_cast<CgerepMode>(mode_int);
            bfr = static_cast<CgerepBfr>(bfr_int);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

