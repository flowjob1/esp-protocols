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

bool parse_reg_line(std::string_view response, std::string_view prefix, int &n, RegStat &stat, std::string *area, std::string *cell)
{
    const auto line = detail::find_line(response, prefix);
    if (line.empty()) {
        return false;
    }

    const auto fields = detail::split_csv(line.substr(prefix.size()));
    if (fields.size() < 2) {
        return false;
    }

    int stat_value = 0;
    if (!detail::parse_integer(fields[0], n) || !detail::parse_integer(fields[1], stat_value)) {
        return false;
    }

    stat = static_cast<RegStat>(stat_value);
    if (area && fields.size() > 2) {
        *area = detail::unquote(fields[2]);
    }
    if (cell && fields.size() > 3) {
        *cell = detail::unquote(fields[3]);
    }
    return true;
}

} // namespace

CR A7670E::set_creg(int n)
{
    return dte->command("AT+CREG=" + std::to_string(n) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_creg(int &n, RegStat &stat, std::string &lac, std::string &ci)
{
    return dte->command("AT+CREG?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("+CREG:") != std::string_view::npos && !parse_reg_line(response, "+CREG:", n, stat, &lac, &ci)) {
            return CR::FAIL;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::scan_operators(std::vector<OperatorInfo> &ops)
{
    ops.clear();
    return dte->command("AT+COPS=?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+COPS:");
        if (!line.empty()) {
            const auto payload = line.substr(std::string_view("+COPS:").size());
            size_t cursor = 0;
            std::vector<OperatorInfo> parsed_ops;

            while (cursor < payload.size()) {
                const auto group_start = payload.find('(', cursor);
                if (group_start == std::string_view::npos) {
                    break;
                }

                bool in_quotes = false;
                size_t group_end = group_start + 1;
                for (; group_end < payload.size(); ++group_end) {
                    const auto ch = payload[group_end];
                    if (ch == '"') {
                        in_quotes = !in_quotes;
                    } else if (ch == ')' && !in_quotes) {
                        break;
                    }
                }
                if (group_end >= payload.size()) {
                    return CR::TIMEOUT;
                }

                const auto fields = detail::split_csv(payload.substr(group_start + 1, group_end - group_start - 1));
                if (fields.size() >= 5) {
                    int stat_value = 0;
                    int act_value = 0;
                    if (detail::parse_integer(fields[0], stat_value) &&
                            detail::parse_integer(fields[4], act_value)) {
                        OperatorInfo info{};
                        info.stat = stat_value;
                        info.long_name = detail::unquote(fields[1]);
                        info.short_name = detail::unquote(fields[2]);
                        info.numeric = detail::unquote(fields[3]);
                        info.act = static_cast<AccessTech>(act_value);
                        parsed_ops.push_back(std::move(info));
                    }
                }
                cursor = group_end + 1;
            }

            ops = std::move(parsed_ops);
        }
        return ok_or_error(response);
    }, 60000);
}

CR A7670E::get_operator(OperatorMode &mode, OperatorFormat &fmt, std::string &oper, AccessTech &act)
{
    return dte->command("AT+COPS?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+COPS:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+COPS:").size()));
            if (fields.empty()) {
                return CR::FAIL;
            }

            int mode_value = 0;
            if (!detail::parse_integer(fields[0], mode_value)) {
                return CR::FAIL;
            }
            mode = static_cast<OperatorMode>(mode_value);

            int fmt_value = 0;
            if (fields.size() > 1 && detail::parse_integer(fields[1], fmt_value)) {
                fmt = static_cast<OperatorFormat>(fmt_value);
            }
            if (fields.size() > 2) {
                oper = detail::unquote(fields[2]);
            }
            int act_value = 0;
            if (fields.size() > 3 && detail::parse_integer(fields[3], act_value)) {
                act = static_cast<AccessTech>(act_value);
            }
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_operator(OperatorMode mode, std::optional<OperatorFormat> fmt, std::optional<std::string> oper, std::optional<AccessTech> act)
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

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 60000);
}

CR A7670E::set_cgreg(int n)
{
    return dte->command("AT+CGREG=" + std::to_string(n) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cgreg(int &n, RegStat &stat)
{
    return dte->command("AT+CGREG?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("+CGREG:") != std::string_view::npos && !parse_reg_line(response, "+CGREG:", n, stat, nullptr, nullptr)) {
            return CR::FAIL;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_cereg(int n)
{
    return dte->command("AT+CEREG=" + std::to_string(n) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cereg(int &n, RegStat &stat, std::string &tac, std::string &ci)
{
    return dte->command("AT+CEREG?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("+CEREG:") != std::string_view::npos && !parse_reg_line(response, "+CEREG:", n, stat, &tac, &ci)) {
            return CR::FAIL;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_cgatt(int state)
{
    return dte->command("AT+CGATT=" + std::to_string(state) + "\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cgatt(int &state)
{
    return dte->command("AT+CGATT?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CGATT:");
        if (!line.empty() && !detail::parse_integer(line.substr(std::string_view("+CGATT:").size()), state)) {
            return CR::FAIL;
        }
        return ok_or_error(response);
    }, 9000);
}

CR A7670E::set_cgerep(CgerepMode mode, CgerepBfr bfr)
{
    const std::string cmd = "AT+CGEREP=" + std::to_string(static_cast<int>(mode)) + "," + std::to_string(static_cast<int>(bfr)) + "\r";
    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 9000);
}

CR A7670E::get_cgerep(CgerepMode &mode, CgerepBfr &bfr)
{
    return dte->command("AT+CGEREP?\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CGEREP:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CGEREP:").size()));
            int mode_value = 0;
            int bfr_value = 0;
            if (fields.size() < 2 ||
                    !detail::parse_integer(fields[0], mode_value) ||
                    !detail::parse_integer(fields[1], bfr_value)) {
                return CR::FAIL;
            }
            mode = static_cast<CgerepMode>(mode_value);
            bfr = static_cast<CgerepBfr>(bfr_value);
        }
        return ok_or_error(response);
    }, 9000);
}
