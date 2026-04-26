#include <memory>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include "LoopbackTerm.h"
#include "a7670e_module.hpp"
#include "a7670e_urc_handler.hpp"
#include "cxx_include/esp_modem_dce_factory.hpp"

using namespace esp_modem;
using namespace a7670e;

namespace {

std::unique_ptr<DCE> make_a7670e_dce(LoopbackTerm *&loopback)
{
    auto term = std::make_unique<LoopbackTerm>();
    loopback = term.get();
    auto dte = std::make_shared<DTE>(std::move(term));
    esp_modem_dce_config_t dce_config = ESP_MODEM_DCE_DEFAULT_CONFIG("APN");
    return dce_factory::Factory::create_unique_dce_from<A7670E>(&dce_config, dte, nullptr);
}

void inject_response(LoopbackTerm *loopback, const std::string &response, size_t chunk_size = 4)
{
    REQUIRE(loopback != nullptr);
    loopback->inject(reinterpret_cast<uint8_t *>(const_cast<char *>(response.data())), response.size(), chunk_size, 0, 0);
}

} // namespace

TEST_CASE("A7670E HTTP helpers parse binary-safe payloads", "[a7670e][http]")
{
    LoopbackTerm *loopback = nullptr;
    auto dce = make_a7670e_dce(loopback);
    REQUIRE(dce != nullptr);
    auto *modem = static_cast<A7670E *>(dce->get_module());
    REQUIRE(modem != nullptr);

    const std::string header = "Content-Type: text/plain\r\nX-Test: 1\r\n";
    inject_response(loopback, "+HTTPHEAD: " + std::to_string(header.size()) + "\r\n" + header + "OK\r\n", 3);

    std::string header_out;
    CHECK(modem->http_head(header_out) == command_result::OK);
    CHECK(header_out == header);

    const std::string body = "ABC\n123";
    inject_response(loopback, "+HTTPREAD: " + std::to_string(body.size()) + "\r\n" + body + "+HTTPREAD: 0\r\nOK\r\n", 2);

    std::string body_out;
    CHECK(modem->http_read(0, static_cast<int>(body.size()), body_out) == command_result::OK);
    CHECK(body_out == body);
}

TEST_CASE("A7670E CFTRANTX accumulates all data blocks once", "[a7670e][fs]")
{
    LoopbackTerm *loopback = nullptr;
    auto dce = make_a7670e_dce(loopback);
    REQUIRE(dce != nullptr);
    auto *modem = static_cast<A7670E *>(dce->get_module());
    REQUIRE(modem != nullptr);

    const std::string response =
        "+CFTRANTX: DATA,4\r\nABCD"
        "+CFTRANTX: DATA,3\r\nEFG"
        "+CFTRANTX: 0\r\nOK\r\n";
    inject_response(loopback, response, 3);

    std::string out;
    CHECK(modem->cftrantx("C:/test.txt", out, 0, 7, 0) == command_result::OK);
    CHECK(out == "ABCDEFG");
}

TEST_CASE("A7670E GNSS parsing accepts no-fix and sparse fix replies", "[a7670e][gnss]")
{
    LoopbackTerm *loopback = nullptr;
    auto dce = make_a7670e_dce(loopback);
    REQUIRE(dce != nullptr);
    auto *modem = static_cast<A7670E *>(dce->get_module());
    REQUIRE(modem != nullptr);

    inject_response(loopback, "+CGNSSINFO: ,,,,,,,,\r\nOK\r\n", 5);
    GnssPosition no_fix{};
    CHECK(modem->gnss_info(no_fix) == command_result::OK);
    CHECK_FALSE(no_fix.valid);

    inject_response(loopback,
                    "+CGNSSINFO: 3,10,00,,00,48.5393715,N,12.1240492,E,250426,095854.00,482.0,1.203,,6.02,3.51,4.88,04\r\nOK\r\n",
                    7);
    GnssPosition fix{};
    CHECK(modem->gnss_info(fix) == command_result::OK);
    CHECK(fix.valid);
    CHECK(fix.mode == 3);
    CHECK(fix.gps_svs == 10);
    CHECK(fix.glonass_svs == 0);
    CHECK(fix.num_sv == 4);
    CHECK(fix.date == "250426");
    CHECK(fix.utc == "095854.00");
}

TEST_CASE("A7670E URC handler parses MQTT URCs with empty payload", "[a7670e][urc]")
{
    A7670eUrcHandler handler;
    MqttMessage received{};
    bool called = false;
    handler.on_mqtt_message = [&](const MqttMessage &msg) {
        received = msg;
        called = true;
    };

    const std::string buffer = "+CMQTTRECV: 0,\"cmd/cancel_overrides/set\",0,\"\"\r\nOK\r\n";
    const auto consumed = handler.handle_buffer(buffer, true);

    CHECK(called);
    CHECK(consumed > 0);
    CHECK(consumed < buffer.size());
    CHECK(received.client_index == 0);
    CHECK(received.topic == "cmd/cancel_overrides/set");
    CHECK(received.qos == 0);
    CHECK(received.payload.empty());
}
