# Changelog

## [1.0.0] - 2025-04-25

### Added
- Initial release of A7670E custom esp_modem module
- AT-command interface for SIMCom A7670E LTE modem
- Module-only architecture (no PPP support)
- Network management (CREG, CGREG, CEREG, CGATT)
- Operator scanning and selection (COPS)
- Serial interface configuration (baudrate, flow control, sleep modes)
- File system operations (FSATTRI, CFTRANRX, CFTRANTX)
- HTTP(S) client with SSL integration
- MQTT(S) with argtopic mode (mandatory configuration)
- Complete SSL/TLS context configuration
- GNSS/GPS support with position tracking
- eDRX (Extended Discontinuous Reception) mode
- Asynchronous URC handling with callbacks
- Type-safe enums and structures for all parameters
- Comprehensive URC parsing for all supported messages
- Full error handling and timeout management
- Example application demonstrating all features
- Complete documentation and API reference

### Implementation Details
- 10 command implementation files (net, serial, fs, http, mqtt, ssl, gnss, edrx, module, urc)
- 3 header files with complete API definitions
- 1 URC handler with callback support
- argtopic-mode mandatory MQTT support with inline topic/payload
- Prompt-based data transfer for HTTP and file operations
- Chunked file transfer support with location-based reads
- All 50+ AT-commands fully implemented
- Type system with 15+ enumerations and 8+ data structures

### Known Limitations
- MQTT requires argtopic mode to be configured before connection
- AT+CMQTTREL and AT+CMQTTSTOP do not accept timeout parameters
- Operator scan has 60-second timeout
- File chunk size recommended ≤475 bytes
- CMUX not recommended for normal operation
- URC callbacks execute in DTE event loop (must be thread-safe)

### Dependencies
- esp_modem >= 1.1.0
- esp_event (required)
- freertos (required)
- ESP-IDF >= v5.2

### Testing
- Syntax validation completed
- Type checking passed
- Build configuration tested
- Example application provided for validation

### Documentation
- README.md with usage examples
- Inline API documentation in headers
- Example code with all major features
- Troubleshooting guide
- Command reference table

---

## Version Comparison

### v2 Corrections (from Testing)
- **MQTT Publish**: argtopic format with topic inline
- **MQTT Subscribe**: Topic inline, no separate topic command
- **MQTT Receive URC**: Single-line `+CMQTTRECV:` format (not multi-line CMQTTRXSTART/TOPIC/PAYLOAD/END)
- **File Transfer**: CFTRANTX includes transMode parameter
- **CMQTTREL/CMQTTSTOP**: No timeout parameter (ERROR if provided)
- **Filesystem**: Reduced to FSATTRI + CFTRANRX + CFTRANTX only

### v1 Notes (Legacy)
- Previous version had different MQTT architecture
- Multi-part MQTT RX sequence (deprecated)
- No argtopic mode support

