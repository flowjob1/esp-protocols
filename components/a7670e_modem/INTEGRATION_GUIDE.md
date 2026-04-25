# Integration Guide - A7670E Custom Module

## Schritt-für-Schritt Integration

### 1. Komponente hinzufügen

Die Komponente `a7670e_modem` ist bereits im Verzeichnis:
```
esp-protocols/components/a7670e_modem/
```

### 2. In Projekt-CMakeLists.txt hinzufügen

In der `CMakeLists.txt` des Test-Projekts REQUIRES hinzufügen:

```cmake
idf_component_register(
    SRCS "your_main.cpp"
    REQUIRES esp_modem a7670e_modem  # ← a7670e_modem hinzufügen
)
```

### 3. UART-Hardware konfigurieren

Beispiel-Konfiguration in `main.cpp`:

```cpp
#include "sdkconfig.h"
#include "a7670e_module.hpp"

// UART-Konfiguration anpassen nach Hardware:
dte_config dte_cfg{};
dte_cfg.port_num = 2;          // UART2
dte_cfg.tx_io_num = 4;         // GPIO4 → TX
dte_cfg.rx_io_num = 5;         // GPIO5 → RX
dte_cfg.rts_io_num = 6;        // GPIO6 → RTS (optional)
dte_cfg.cts_io_num = 7;        // GPIO7 → CTS (optional)
dte_cfg.baud_rate = 115200;
dte_cfg.flow_control = esp_modem::flow_control::HW;
dte_cfg.task_stack_size = 4096;
```

### 4. DCE erstellen

```cpp
using namespace esp_modem;
using namespace a7670e;

// DTE + DCE erstellen (AT-only, netif=nullptr)
auto uart_dte = create_uart_dte(&dte_cfg);

dce_config dce_cfg{};
dce_cfg.dte = uart_dte;

auto dce = dce_factory::Factory::create_unique_dce_from<A7670E>(
    &dce_cfg, uart_dte, nullptr);

auto *modem = static_cast<A7670E*>(dce->get_module());
modem->init_urc_handler(uart_dte);
```

### 5. Initialisierungssequenz

Empfohlene Initialisierung (nach AT-Datablatt):

```cpp
// 1. Reset
modem->reset_module();
vTaskDelay(pdMS_TO_TICKS(1000));

// 2. URC-Port
modem->set_urc_port(UrcPort::UART);

// 3. GPRS-Events
modem->set_cgerep(CgerepMode::BUFFER_IF_BUSY, CgerepBfr::FLUSH);

// 4. Echo deaktivieren (falls vorhanden)
// modem->set_echo(false);  // Falls GenericModule Methode


// 5. PS-Attach
modem->set_cgatt(1);

// 6. Netzwerk-Status prüfen
RegStat stat;
int n;
std::string lac, ci;
modem->get_creg(n, stat, lac, ci);
ESP_LOGI(TAG, "Registration status: %d", static_cast<int>(stat));
```

### 6. Funktionalität aktivieren

**Für MQTT:**
```cpp
modem->mqtt_start();
modem->mqtt_accq(0, "device-id", MqttServerType::TCP);
modem->mqtt_cfg_argtopic(0, 1, 1);  // CRITICAL!
modem->mqtt_connect(0, "tcp://broker:1883", 60, true);

modem->set_mqtt_message_cb([](const MqttMessage &msg) {
    ESP_LOGI(TAG, "MQTT: %s = %s", msg.topic.c_str(), msg.payload.c_str());
});

modem->mqtt_subscribe(0, "topic/#", MqttQos::AT_LEAST_ONCE);
```

**Für GNSS:**
```cpp
modem->set_gnss_ready_cb([]() {
    ESP_LOGI(TAG, "GNSS ready");
});

modem->set_gnss_info_cb([](const GnssPosition &pos) {
    if (pos.valid) {
        ESP_LOGI(TAG, "Lat=%.6f Lon=%.6f", pos.lat, pos.lon);
    }
});

modem->gnss_power(1);
modem->gnss_mode_set(GnssMode::GPS_BDS);
```

**Für HTTP:**
```cpp
modem->http_init();
modem->http_set_url("https://api.example.com/status");
modem->http_set_ssl_cfg(0);
HttpActionResult result;
modem->http_action(HttpMethod::GET, result);
ESP_LOGI(TAG, "HTTP Status: %d", result.status_code);
modem->http_term();
```

