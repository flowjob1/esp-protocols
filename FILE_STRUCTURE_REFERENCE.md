# A7670E Component - File Structure Documentation

## Complete Component Layout

```
esp-protocols/components/a7670e_modem/
│
├── README.md                           # Main documentation with usage examples
├── CHANGELOG.md                        # Release history and version notes
├── CONTRIBUTING.md                     # Developer guidelines
├── INTEGRATION_GUIDE.md                # Step-by-step integration instructions
├── LICENSE                             # Apache 2.0 license
├── CMakeLists.txt                      # Build configuration
├── Kconfig                             # ESP-IDF menuconfig options
├── idf_component.yml                   # Component manifest (v1.0.0)
├── verify.sh                           # Linux/Mac verification script
├── verify.bat                          # Windows verification script
│
├── include/
│   ├── a7670e_types.hpp               # Type system (enums, structs)
│   ├── a7670e_module.hpp              # Main module class + API
│   └── a7670e_urc_handler.hpp         # URC handler interface
│
├── src/
│   ├── a7670e_module.cpp              # Module init, callbacks, helper functions
│   ├── a7670e_commands_net.cpp        # Network & Packet Domain (Sections 4-5)
│   ├── a7670e_commands_serial.cpp     # Serial Interface (Section 10)
│   ├── a7670e_commands_fs.cpp         # File System & Transmission (Sections 12-13)
│   ├── a7670e_commands_http.cpp       # HTTP(S) Client (Section 16)
│   ├── a7670e_commands_mqtt.cpp       # MQTT(S) - argtopic mode (Section 18)
│   ├── a7670e_commands_ssl.cpp        # SSL/TLS Configuration (Section 19)
│   ├── a7670e_commands_gnss.cpp       # GNSS/GPS (Section 23)
│   ├── a7670e_commands_edrx.cpp       # eDRX Mode (Section 34)
│   └── a7670e_urc_handler.cpp         # URC Processing & Callbacks
│
└── examples/
    └── a7670e_at_only/
        ├── CMakeLists.txt              # Example build configuration
        └── a7670e_at_example.cpp       # Functional example with all features
```

## File Descriptions

### Configuration Files

#### `CMakeLists.txt` (Build System)
- Registers ESP-IDF component
- Lists all source files to compile
- Defines include directories
- Specifies dependencies: esp_modem, esp_event, freertos

**Line Count:** ~11 lines
**Key Exports:** Include path, object files

#### `Kconfig` (ESP-IDF Configuration)
- Adds menuconfig options for component
- `CONFIG_A7670E_MODEM_ENABLED` - Enable/disable module
- `CONFIG_A7670E_URC_TASK_STACK_SIZE` - URC handler stack

**Line Count:** ~10 lines

#### `idf_component.yml` (Component Manifest)
- Declares component version (1.0.0)
- Lists all dependencies
- Sets metadata (category: Connectivity)

**Format:** YAML v1 metadata

### Documentation Files

#### `README.md` (Main Documentation)
**Sections:**
- Features overview
- Requirements
- Architecture diagram
- Basic usage examples
- Complete command reference (50+ commands)
- Important notes & limitations
- Troubleshooting guide
- Example code

**Line Count:** ~400 lines
**Audience:** End users & integrators

#### `INTEGRATION_GUIDE.md` (Setup Instructions)
**Sections:**
- Step-by-step component integration
- UART hardware configuration
- DCE initialization code
- Feature enablement examples
- Hardware connection diagram
- Common problems & solutions
- Advanced configuration (SSL, eDRX, serial)
- Testing checklist

**Line Count:** ~450 lines
**Audience:** Integrators & system developers

#### `CONTRIBUTING.md` (Developer Guide)
**Sections:**
- Code style guidelines
- How to add new AT-commands
- Logging & error handling
- Timeout conventions
- Testing procedures
- MQTT argtopic requirements
- Performance benchmarks
- Debugging tips
- Release process

**Line Count:** ~350 lines
**Audience:** Contributors & maintainers

#### `CHANGELOG.md` (Version History)
**Content:**
- v1.0.0 initial release
- Feature list (50+ commands)
- Known limitations
- Dependencies
- Corrections from v2 specification

**Format:** Keep a Changelog v1.0

#### `LICENSE` (Apache 2.0)
- Standard Apache License text
- Copyright Espressif 2025

### Header Files (Public API)

#### `a7670e_types.hpp` (Type System)
**Size:** ~140 lines
**Content:**
- 9 network enumerations (RegStat, OperatorMode, etc.)
- 8 serial interface enums
- 3 HTTP enums + result struct
- 2 MQTT enums + MqttMessage struct + callbacks
- 4 SSL/TLS enums + SslContext struct
- 2 GNSS enums + GnssPosition struct (18 fields)
- 2 eDRX enums + EDrxParams struct

