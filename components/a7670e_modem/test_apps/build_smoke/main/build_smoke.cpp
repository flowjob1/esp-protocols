#include "a7670e_module.hpp"
#include "driver/uart.h"
#include "esp_modem_config.h"

using namespace esp_modem;
using namespace a7670e;

extern "C" void app_main(void)
{
    esp_modem_dte_config_t dte_config = ESP_MODEM_DTE_DEFAULT_CONFIG();
    dte_config.uart_config.port_num = UART_NUM_1;
    dte_config.uart_config.baud_rate = 115200;

    esp_modem_dce_config_t dce_config = ESP_MODEM_DCE_DEFAULT_CONFIG("");

    auto factory_fn = &create_a7670e_dce;
    (void)factory_fn;
    (void)dte_config;
    (void)dce_config;
}