### 7. Build durchführen

```bash
idf.py build
```

### 8. Hardware-Verbindungen

```
ESP32                A7670E
─────────────────────────────
GPIO4   (TX2) ────── RXD
GPIO5   (RX2) ────── TXD
GPIO6   (RTS2) ────── RTS
GPIO7   (CTS2) ────── CTS
GND     ────────── GND
3.3V    ────────── 3.3V (durch Level-Shifter wenn nötig)
```

## Häufige Probleme

### Problem: Commands geben ERROR zurück
**Lösung:**
1. UART-Verbindung prüfen
2. Baudrate prüfen (115200 Standard)
3. `set_urc_port(UrcPort::UART)` aufrufen
4. Module muss registriert sein für Netzwerk-Commands

### Problem: MQTT verbindet nicht
**Lösung:**
1. **argtopic-Modus aktivieren:** `mqtt_cfg_argtopic(0, 1, 1)` BEFORE `mqtt_connect()`
2. Netzwerk-Status prüfen mit `get_cgatt()`
3. SSL-Zertifikat bei TLS konfigurieren

### Problem: Dateioperationen fehlgeschlagen
**Lösung:**
1. EFS-Größe mit `fs_attri()` prüfen
2. Dateiname korrekt: "C:/filename" oder "filename"
3. Chunk-Größe bei großen Dateien reduzieren (≤475 Bytes)

### Problem: GNSS bekommt keinen Fix
**Lösung:**
1. Im Freien testen mit freiem Himmel
2. 2+ Minuten für First Fix einplanen
3. Mode mit `gnss_mode_set()` überprüfen

## Advanced Konfiguration

### Custom SSL-Zertifikat

```cpp
// 1. Zertifikat hochladen
std::string pem_data = /* read from file */;
modem->cftranrx("ca_cert.pem", pem_data);

// 2. SSL-Context konfigurieren
modem->ssl_cfg_set_ca(0, "ca_cert.pem");
modem->ssl_cfg_set_version(0, SslVersion::TLS12);
modem->ssl_cfg_set_auth_mode(0, SslAuthMode::SERVER_AUTH);
modem->ssl_cfg_set_sni(0, true);

// 3. Für HTTP verwenden
modem->http_set_ssl_cfg(0);

// 4. Für MQTT verwenden
modem->mqtt_ssl_cfg(0, 0);
```

### eDRX-Modus

```cpp
// eDRX aktivieren (LTE mit optimiertem Batteriebrauch)
modem->edrx_set(2, EDrxActType::EUTRAN_WB, "0001");

// Dynamische Parameter lesen
EDrxParams params;
modem->edrx_rdp(params);
ESP_LOGI(TAG, "eDRX ACT=%d, PTW=%s",
         static_cast<int>(params.act_type),
         params.paging_time_window.c_str());
```

### Serial Interface Config

```cpp
// Permanente Baudrate setzen
modem->set_baud_permanent(BaudRate::B115200);

// Flow Control
modem->set_ifc(IfcMode::HW, IfcMode::HW);

// UART Sleep
modem->set_uart_sleep(UartSleep::DTR);

// URC Delay (Empfohlen für zuverlässige URC-Verarbeitung)
modem->set_curcd(4000, 1);
```

## Testing

### Validierungs-Checkliste

- [ ] Modem antwortet auf AT-Commands
- [ ] Registration stabil (stat=1 oder 5)
- [ ] PS Attach erfolgreich
- [ ] HTTP GET funktioniert
- [ ] MQTT Connect funktioniert (mit argtopic!)
- [ ] MQTT Subscribe/Publish funktioniert
- [ ] GNSS bekommt Fix nach 2+ Minuten
- [ ] Datei-Upload/Download funktioniert
- [ ] SSL-Zertifikat wird geladen
- [ ] Callbacks werden getriggert

## Dokumentation

- Vollständige API: siehe `a7670e_module.hpp`
- Typen & Enums: siehe `a7670e_types.hpp`
- Beispiel: siehe `examples/a7670e_at_only/a7670e_at_example.cpp`
- AT-Befehle: siehe jeweilige `a7670e_commands_*.cpp`

## Support

Bei Fragen oder Problemen:
1. Siehe TROUBLESHOOTING in README.md
2. Überprüfen Sie die AT-Command Logs
3. Konsultieren Sie das A7670E Datenblatt
4. Prüfen Sie die esp_modem Dokumentation

