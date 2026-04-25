#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 19. SSL ──────────────────────────────────────────────────────────────────

CR A7670E::ssl_cfg_set_version(int ctx_id, SslVersion v)
{
    std::string cmd = "AT+CSSLCFG=\"sslversion\"," + std::to_string(ctx_id) + "," +
                      std::to_string(static_cast<int>(v)) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_auth_mode(int ctx_id, SslAuthMode m)
{
    std::string cmd = "AT+CSSLCFG=\"authmode\"," + std::to_string(ctx_id) + "," +
                      std::to_string(static_cast<int>(m)) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_ignore_time(int ctx_id, bool ignore)
{
    std::string cmd = "AT+CSSLCFG=\"ignorelocaltime\"," + std::to_string(ctx_id) + "," +
                      std::to_string(ignore ? 1 : 0) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_negotiate_timeout(int ctx_id, int sec)
{
    std::string cmd = "AT+CSSLCFG=\"negotiatetime\"," + std::to_string(ctx_id) + "," +
                      std::to_string(sec) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_ca(int ctx_id, const std::string &file)
{
    std::string cmd = "AT+CSSLCFG=\"cacert\"," + std::to_string(ctx_id) + ",\"" +
                      file + "\"\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_client_cert(int ctx_id, const std::string &file)
{
    std::string cmd = "AT+CSSLCFG=\"clientcert\"," + std::to_string(ctx_id) + ",\"" +
                      file + "\"\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_client_key(int ctx_id, const std::string &file)
{
    std::string cmd = "AT+CSSLCFG=\"clientkey\"," + std::to_string(ctx_id) + ",\"" +
                      file + "\"\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_password(int ctx_id, const std::string &file)
{
    std::string cmd = "AT+CSSLCFG=\"password\"," + std::to_string(ctx_id) + ",\"" +
                      file + "\"\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_sni(int ctx_id, bool enable)
{
    std::string cmd = "AT+CSSLCFG=\"enableSNI\"," + std::to_string(ctx_id) + "," +
                      std::to_string(enable ? 1 : 0) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_set_ignore_cn(int ctx_id, bool ignore)
{
    std::string cmd = "AT+CSSLCFG=\"ignorecertCN\"," + std::to_string(ctx_id) + "," +
                      std::to_string(ignore ? 1 : 0) + "\r";

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

CR A7670E::ssl_cfg_get(int ctx_id, SslContext &ctx)
{
    std::string cmd = "AT+CSSLCFG=" + std::to_string(ctx_id) + "\r";

    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        // Parse response: +CSSLCFG: <fields>
        auto pos = r.find("+CSSLCFG:");
        if (pos != std::string_view::npos) {
            int version_int, auth_int, ignore_int, neg_time;
            char ca_buf[256] = {0};
            char cert_buf[256] = {0};
            char key_buf[256] = {0};
            char pwd_buf[256] = {0};
            int sni_int, cn_int;

            sscanf(r.data() + pos,
                   "+CSSLCFG: %d,%d,%d,%d,\"%255[^\"]\",\"%255[^\"]\",\"%255[^\"]\",\"%255[^\"]\"%*c%d,%d",
                   &version_int, &auth_int, &ignore_int, &neg_time,
                   ca_buf, cert_buf, key_buf, pwd_buf, &sni_int, &cn_int);

            ctx.version = static_cast<SslVersion>(version_int);
            ctx.auth_mode = static_cast<SslAuthMode>(auth_int);
            ctx.ignore_local_time = (ignore_int != 0);
            ctx.negotiate_timeout = neg_time;
            ctx.ca_file = ca_buf;
            ctx.client_cert_file = cert_buf;
            ctx.client_key_file = key_buf;
            ctx.password_file = pwd_buf;
            ctx.enable_sni = (sni_int != 0);
            ctx.ignore_cert_cn = (cn_int != 0);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 120000);
}