**Dependencies:** std::string, std::function, std::optional

#### `a7670e_module.hpp` (Module Class Declaration)
**Size:** ~460 lines
**Content:**
- Class A7670E(GenericModule) - inherits from esp_modem
- ~60 public method declarations
- All AT-command methods properly declared
- Callback setter methods (MQTT, GNSS)
- Private helper: send_data_after_prompt()
- URC handler member variable

**Key Methods:**
- Network: creg, cgreg, cereg, cgatt, cgerep, cops
- Serial: baud, icf, ifc, uart_sleep, cmux, urc_port, cfgri, curcd
- File: fs_attri, cftranrx, cftrantx
- HTTP: init, term, set_*, action, read, data_input, post_file
- MQTT: start, stop, accq, rel, ssl_cfg, connect, disconnect, cfg_*, publish, subscribe
- SSL: 10+ configuration methods
- GNSS: power, mode, nmea, info
- eDRX: set, get, rdp

#### `a7670e_urc_handler.hpp` (URC Handler Interface)
**Size:** ~30 lines
**Content:**
- Class A7670eUrcHandler
- void handle() method for raw URC processing
- Callback member variables (MqttMessage, MqttConnLost, GNSS, HTTP, etc.)
- Private methods: handle_line(), parse_gnss_info()

### Implementation Files (Module Logic)

#### `a7670e_module.cpp` (Core Implementation)
**Size:** ~90 lines
**Functions:**
- `init_urc_handler()` - Setup URC handler
- Callback setters: `set_mqtt_message_cb()`, `set_gnss_ready_cb()`, etc.
- `send_data_after_prompt()` - Helper for file/HTTP/MQTT data transfer
- `power_off()` - AT+CPOF with optional mode parameter
- `reset_module()` - AT+CRESET

**Pattern:** Simple AT-commands with 9000ms timeout

#### `a7670e_commands_net.cpp` (Network Commands)
**Size:** ~250 lines
**Commands (7):**
- set_creg() - `AT+CREG=<n>`
- get_creg() - `AT+CREG?` (parses LAC, CI)
- scan_operators() - `AT+COPS=?` (60s timeout, CSV parsing)
- get_operator() - `AT+COPS?`
- set_operator() - `AT+COPS=<mode>[,<fmt>[,<oper>[,<act>]]]`
- set/get_cgreg() - GPRS registration
- set/get_cereg() - LTE registration
- set/get_cgatt() - PS attach/detach
- set/get_cgerep() - Event reporting

**Parsing:** sscanf with string buffer extraction

#### `a7670e_commands_serial.cpp` (Serial Configuration)
**Size:** ~260 lines
**Commands (13):**
- Baudrate: set/get_baud_temp(), set/get_baud_permanent() [IPR, IPREX]
- Framing: set/get_icf() [character format]
- Flow: set/get_ifc() [XON/XOFF, Hardware]
- Sleep: set/get_uart_sleep() [DTR, RX, GPIO modes]
- CMUX: enable_cmux(), get_cmux()
- URC: set/get_urc_port() [UART, MODEM, CMUX ports]
- RI: set/get_cfgri() [ring indicator]
- Delay: set/get_curcd() [URC delay, cache]

**Timeout:** All 9000ms standard

#### `a7670e_commands_fs.cpp` (File System)
**Size:** ~100 lines
**Commands (3):**
- fs_attri() - Query file size (5000ms timeout)
- cftranrx() - Write file with prompt (60000ms)
- cftrantx() - Read file chunked (60000ms, parses DATA blocks)

**Pattern:** Prompt-based data transfer for RX, raw read for TX

#### `a7670e_commands_http.cpp` (HTTP Client)
**Size:** ~300 lines
**Commands (11):**
- Session: http_init(), http_term()
- Config: http_set_url, timeout, content_type, accept, ssl_cfg, user_data, read_mode
- Action: http_action() [GET, POST, HEAD, etc.]
- Data: http_read(), http_read_len(), http_head()
- Payload: http_data_input() [prompt-based]
- File: http_post_file(), http_read_file()

**Timeout:** 120000ms for most operations (slow protocol)

#### `a7670e_commands_mqtt.cpp` (MQTT - argtopic mode)
**Size:** ~310 lines
**Commands (16):**
- Session: mqtt_start(), mqtt_stop() [NO timeout param!]
- Client: mqtt_accq(), mqtt_rel() [NO timeout param!]
- SSL: mqtt_ssl_cfg()
- Connect: mqtt_connect(), mqtt_disconnect()
- Config: mqtt_cfg_argtopic (MANDATORY!), mqtt_cfg_check_utf8, mqtt_cfg_optimeout, mqtt_cfg_version, mqtt_cfg_cid, mqtt_cfg_scid
- Messaging: mqtt_publish() [prompt-based payload], mqtt_subscribe()

