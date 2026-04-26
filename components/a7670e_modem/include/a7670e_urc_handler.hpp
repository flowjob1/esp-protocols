#pragma once
#include "a7670e_types.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <cstdint>

namespace a7670e {

class A7670eUrcHandler {
public:
    A7670eUrcHandler() = default;
    ~A7670eUrcHandler() = default;

    void handle(uint8_t *data, size_t len);
    size_t handle_buffer(std::string_view buffer, bool command_active);

    // Callbacks (von A7670E::set_*_cb() gesetzt)
    MqttMessageCb  on_mqtt_message;
    MqttConnLostCb on_mqtt_conn_lost;
    std::function<void(int err)>                   on_mqtt_start;
    std::function<void(int idx, int err)>           on_mqtt_connect;
    std::function<void(int idx, int err)>           on_mqtt_disconnect;
    std::function<void()>                           on_gnss_ready;
    std::function<void(const GnssPosition&)>        on_gnss_info;
    std::function<void(HttpActionResult)>           on_http_action;
    std::function<void(int errcode)>                on_http_read_file;

private:
    bool is_async_only_urc(std::string_view line) const;
    bool handle_line(std::string_view line);
    GnssPosition parse_gnss_info(const std::string &payload);
};

} // namespace a7670e
