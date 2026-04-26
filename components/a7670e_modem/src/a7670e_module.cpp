#include "a7670e_module.hpp"
#include "cxx_include/esp_modem_dce_factory.hpp"
#include "cxx_include/esp_modem_dte.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

void A7670E::init_urc_handler(std::shared_ptr<esp_modem::DTE> dte_ref)
{
    urc_handler_ = std::make_unique<A7670eUrcHandler>();
    auto target_dte = dte_ref ? std::move(dte_ref) : dte;
    if (!urc_handler_ || !target_dte) {
        return;
    }

#ifdef CONFIG_ESP_MODEM_URC_HANDLER
    auto *handler = urc_handler_.get();
    target_dte->set_enhanced_urc_cb([handler](const esp_modem::DTE::UrcBufferInfo &info) {
        const std::string_view buffer(reinterpret_cast<const char *>(info.buffer_start), info.buffer_total_size);
        const auto consumed = handler->handle_buffer(buffer, info.is_command_active);
        if (consumed == 0) {
            return esp_modem::DTE::UrcConsumeInfo{esp_modem::DTE::UrcConsumeResult::CONSUME_NONE, 0};
        }
        if (consumed >= info.buffer_total_size) {
            return esp_modem::DTE::UrcConsumeInfo{esp_modem::DTE::UrcConsumeResult::CONSUME_ALL, info.buffer_total_size};
        }
        return esp_modem::DTE::UrcConsumeInfo{esp_modem::DTE::UrcConsumeResult::CONSUME_PARTIAL, consumed};
    });
#endif
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
    auto r = dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view resp(reinterpret_cast<char*>(d), l);
        if (resp.find(">")        != std::string_view::npos) return CR::OK;
        if (resp.find("DOWNLOAD") != std::string_view::npos) return CR::OK;
        if (resp.find("ERROR")    != std::string_view::npos) return CR::FAIL;
        return CR::TIMEOUT;
    }, timeout_ms);

    if (r != CR::OK) {
        return r;
    }

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

    return dte->command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("POWERED DOWN") != std::string_view::npos) return CR::OK;
        if (r.find("OK")          != std::string_view::npos) return CR::OK;
        if (r.find("ERROR")       != std::string_view::npos) return CR::FAIL;
        return CR::TIMEOUT;
    }, 9000);
}

CR A7670E::reset_module()
{
    return dte->command("AT+CRESET\r", [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::TIMEOUT;
    }, 9000);
}

std::unique_ptr<DCE> a7670e::create_a7670e_dce(const dce_config *dce_cfg, const dte_config *dte_cfg)
{
    auto uart_dte = create_uart_dte(dte_cfg);
    if (!uart_dte) {
        return nullptr;
    }

    auto dce = dce_factory::Factory::create_unique_dce_from<A7670E>(dce_cfg, uart_dte, nullptr);
    if (!dce) {
        return nullptr;
    }

    auto *modem = static_cast<A7670E *>(dce->get_module());
    if (modem) {
        modem->init_urc_handler(uart_dte);
    }
    return dce;
}
