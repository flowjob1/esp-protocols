# A7670E Custom Modem Module

Custom esp_modem module for SIMCom A7670E LTE modem with advanced AT-command interface support.

## Features

- **AT-Command Interface Only**: No PPP support, designed for simple AT command operations
- Complete Network Management (registration, operator selection, packet domain)
- Serial Interface Configuration (baudrate, flow control, UART sleep modes)
- File System Operations (read/write files to device EFS)
- HTTP(S) Client Operations
- MQTT(S) Support with argtopic mode (inline topic/payload)
- SSL/TLS Configuration
- GNSS/GPS Support with URC callbacks
- eDRX (Extended Discontinuous Reception)
- Asynchronous URC Handling

## Requirements

- ESP-IDF >= v5.2
- esp_modem component >= 1.1.0
- esp_event component
- FreeRTOS

## Architecture

The module is implemented as a "module-only" variant without PPP support:

```
DCE created with netif=nullptr
└── A7670E (GenericModule)
    └── Custom Commands (Network, Serial, HTTP, MQTT, etc.)
    └── URC Handler (async message processing)
```

## Usage

### Basic Initialization

```cpp
#include "a7670e_module.hpp"

using namespace a7670e;

// Create DTE and DCE
auto uart_dte = create_uart_dte(&dte_cfg);
auto dce = dce_factory::Factory::create_unique_dce_from<A7670E>(&dce_cfg, uart_dte, nullptr);

// Get module and initialize URC handler
auto *modem = static_cast<A7670E*>(dce->get_module());
modem->init_urc_handler(uart_dte);
```

### Network Operations

```cpp
// Set URC port
modem->set_urc_port(UrcPort::UART);

// Check registration
RegStat stat;
int n;
std::string lac, ci;
modem->get_creg(n, stat, lac, ci);

// Attach to PS domain
modem->set_cgatt(1);
```

### MQTT with argtopic Mode

```cpp
// Mandatory: Configure argtopic mode after mqtt_accq()
modem->mqtt_start();
modem->mqtt_accq(0, "device-id", MqttServerType::SSL_TLS);
modem->mqtt_cfg_argtopic(0, 1, 1);  // CRITICAL!
modem->mqtt_cfg_version(0, 4);

// Configure SSL
modem->ssl_cfg_set_auth_mode(0, SslAuthMode::SERVER_AUTH);
modem->ssl_cfg_set_ca(0, "ca_cert.pem");

// Connect and use
modem->mqtt_connect(0, "tcp://broker:8883", 60, true, "user", "pass");
modem->mqtt_subscribe(0, "topic/#", MqttQos::AT_LEAST_ONCE);
modem->mqtt_publish(0, "status", "online", MqttQos::AT_LEAST_ONCE, 30);
```

### File Operations

```cpp
// Check file size
FsAttriResult result;
modem->fs_attri("ca_cert.pem", result);

// Write file to device
std::string cert_data = "...";
modem->cftranrx("ca_cert.pem", cert_data);

// Read file from device
std::string read_data;
modem->cftrantx("ca_cert.pem", read_data);
```

### URC Callbacks

```cpp
// MQTT Message callback
modem->set_mqtt_message_cb([](const MqttMessage &msg) {
    printf("Topic: %s, Payload: %s\n", msg.topic.c_str(), msg.payload.c_str());
});

// GNSS callbacks
modem->set_gnss_ready_cb([]() {
    printf("GNSS ready!\n");
});

modem->set_gnss_info_cb([](const GnssPosition &pos) {
    if (pos.valid) {
        printf("Position: %.6f, %.6f\n", pos.lat, pos.lon);
    }
});
```

## Command Reference

### Status Control
- `power_off(mode)` - Power off modem
- `reset_module()` - Reset modem

### Network
- `set/get_creg(n)` - Circuit switched registration
- `set/get_cgreg(n)` - GPRS registration
- `set/get_cereg(n)` - LTE registration
- `scan_operators(ops)` - Scan available operators
- `get/set_operator(mode, fmt, oper, act)` - Operator selection

### Packet Domain
- `set/get_cgatt(state)` - GPRS attach
- `set/get_cgerep(mode, bfr)` - GPRS event reporting

### Serial Interface
- `set/get_baud_temp/permanent(speed)` - Baudrate control
- `set/get_icf(format, parity)` - Character framing
- `set/get_ifc(dce_flow, dte_flow)` - Flow control
- `set/get_uart_sleep(mode)` - UART sleep mode
- `set/get_urc_port(port)` - URC output port

### File System
- `fs_attri(filename, result)` - Get file size
- `cftranrx(filepath, data, location)` - Write file
- `cftrantx(filepath, out, location, size, trans_mode)` - Read file

### HTTP
- `http_init/term()` - Initialize/terminate HTTP
- `http_set_url/content_type/ssl_cfg()` - Configure HTTP
- `http_action(method, result)` - Execute HTTP request
- `http_read(start, len, data)` - Read response data
- `http_data_input(data, timeout)` - Send POST data

### MQTT
- `mqtt_start/stop()` - MQTT session start/stop
- `mqtt_accq(idx, id, type)` - Acquire client
- `mqtt_connect/disconnect()` - Connection management
- `mqtt_cfg_argtopic()` - **MANDATORY before connect!**
- `mqtt_subscribe/publish()` - Message operations

### SSL
- `ssl_cfg_set_version/auth_mode/ca()` - SSL configuration
- `ssl_cfg_set_sni/ignore_cn()` - Advanced SSL options

### GNSS
- `gnss_power(power)` - Power on/off
- `gnss_mode_set/get(mode)` - GNSS mode
- `gnss_info/info_periodic()` - Position information

### eDRX
- `edrx_set/get()` - eDRX configuration
- `edrx_rdp()` - Read eDRX parameters

## Important Notes

1. **argtopic-Modus**: MQTT requires `mqtt_cfg_argtopic()` to be called after `mqtt_accq()` and before `mqtt_connect()`. Without this, MQTT commands will fail or behave unexpectedly.

2. **AT+CMQTTREL/AT+CMQTTSTOP**: These commands do NOT accept timeout parameters. Sending `AT+CMQTTREL=0,20` will return ERROR.

3. **Operator Scan**: `scan_operators()` has a 60-second timeout. No other commands should be sent during the scan.

4. **File Operations**: `cftrantx()` may need multiple calls for large files. Use chunked reads with `location` and `size` parameters.

5. **URC Handling**: URC callbacks are executed in the DTE's event loop. Keep callbacks short and thread-safe.

## Examples

See `examples/a7670e_at_only/` for a complete working example.

## Troubleshooting

### Commands return ERROR
- Verify AT-command is correctly formatted
- Check module is in correct state (e.g., registered for network commands)
- Ensure URC port is set correctly: `set_urc_port(UrcPort::UART)`

### MQTT not working
- Verify argtopic mode is configured: `mqtt_cfg_argtopic(idx, 1, 1)` BEFORE connect
- Check SSL configuration if using TLS
- Ensure network is attached: `set_cgatt(1)`

### File transfer fails
- Verify file size with `fs_attri()` first
- Use chunked transfers for large files
- Ensure EFS has sufficient space

### GNSS not getting fixes
- Require outdoor positioning with clear sky view
- May take 2+ minutes for first fix (GPS cold start)
- Verify power is on: `gnss_power(1)`
- Check NMEA sentence output: `gnss_nmea_get()`

## License

See top-level LICENSE file

