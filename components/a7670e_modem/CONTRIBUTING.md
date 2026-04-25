# Contributing to A7670E Module

## Development Guidelines

### Code Style

- **C++ Standard:** C++14 minimum, C++17 recommended
- **Formatting:** OTBS style (Allman variant), 4-space indentation
- **Naming:** camelCase for methods/variables, UPPERCASE for constants
- **Documentation:** Doxygen-style comments recommended

### Adding New Commands

When adding new AT-commands to the module:

1. **Define Types** (`a7670e_types.hpp`):
   ```cpp
   enum class NewMode : int { VALUE1=0, VALUE2=1 };
   struct NewResult { int status; std::string data; };
   ```

2. **Declare Method** (`a7670e_module.hpp`):
   ```cpp
   esp_modem::command_result new_command(int param, NewResult &result);
   ```

3. **Implement** (`a7670e_commands_*.cpp`):
   ```cpp
   CR A7670E::new_command(int param, NewResult &result) {
       std::string cmd = "AT+NEWCMD=" + std::to_string(param) + "\r";
       return command(cmd, [&](uint8_t *d, size_t l) -> CR {
           std::string_view r(reinterpret_cast<char*>(d), l);
           auto pos = r.find("+NEWCMD:");
           if (pos != std::string_view::npos) {
               int status;
               sscanf(r.data() + pos, "+NEWCMD: %d", &status);
               result.status = status;
           }
           if (r.find("OK")    != std::string_view::npos) return CR::OK;
           if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
           return CR::AGAIN;
       }, 9000);  // timeout
   }
   ```

4. **Add URC Handler** (if async response) in `a7670e_urc_handler.cpp`:
   ```cpp
   if (line.find("+NEWCMD_URC:") != std::string::npos) {
       if (on_new_handler) {
           // Parse and call callback
       }
       return;
   }
   ```

5. **Update Documentation:**
   - Add to README.md Command Reference
   - Add to appropriate section in INTEGRATION_GUIDE.md
   - Update CHANGELOG.md

### Logging & Error Handling

- Use `ESP_LOGI/LOGE` from esp_log
- Return `command_result::FAIL` for errors
- Never throw exceptions, use error codes

### Timeouts

Common timeout values (in milliseconds):
- **9000 ms** - Standard commands (queries, set operations)
- **5000 ms** - Quick operations (file checks, config)
- **60000 ms** - Slow operations (operator scan, HTTP, MQTT connect)
- **120000 ms** - Very slow operations (HTTP downloads, large file transfers)

### Testing Guidelines

Before submitting changes:

1. **Compile without errors:**
   ```bash
   idf.py build
   ```

2. **Test with real hardware** if possible

3. **Verify with example code:**
   ```cpp
   auto res = modem->new_command(param, result);
   assert(res == command_result::OK);
   ```

4. **Check memory usage:**
   - Avoid dynamic allocations in hot paths
   - Use string_view for parsing

5. **Ensure thread-safety:**
   - `command()` is internally serialized (mutex)
   - Callbacks run in DTE thread - keep them short

### MQTT argtopic Mode

When working with MQTT commands:

- **Always** configure argtopic after `mqtt_accq()`:
  ```cpp
  mqtt_accq(idx, id, type);
  mqtt_cfg_argtopic(idx, 1, 1);  // MANDATORY
  ```

- URC format is **single-line**:
  ```
  +CMQTTRECV: <idx>,"<topic>",<qos>,"<payload>"
  ```

- NOT multi-part (deprecated):
  ```
  +CMQTTRXSTART: ...
  +CMQTTTOPIC: ...
  +CMQTTPAYLOAD: ...
  +CMQTTRXEND:
  ```

### File Transfer Best Practices

- Use `fs_attri()` before transfer to verify file size
- Keep chunk size ≤ 475 bytes for safety
- For large files, use multiple `cftrantx()` calls with location offsets
- Always check return values for FAIL status

### Performance Considerations

1. **Network Commands:**
   - Batch related operations
   - Use efficient scanning (scan_operators has 60s timeout)
   - Cache operator information

2. **HTTP/MQTT:**
   - Reuse SSL contexts
   - Connection pooling recommended
   - Buffer management for large payloads

3. **GNSS:**
   - Allow 2+ minutes for cold start
   - Use callbacks for position updates
   - Disable when not needed (power saving)

4. **File Operations:**
   - Close files immediately after use
   - Use chunked reads for large files
   - Verify checksums if critical

### Documentation

**Code Comments:**
```cpp
// Describes WHAT and WHY, not HOW
// Use Doxygen style for public APIs:
/**
 * @brief Set the MQTT topic
 * @param[in] idx MQTT client index
 * @param[in] topic Topic string (max 512 chars)
 * @return command result (OK if successful)
 */
```

**Commit Messages:**
```
[component] Brief description (50 chars max)

Detailed explanation of changes (wrap at 72 chars):
- What was changed
- Why it was necessary
- Any breaking changes
```

**PR Description Template:**
```markdown
## Changes
- List of modifications

## Testing
- How was this tested
- Any limitations

## Impact
- Performance impact
- Memory impact
- Compatibility impact
```

### Backwards Compatibility

- Never remove public methods without deprecation notice
- When changing signatures, provide deprecated wrapper
- Document API changes in CHANGELOG
- Support older module firmware if possible

### Performance Benchmarks

Key metrics to consider:

| Operation | Target | Notes |
|-----------|--------|-------|
| MQTT Connect | <5000ms | Depends on network |
| HTTP GET | <10000ms | Depends on bandwidth |
| File Write | <1000ms per 100B | USB2 UART speed limited |
| GNSS Fix | <120000ms | Cold start with clear sky |
| Network Register | <30000ms | Depends on coverage |

## Repository Structure

```
a7670e_modem/
├── include/
│   ├── a7670e_types.hpp           # Type system
│   ├── a7670e_module.hpp          # Main API
│   └── a7670e_urc_handler.hpp     # URC handling
├── src/
│   ├── a7670e_module.cpp          # Core implementation
│   ├── a7670e_commands_*.cpp      # Command groups
│   └── a7670e_urc_handler.cpp     # URC processing
├── examples/
│   └── a7670e_at_only/            # Complete example
├── CMakeLists.txt
├── Kconfig
├── README.md
├── INTEGRATION_GUIDE.md
├── CHANGELOG.md
└── LICENSE
```

## Debugging Tips

### Enable verbose logging:
```cpp
esp_log_level_set("A7670E", ESP_LOG_DEBUG);
esp_log_level_set("esp_modem_dce", ESP_LOG_DEBUG);
```

### Monitor AT commands:
```cpp
// Add to DTE handler or use serial monitor
ESP_LOGI(TAG, "TX: %s", command.c_str());
```

### Check response parsing:
```cpp
std::string_view resp(reinterpret_cast<char*>(data), len);
ESP_LOGI(TAG, "RX: %.*s", (int)resp.size(), resp.data());
```

### Memory leak detection:
```cpp
heap_trace_start(HEAP_TRACE_ALLOC);
// ... run your code ...
heap_trace_stop();
heap_trace_dump(stdout);
```

## Release Process

1. Update `a7670e_types.hpp` version if needed
2. Update CHANGELOG.md with all changes
3. Run full test suite
4. Get code review from maintainers
5. Update documentation
6. Tag release in git

## Contact & Support

- GitHub Issues: Report bugs and feature requests
- Discussions: General questions and discussion
- Pull Requests: Submit improvements

---

Thank you for contributing to the A7670E module!

