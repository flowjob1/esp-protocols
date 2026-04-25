#include "a7670e_module.hpp"
#include "esp_modem_api.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using namespace esp_modem;
using namespace a7670e;

static const char *TAG = "A7670E_EXAMPLE";

// Beispiel: Instanziierung und einfache AT-Commands
void a7670e_example_task(void *pvParameters)
{
    // Konfiguration für DTE (Device Terminal Equipment)
    dte_config dce_cfg{};
    dce_cfg.port_num = 2;          // UART2
    dce_cfg.tx_io_num = 4;
    dce_cfg.rx_io_num = 5;
    dce_cfg.rts_io_num = 6;
    dce_cfg.cts_io_num = 7;
    dce_cfg.baud_rate = 115200;
    dce_cfg.flow_control = flow_control::HW;
    dce_cfg.task_stack_size = 4096;

    // Konfiguration für DCE (Data Communications Equipment)
    dce_config dce_cfg{};
    dce_cfg.dte = &dce_cfg;
    dce_cfg.delay_after_firstread_ms = 0;
    dce_cfg.uart_timeout_ms = 1000;

    // DCE erstellen (AT-only Mode, netif=nullptr)
    std::unique_ptr<DCE> dce;
    try {
        auto uart_dte = create_uart_dte(&dce_cfg);
        dce = dce_factory::Factory::create_unique_dce_from<A7670E>(&dce_cfg, uart_dte, nullptr);
    } catch (const std::exception &e) {
        ESP_LOGE(TAG, "Failed to create DCE: %s", e.what());
        vTaskDelete(NULL);
        return;
    }

    auto *modem = static_cast<A7670E*>(dce->get_module());
    if (!modem) {
        ESP_LOGE(TAG, "Failed to get module");
        vTaskDelete(NULL);
        return;
    }

    // URC-Handler initialisieren
    modem->init_urc_handler(uart_dte);

    ESP_LOGI(TAG, "A7670E Modem initialized");

    // ── Beispiel 1: Module zurücksetzen
    if (modem->reset_module() == command_result::OK) {
        ESP_LOGI(TAG, "Module reset successful");
    }

    // ── Beispiel 2: Netzwerkregistrierung überprüfen
    int n;
    RegStat stat;
    std::string lac, ci;
    if (modem->get_creg(n, stat, lac, ci) == command_result::OK) {
        ESP_LOGI(TAG, "CREG: n=%d, stat=%d, lac=%s, ci=%s", n, static_cast<int>(stat),
                 lac.c_str(), ci.c_str());
    }

    // ── Beispiel 3: PS Attach
    if (modem->set_cgatt(1) == command_result::OK) {
        ESP_LOGI(TAG, "PS Attach successful");
    }

    // ── Beispiel 4: Baudrate auslesen
    BaudRate baud;
    if (modem->get_baud_temp(baud) == command_result::OK) {
        ESP_LOGI(TAG, "Current baudrate: %u", static_cast<uint32_t>(baud));
    }

    // ── Beispiel 5: URC-Port setzen
    if (modem->set_urc_port(UrcPort::UART) == command_result::OK) {
        ESP_LOGI(TAG, "URC port set to UART");
    }

    // ── Beispiel 6: MQTT Message Callback registrieren
    modem->set_mqtt_message_cb([](const MqttMessage &msg) {
        ESP_LOGI(TAG, "MQTT Message received - Topic: %s, Payload: %s",
                 msg.topic.c_str(), msg.payload.c_str());
    });

    // ── Beispiel 7: Datei-Größe abfragen
    FsAttriResult fs_result;
    if (modem->fs_attri("ca_cert.pem", fs_result) == command_result::OK) {
        ESP_LOGI(TAG, "File size: %llu bytes", fs_result.size_bytes);
    }

    // ── Beispiel 8: GNSS Power einschalten (mit Callback)
    modem->set_gnss_ready_cb([]() {
        ESP_LOGI(TAG, "GNSS is ready!");
    });

    modem->set_gnss_info_cb([](const GnssPosition &pos) {
        if (pos.valid) {
            ESP_LOGI(TAG, "GNSS Position: lat=%.6f%c, lon=%.6f%c, alt=%.1f m",
                     pos.lat, pos.ns, pos.lon, pos.ew, pos.alt_m);
        }
    });

    if (modem->gnss_power(1) == command_result::OK) {
        ESP_LOGI(TAG, "GNSS power on sent");
    }

    // ── Beispiel 9: HTTP-Operation
    if (modem->http_init() == command_result::OK) {
        ESP_LOGI(TAG, "HTTP initialized");

        modem->http_set_url("http://example.com/status");
        HttpActionResult result;
        if (modem->http_action(HttpMethod::GET, result) == command_result::OK) {
            ESP_LOGI(TAG, "HTTP GET: status=%d, len=%d", result.status_code, result.data_len);
        }

        modem->http_term();
    }

    // ── Beispiel 10: MQTT nutzen (vereinfacht)
    // Hinweis: argtopic-Modus ist mandatory!
    if (modem->mqtt_start() == command_result::OK) {
        ESP_LOGI(TAG, "MQTT started");

        if (modem->mqtt_accq(0, "ESP32-A7670E", MqttServerType::TCP) == command_result::OK) {
            ESP_LOGI(TAG, "MQTT client acquired");

            // argtopic-Modus aktivieren - WICHTIG!
            modem->mqtt_cfg_argtopic(0, 1, 1);

            if (modem->mqtt_connect(0, "tcp://broker.example.com:1883", 60, true) == command_result::OK) {
                ESP_LOGI(TAG, "MQTT connected");

                // Subscribe
                modem->mqtt_subscribe(0, "test/topic", MqttQos::AT_LEAST_ONCE);

                // Publish
                modem->mqtt_publish(0, "status/online", "ESP32 online",
                                   MqttQos::AT_LEAST_ONCE, 30, false);

                // Disconnect
                modem->mqtt_disconnect(0);
                modem->mqtt_rel(0);
            }
        }

        modem->mqtt_stop();
    }

    ESP_LOGI(TAG, "Example completed");
    vTaskDelete(NULL);
}

extern "C" void app_main(void)
{
    xTaskCreate(a7670e_example_task, "a7670e_example", 8192, NULL, 5, NULL);
}

