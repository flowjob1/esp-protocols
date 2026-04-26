#include "a7670e_module.hpp"
#include "cxx_include/esp_modem_api.hpp"
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_modem_config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <inttypes.h>

using namespace esp_modem;
using namespace a7670e;

static const char *TAG = "A7670E_EXAMPLE";

void a7670e_example_task(void *pv_parameters)
{
    (void)pv_parameters;

    esp_modem_dte_config_t dte_config = ESP_MODEM_DTE_DEFAULT_CONFIG();
    dte_config.uart_config.port_num = UART_NUM_2;
    dte_config.uart_config.tx_io_num = 4;
    dte_config.uart_config.rx_io_num = 5;
    dte_config.uart_config.rts_io_num = 6;
    dte_config.uart_config.cts_io_num = 7;
    dte_config.uart_config.baud_rate = 115200;
    dte_config.uart_config.flow_control = ESP_MODEM_FLOW_CONTROL_HW;
    dte_config.dte_buffer_size = 2048;
    dte_config.task_stack_size = 4096;

    esp_modem_dce_config_t dce_config = ESP_MODEM_DCE_DEFAULT_CONFIG("");

    auto dce = create_a7670e_dce(&dce_config, &dte_config);
    if (!dce) {
        ESP_LOGE(TAG, "Failed to create A7670E DCE");
        vTaskDelete(nullptr);
        return;
    }

    auto *modem = static_cast<A7670E *>(dce->get_module());
    if (!modem) {
        ESP_LOGE(TAG, "Failed to access A7670E module");
        vTaskDelete(nullptr);
        return;
    }

    modem->set_mqtt_message_cb([](const MqttMessage &msg) {
        ESP_LOGI(TAG, "MQTT message topic=%s payload=%s qos=%d", msg.topic.c_str(), msg.payload.c_str(), msg.qos);
    });
    modem->set_gnss_ready_cb([]() {
        ESP_LOGI(TAG, "GNSS ready");
    });
    modem->set_gnss_info_cb([](const GnssPosition &pos) {
        if (pos.valid) {
            ESP_LOGI(TAG, "GNSS lat=%.6f%c lon=%.6f%c alt=%.1f", pos.lat, pos.ns, pos.lon, pos.ew, pos.alt_m);
        }
    });

    int creg_mode = 0;
    RegStat creg_stat = RegStat::UNKNOWN;
    std::string lac;
    std::string ci;
    if (modem->get_creg(creg_mode, creg_stat, lac, ci) == command_result::OK) {
        ESP_LOGI(TAG, "CREG n=%d stat=%d lac=%s ci=%s", creg_mode, static_cast<int>(creg_stat), lac.c_str(), ci.c_str());
    }

    BaudRate baud = BaudRate::B115200;
    if (modem->get_baud_temp(baud) == command_result::OK) {
        ESP_LOGI(TAG, "Current baud rate=%" PRIu32, static_cast<uint32_t>(baud));
    }

    FsAttriResult fs_result{};
    if (modem->fs_attri("ca_cert.pem", fs_result) == command_result::OK) {
        ESP_LOGI(TAG, "ca_cert.pem size=%" PRIu64, fs_result.size_bytes);
    }

    if (modem->http_init() == command_result::OK) {
        ESP_LOGI(TAG, "HTTP initialized");
        modem->http_set_url("http://example.com/status");
        HttpActionResult http_result{};
        if (modem->http_action(HttpMethod::GET, http_result) == command_result::OK) {
            ESP_LOGI(TAG, "HTTP status=%d length=%d", http_result.status_code, http_result.data_len);
        }
        modem->http_term();
    }

    if (modem->mqtt_start() == command_result::OK) {
        ESP_LOGI(TAG, "MQTT started");
        if (modem->mqtt_accq(0, "ESP32-A7670E", MqttServerType::TCP) == command_result::OK &&
                modem->mqtt_cfg_argtopic(0, 1, 1) == command_result::OK &&
                modem->mqtt_cfg_version(0, 4) == command_result::OK &&
                modem->mqtt_connect(0, "tcp://broker.example.com:1883", 60, true) == command_result::OK) {
            modem->mqtt_subscribe(0, "test/topic", MqttQos::AT_LEAST_ONCE);
            modem->mqtt_publish(0, "status/online", "ESP32 online", MqttQos::AT_LEAST_ONCE, 30, false);
            modem->mqtt_disconnect(0);
            modem->mqtt_rel(0);
        }
        modem->mqtt_stop();
    }

    ESP_LOGI(TAG, "A7670E example finished");
    vTaskDelete(nullptr);
}

extern "C" void app_main(void)
{
    xTaskCreate(a7670e_example_task, "a7670e_example", 8192, nullptr, 5, nullptr);
}
