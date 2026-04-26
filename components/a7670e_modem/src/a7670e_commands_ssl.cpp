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

CR A7670E::ssl_cfg_set_version(int ctx_id, SslVersion v)
{
    return dte->command("AT+CSSLCFG=\"sslversion\"," + std::to_string(ctx_id) + "," + std::to_string(static_cast<int>(v)) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_auth_mode(int ctx_id, SslAuthMode m)
{
    return dte->command("AT+CSSLCFG=\"authmode\"," + std::to_string(ctx_id) + "," + std::to_string(static_cast<int>(m)) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_ignore_time(int ctx_id, bool ignore)
{
    return dte->command("AT+CSSLCFG=\"ignorelocaltime\"," + std::to_string(ctx_id) + "," + std::to_string(ignore ? 1 : 0) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_negotiate_timeout(int ctx_id, int sec)
{
    return dte->command("AT+CSSLCFG=\"negotiatetime\"," + std::to_string(ctx_id) + "," + std::to_string(sec) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_ca(int ctx_id, const std::string &file)
{
    return dte->command("AT+CSSLCFG=\"cacert\"," + std::to_string(ctx_id) + ",\"" + file + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_client_cert(int ctx_id, const std::string &file)
{
    return dte->command("AT+CSSLCFG=\"clientcert\"," + std::to_string(ctx_id) + ",\"" + file + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_client_key(int ctx_id, const std::string &file)
{
    return dte->command("AT+CSSLCFG=\"clientkey\"," + std::to_string(ctx_id) + ",\"" + file + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_password(int ctx_id, const std::string &file)
{
    return dte->command("AT+CSSLCFG=\"password\"," + std::to_string(ctx_id) + ",\"" + file + "\"\r", [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_sni(int ctx_id, bool enable)
{
    return dte->command("AT+CSSLCFG=\"enableSNI\"," + std::to_string(ctx_id) + "," + std::to_string(enable ? 1 : 0) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_set_ignore_cn(int ctx_id, bool ignore)
{
    return dte->command("AT+CSSLCFG=\"ignorecertCN\"," + std::to_string(ctx_id) + "," + std::to_string(ignore ? 1 : 0) + "\r",
                   [](uint8_t *d, size_t l) -> CR {
        return ok_or_error(std::string_view(reinterpret_cast<char *>(d), l));
    }, 120000);
}

CR A7670E::ssl_cfg_get(int ctx_id, SslContext &ctx)
{
    return dte->command("AT+CSSLCFG=" + std::to_string(ctx_id) + "\r", [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+CSSLCFG:");
        if (!line.empty()) {
            const auto fields = detail::split_csv(line.substr(std::string_view("+CSSLCFG:").size()));
            int version_value = 0;
            int auth_value = 0;
            int ignore_time_value = 0;
            int negotiate_timeout = 0;
            int sni_value = 0;
            int ignore_cn_value = 0;

            if (fields.size() < 10 ||
                    !detail::parse_integer(fields[0], version_value) ||
                    !detail::parse_integer(fields[1], auth_value) ||
                    !detail::parse_integer(fields[2], ignore_time_value) ||
                    !detail::parse_integer(fields[3], negotiate_timeout) ||
                    !detail::parse_integer(fields[8], sni_value) ||
                    !detail::parse_integer(fields[9], ignore_cn_value)) {
                return CR::FAIL;
            }

            ctx.version = static_cast<SslVersion>(version_value);
            ctx.auth_mode = static_cast<SslAuthMode>(auth_value);
            ctx.ignore_local_time = ignore_time_value != 0;
            ctx.negotiate_timeout = negotiate_timeout;
            ctx.ca_file = detail::unquote(fields[4]);
            ctx.client_cert_file = detail::unquote(fields[5]);
            ctx.client_key_file = detail::unquote(fields[6]);
            ctx.password_file = detail::unquote(fields[7]);
            ctx.enable_sni = sni_value != 0;
            ctx.ignore_cert_cn = ignore_cn_value != 0;
        }
        return ok_or_error(response);
    }, 120000);
}
