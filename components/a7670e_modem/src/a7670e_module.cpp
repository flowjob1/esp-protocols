#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

void A7670E::init_urc_handler(std::shared_ptr<esp_modem::DTE> dte_ref)
{
    urc_handler_ = std::make_unique<A7670eUrcHandler>();
    if (urc_handler_) {
        auto handler = urc_handler_.get();
        set_urc([handler](uint8_t *data, size_t len) {
            handler->handle(data, len);
        });
    }
}

void A7670E::set_mqtt_message_cb(MqttMessageCb cb)
{
    if (urc_handler_) {
        urc_handler_->on_mqtt_message = cb;
    }
}

void A7670E::set_mqtt_conn_lost_cb(MqttConnLostCb cb)
{
    if (urc_handler_) {
        urc_handler_->on_mqtt_conn_lost = cb;
    }
}

void A7670E::set_gnss_ready_cb(std::function<void()> cb)
{
    if (urc_handler_) {
        urc_handler_->on_gnss_ready = cb;
    }
}

void A7670E::set_gnss_info_cb(std::function<void(const GnssPosition&)> cb)
{
    if (urc_handler_) {
        urc_handler_->on_gnss_info = cb;
    }
}

CR A7670E::send_data_after_prompt(const std::string &cmd,
                                   const std::string &data,
                                   const std::string &expected_final,
                                   uint32_t timeout_ms)
{
    // Phase 1: Command senden, auf Prompt warten
    auto r = command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view resp(reinterpret_cast<char*>(d), l);
        if (resp.find(">")        != std::string_view::npos) return CR::OK;
        if (resp.find("DOWNLOAD") != std::string_view::npos) return CR::OK;
        if (resp.find("ERROR")    != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, timeout_ms);

    if (r != CR::OK) return CR::FAIL;

    // Phase 2: Rohdaten senden, auf finales OK warten
    std::string out;
    return at_raw(data, out, expected_final, "ERROR", timeout_ms);
}

// ── 3. Status Control ────────────────────────────────────

CR A7670E::power_off(int mode)
{
    std::string cmd;
    if (mode >= 0) {
        cmd = "AT+CPOF=" + std::to_string(mode) + "\r";
    } else {
        cmd = "AT+CPOF\r";
    }

    return command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("POWERED DOWN") != std::string_view::npos) return CR::OK;
        if (r.find("OK")          != std::string_view::npos) return CR::OK;
        if (r.find("ERROR")       != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

CR A7670E::reset_module()
{
    return command("AT+CRESET\r", [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}