**Critical:** argtopic mode MUST be configured after mqtt_accq()

#### `a7670e_commands_ssl.cpp` (SSL/TLS Configuration)
**Size:** ~160 lines
**Commands (10):**
- set_version() - SSL/TLS version
- set_auth_mode() - No/Server/Mutual/Client auth
- set_ignore_time() - Ignore local time
- set_negotiate_timeout() - Timeout in seconds
- set_ca() - CA certificate file
- set_client_cert() - Client certificate
- set_client_key() - Client private key
- set_password() - Certificate password
- set_sni() - SNI enabled/disabled
- set_ignore_cn() - Ignore CN checking
- ssl_cfg_get() - Read ALL settings

**Pattern:** All use `AT+CSSLCFG="<key>",<ctx_id>,<value>`

#### `a7670e_commands_gnss.cpp` (GNSS/GPS)
**Size:** ~130 lines
**Commands (6):**
- gnss_power() - Power on/off (9000ms)
- gnss_mode_set/get() - Select sattelite system
- gnss_nmea_set/get() - Configure NMEA sentences
- gnss_info() - Get current position (parses 18 fields)
- gnss_info_periodic() - Periodic updates

**Parsing:** Full GnssPosition struct with 14+ fields

#### `a7670e_commands_edrx.cpp` (eDRX Mode)
**Size:** ~75 lines
**Commands (3):**
- edrx_set() - Enable with mode & parameters
- edrx_get() - Read current config
- edrx_rdp() - Read dynamic parameters

**Modes:** Not using, EC-GSM-IoT, GSM, UTRAN, LTE WB, LTE NB

#### `a7670e_urc_handler.cpp` (URC Processing)
**Size:** ~180 lines
**Functions:**
- handle() - Main entry point (splits by lines)
- handle_line() - Process single line (30+ URC types)
- parse_gnss_info() - Parse 18-field GNSS response

**URCs Handled:**
- MQTT: CMQTTRECV (single-line argtopic), CMQTTSTART, CMQTTCONNECT, CMQTTDISC, CMQTTCONNLOST
- GNSS: CGNSSPWR READY, CGNSSINFO
- HTTP: HTTPACTION, HTTPPOSTFILE, HTTPREADFILE
- Network: CGEV, NETOPEN, HTTP_PEER_CLOSED, HTTP_NONET_EVENT

### Example Application

#### `examples/a7670e_at_only/CMakeLists.txt`
- Registers example component
- Links to a7670e_modem + esp_modem

#### `examples/a7670e_at_only/a7670e_at_example.cpp`
**Size:** ~180 lines
**Demonstrates:**
1. DCE creation (module-only, netif=nullptr)
2. URC handler initialization
3. Module reset & basic AT commands
4. Network registration check
5. PS Attach & CGATT
6. Baudrate queries
7. URC port setup
8. MQTT with callbacks & argtopic
9. HTTP operations
10. GNSS with callbacks
11. File operations

**Task:** FreeRTOS task running sequentially

## Implementation Statistics

### Code Size Summary

| Component | Files | Lines | Purpose |
|-----------|-------|-------|---------|
| Types | 1 | 140 | Enums & Structs |
| Headers | 2 | 490 | Module API + URC |
| Commands | 9 | 1,700 | AT-command implementation |
| URC | 1 | 180 | Async message processing |
| Documentation | 6 | 2,100 | Integration guides |
| Examples | 1 | 180 | Working example |
| **TOTAL** | **20** | **~4,800** | **Full component** |

### Command Implementation

| Category | Count | Status |
|----------|-------|--------|
| Network | 8 | ✅ Complete |
| Packet Domain | 4 | ✅ Complete |
| Serial | 13 | ✅ Complete |
| File System | 3 | ✅ Complete |
| HTTP | 11 | ✅ Complete|
| MQTT | 16 | ✅ Complete |
| SSL | 10 | ✅ Complete |
| GNSS | 6 | ✅ Complete |
| eDRX | 3 | ✅ Complete |
| Status Control | 2 | ✅ Complete |
| **TOTAL** | **76** | **✅ Implemented** |

## Next Steps for Users

1. **Copy component** to Espressif IDF project
2. **Customize UART pins** in CMakeLists.txt or app code
3. **Review INTEGRATION_GUIDE.md** for setup
4. **Run example** to validate
5. **Integrate into application**

## Maintenance

- Update CHANGELOG.md for each change
- Follow CONTRIBUTING.md guidelines
- Run verify.sh/verify.bat before commits
- Keep documentation synchronized with code

