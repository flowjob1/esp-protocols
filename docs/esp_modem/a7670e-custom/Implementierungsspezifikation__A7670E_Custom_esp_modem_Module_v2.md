# Implementierungsspezifikation: SIMCom A7670E – Custom `esp_modem` Module (v2)

> **Zielversion:** `esp-protocols` master (esp_modem ≥ 1.1.0, getestet mit ESP-IDF ≥ v5.2)
> **Referenzen:**
> - Docs: https://docs.espressif.com/projects/esp-protocols/esp_modem/docs/latest/
> - Advanced API: `.../advanced_api.html` → Custom Module, DCE Factory
> - Customization: `.../customization.html`
> - Quellcode: `components/esp_modem/` im esp-protocols-Repo
>
> **v2 — Korrekturen gegenüber v1 basierend auf realen Modem-Tests (Log-Datei):**
> - MQTT Publish/Subscribe: argtopic-Modus, Topic inline, kein CMQTTTOPIC/CMQTTPAYLOAD/CMQTTSUBTOPIC
> - MQTT URC: einzeiliges `+CMQTTRECV:` statt mehrteiliger CMQTTRXSTART/TOPIC/PAYLOAD/END-Sequenz
> - `AT+CMQTTREL` / `AT+CMQTTSTOP`: kein Timeout-Parameter (verursacht ERROR)
> - Filesystem: reduziert auf FSATTRI + CFTRANRX + CFTRANTX
> - CFTRANTX: transMode-Parameter ergänzt

---

## 1. Architekturentscheidung: Module-Only vs. Full DCE

Das Projekt nutzt ausschließlich den AT-Command-Modus. Kein PPP, kein `esp_netif`. Daher:

- **Instanziierung:** `dce_factory::Factory::create_unique_dce_from<A7670E>(config, dte, nullptr)` → `netif = nullptr`
- **Zugriff auf Custom-Commands:** `static_cast<A7670E*>(dce->get_module())->method()`
- Kein `esp_netif_t` wird erstellt oder konfiguriert

---

## 2. Komponentenstruktur

```
components/
└── a7670e_modem/
    ├── CMakeLists.txt
    ├── Kconfig
    ├── include/
    │   ├── a7670e_module.hpp          # Modulklasse + alle Command-Deklarationen
    │   ├── a7670e_types.hpp           # Alle Enums, Structs für Parameter/Ergebnisse
    │   └── a7670e_urc_handler.hpp     # URC-Handler-Deklaration
    └── src/
        ├── a7670e_module.cpp          # Instanziierung + init_urc_handler
        ├── a7670e_commands_net.cpp    # Network + Packet Domain (Kap. 4, 5)
        ├── a7670e_commands_serial.cpp # Serial Interface (Kap. 10)
        ├── a7670e_commands_fs.cpp     # File System + File Transmission (Kap. 12, 13)
        ├── a7670e_commands_http.cpp   # HTTP(S) (Kap. 16)
        ├── a7670e_commands_mqtt.cpp   # MQTT(S) (Kap. 18)
        ├── a7670e_commands_ssl.cpp    # SSL (Kap. 19)
        ├── a7670e_commands_gnss.cpp   # GNSS (Kap. 23)
        ├── a7670e_commands_edrx.cpp   # eDRX (Kap. 34)
        └── a7670e_urc_handler.cpp     # URC-Verarbeitung
```

---

## 3. `CMakeLists.txt`

```cmake
idf_component_register(
    SRCS
        "src/a7670e_module.cpp"
        "src/a7670e_commands_net.cpp"
        "src/a7670e_commands_serial.cpp"
        "src/a7670e_commands_fs.cpp"
        "src/a7670e_commands_http.cpp"
        "src/a7670e_commands_mqtt.cpp"
        "src/a7670e_commands_ssl.cpp"
        "src/a7670e_commands_gnss.cpp"
        "src/a7670e_commands_edrx.cpp"
        "src/a7670e_urc_handler.cpp"
    INCLUDE_DIRS "include"
    REQUIRES esp_modem esp_event freertos
)
```

---

## 4. Typ-System (`a7670e_types.hpp`)

```cpp
#pragma once
#include <string>
#include <cstdint>
#include <functional>
#include <optional>
#include <vector>

namespace a7670e {

// ── 4.1 Netzwerk ────────────────────────────────────────────────────────────

enum class RegStat : int {
    NOT_REGISTERED_NOT_SEARCHING = 0,
    REGISTERED_HOME              = 1,
    NOT_REGISTERED_SEARCHING     = 2,
    REGISTRATION_DENIED          = 3,
    UNKNOWN                      = 4,
    REGISTERED_ROAMING           = 5,
    SMS_ONLY_HOME                = 6,
    SMS_ONLY_ROAMING             = 7,
    EMERGENCY_ONLY               = 11
};

enum class OperatorMode   : int { AUTOMATIC=0, MANUAL=1, DEREGISTER=2,
                                   SET_FORMAT_ONLY=3, MANUAL_WITH_FALLBACK=4 };
enum class OperatorFormat : int { LONG_ALPHA=0, SHORT_ALPHA=1, NUMERIC=2 };
enum class AccessTech     : int { GSM=0, GSM_COMPACT=1, UTRAN=2, GSM_EGPRS=3,
                                   UTRAN_HSDPA=4, UTRAN_HSUPA=5,
                                   UTRAN_HSDPA_HSUPA=6, EUTRAN=7, UTRAN_HSPA_PLUS=8 };

struct OperatorInfo {
    int         stat;   // 0=unknown,1=available,2=current,3=forbidden
    std::string long_name, short_name, numeric;
    AccessTech  act;
};

// ── 4.2 Paket-Domain ────────────────────────────────────────────────────────

enum class CgerepMode : int { BUFFER_DISCARD=0, DISCARD_IF_BUSY=1, BUFFER_IF_BUSY=2 };
enum class CgerepBfr  : int { CLEAR=0, FLUSH=1 };

// ── 4.3 Serial Interface ─────────────────────────────────────────────────────

enum class BaudRate : uint32_t {
    B300=300, B600=600, B1200=1200, B2400=2400, B4800=4800,
    B9600=9600, B19200=19200, B38400=38400, B57600=57600,
    B115200=115200, B230400=230400, B460800=460800,
    B921600=921600, B1800000=1800000, B3600000=3600000
};

enum class IcfFormat : int {
    DATA8_PARITY1_STOP1=1, DATA8_STOP1=2,
    DATA7_PARITY1_STOP1=3, DATA7_STOP1=4
};
enum class IcfParity : int { ODD=0, EVEN=1, NONE=2 };
enum class IfcMode   : int { NONE=0, XON_XOFF=1, HW=2 };
enum class UartSleep : int { OFF=0, DTR=1, RX=2, GPIO=3 };  // GPIO nur A7690B
enum class UrcPort   : int { ALL=0, UART=1, MODEM=2, ATCOM=3,
                              CMUX1=4, CMUX2=5, CMUX3=6, CMUX4=7 };

// ── 4.4 Filesystem ──────────────────────────────────────────────────────────

struct FsAttriResult { uint64_t size_bytes; };

// ── 4.5 HTTP ────────────────────────────────────────────────────────────────

enum class HttpMethod : int {
    GET=0, POST=1, HEAD=2, DELETE=3, PUT=4, PATCH=5, DOWNSPEED=20
};
struct HttpActionResult { HttpMethod method; int status_code; int data_len; };

// ── 4.6 MQTT ────────────────────────────────────────────────────────────────

enum class MqttQos        : int { AT_MOST_ONCE=0, AT_LEAST_ONCE=1, EXACTLY_ONCE=2 };
enum class MqttServerType : int { TCP=0, SSL_TLS=1 };

struct MqttMessage {
    int         client_index;
    std::string topic;
    std::string payload;
    int         qos;
};

using MqttMessageCb  = std::function<void(const MqttMessage&)>;
using MqttConnLostCb = std::function<void(int client_index, int cause)>;

// ── 4.7 SSL ─────────────────────────────────────────────────────────────────

enum class SslVersion  : int { SSL30=0, TLS10=1, TLS11=2, TLS12=3, ALL=4 };
enum class SslAuthMode : int { NO_AUTH=0, SERVER_AUTH=1,
                                MUTUAL_AUTH=2, CLIENT_AUTH_NO_SERVER=3 };
struct SslContext {
    SslVersion  version            = SslVersion::ALL;
    SslAuthMode auth_mode          = SslAuthMode::NO_AUTH;
    bool        ignore_local_time  = true;
    int         negotiate_timeout  = 300;
    std::string ca_file, client_cert_file, client_key_file, password_file;
    bool        enable_sni         = false;
    bool        ignore_cert_cn     = false;
};

// ── 4.8 GNSS ────────────────────────────────────────────────────────────────

enum class GnssMode : int {
    GPS=1, BDS=2, GPS_BDS=3, GLONASS=4, GLONASS_GPS=5,
    GLONASS_BDS=6, ALL_NO_GALILEO=7,
    GALILEO=8, GALILEO_GPS=9, GALILEO_BDS=10, GALILEO_GPS_BDS=11,
    GALILEO_GLONASS=12, GALILEO_GLONASS_GPS=13,
    GALILEO_GLONASS_BDS=14, ALL=15
};

struct GnssPosition {
    bool        valid         = false;
    int         mode          = 0;   // 2=2D, 3=3D
    int         gps_svs       = 0;
    int         beidou_svs    = 0;
    int         glonass_svs   = 0;
    int         galileo_svs   = 0;
    double      lat           = 0.0;
    char        ns            = 'N';
    double      lon           = 0.0;
    char        ew            = 'E';
    std::string date;               // ddmmyy
    std::string utc;                // hhmmss.ss
    double      alt_m         = 0.0;
    double      speed_knots   = 0.0;
    double      course_deg    = 0.0;
    double      pdop=0, hdop=0, vdop=0;
    int         num_sv        = 0;
};

// ── 4.9 eDRX ────────────────────────────────────────────────────────────────

enum class EDrxActType : int {
    NOT_USING=0, EC_GSM_IoT=1, GSM=2, UTRAN=3, EUTRAN_WB=4, EUTRAN_NB=5
};
struct EDrxParams {
    EDrxActType act_type;
    std::string requested_value, nw_provided_value, paging_time_window;
};

} // namespace a7670e
```

---

## 5. Modulklasse `a7670e_module.hpp`

```cpp
#pragma once
#include "cxx_include/esp_modem_api.hpp"
#include "cxx_include/esp_modem_dce_module.hpp"
#include "cxx_include/esp_modem_command_library_utils.hpp"
#include "a7670e_types.hpp"
#include "a7670e_urc_handler.hpp"
#include <memory>

namespace a7670e {

class A7670E : public esp_modem::GenericModule {
    using GenericModule::GenericModule;
public:

    // ── Initialisierung ──────────────────────────────────────────────────────
    void init_urc_handler(std::shared_ptr<esp_modem::DTE> dte_ref);

    // ── 3. Status Control ────────────────────────────────────────────────────
    // mode: -1=execution (AT+CPOF), 0=ordinary, 1=quick
    esp_modem::command_result power_off(int mode = -1);
    esp_modem::command_result reset_module();

    // ── 4. Network ───────────────────────────────────────────────────────────
    esp_modem::command_result set_creg(int n);
    esp_modem::command_result get_creg(int &n, RegStat &stat,
                                        std::string &lac, std::string &ci);
    esp_modem::command_result scan_operators(std::vector<OperatorInfo> &ops);
    esp_modem::command_result get_operator(OperatorMode &mode, OperatorFormat &fmt,
                                            std::string &oper, AccessTech &act);
    esp_modem::command_result set_operator(OperatorMode mode,
                                            std::optional<OperatorFormat> fmt = {},
                                            std::optional<std::string> oper   = {},
                                            std::optional<AccessTech>  act    = {});

    // ── 5. Packet Domain ─────────────────────────────────────────────────────
    esp_modem::command_result set_cgreg(int n);
    esp_modem::command_result get_cgreg(int &n, RegStat &stat);
    esp_modem::command_result set_cereg(int n);
    esp_modem::command_result get_cereg(int &n, RegStat &stat,
                                         std::string &tac, std::string &ci);
    esp_modem::command_result set_cgatt(int state);
    esp_modem::command_result get_cgatt(int &state);
    esp_modem::command_result set_cgerep(CgerepMode mode, CgerepBfr bfr = CgerepBfr::CLEAR);
    esp_modem::command_result get_cgerep(CgerepMode &mode, CgerepBfr &bfr);

    // ── 10. Serial Interface ─────────────────────────────────────────────────
    esp_modem::command_result set_baud_temp(BaudRate speed);
    esp_modem::command_result get_baud_temp(BaudRate &speed);
    esp_modem::command_result set_baud_permanent(BaudRate speed);
    esp_modem::command_result get_baud_permanent(BaudRate &speed);
    esp_modem::command_result set_icf(IcfFormat format, IcfParity parity);
    esp_modem::command_result get_icf(IcfFormat &format, IcfParity &parity);
    esp_modem::command_result set_ifc(IfcMode dce_flow, IfcMode dte_flow);
    esp_modem::command_result get_ifc(IfcMode &dce_flow, IfcMode &dte_flow);
    esp_modem::command_result set_uart_sleep(UartSleep mode);
    esp_modem::command_result get_uart_sleep(UartSleep &mode);
    esp_modem::command_result enable_cmux(int port_speed_index = 5,
                                           int n1 = 1500, int t2 = 600);
    esp_modem::command_result get_cmux(int &speed_idx, int &n1, int &t2);
    esp_modem::command_result set_urc_port(UrcPort port);
    esp_modem::command_result get_urc_port(UrcPort &port);
    esp_modem::command_result set_cfgri(bool enabled,
                                         int urc_time_ms = 60, int sms_time_ms = 120);
    esp_modem::command_result get_cfgri(bool &enabled, int &urc_ms, int &sms_ms);
    esp_modem::command_result set_curcd(int delay_ms, int cache_size = 1);
    esp_modem::command_result get_curcd(int &delay_ms, int &cache_size);

    // ── 12 + 13. File System / File Transmission ─────────────────────────────
    // Nur diese drei Operationen werden benötigt.

    // AT+FSATTRI – Dateigröße abfragen. Unterstützt "C:" und "D:".
    esp_modem::command_result fs_attri(const std::string &filename,
                                        FsAttriResult &result);

    // AT+CFTRANRX – Datei in EFS schreiben (> Prompt).
    // location=0 → von Anfang; len wird aus data.size() berechnet.
    esp_modem::command_result cftranrx(const std::string &filepath,
                                        const std::string &data,
                                        int location = 0);

    // AT+CFTRANTX – Dateiinhalt (oder Teilbereich) aus EFS lesen.
    // size < 0 → bis Dateiende. trans_mode: 0=normal, 1=direkt ohne URC-Header.
    esp_modem::command_result cftrantx(const std::string &filepath,
                                        std::string &out,
                                        int location   = 0,
                                        int size       = -1,
                                        int trans_mode = 0);

    // ── 16. HTTP(S) ──────────────────────────────────────────────────────────
    // cid=-1 → Execution Command (AT+HTTPINIT), cid≥1 → Write Command
    esp_modem::command_result http_init(int cid = -1);
    esp_modem::command_result http_term(int cid = -1);
    esp_modem::command_result http_set_url(const std::string &url);
    esp_modem::command_result http_set_connect_timeout(int sec);
    esp_modem::command_result http_set_recv_timeout(int sec);
    esp_modem::command_result http_set_content_type(const std::string &ct);
    esp_modem::command_result http_set_accept(const std::string &accept);
    esp_modem::command_result http_set_ssl_cfg(int sslcfg_id);
    esp_modem::command_result http_set_user_data(const std::string &data);
    esp_modem::command_result http_set_read_mode(int mode);
    esp_modem::command_result http_action(HttpMethod method, HttpActionResult &result);
    esp_modem::command_result http_head(std::string &header_data);
    esp_modem::command_result http_read(int start_offset, int byte_size,
                                         std::string &data);
    esp_modem::command_result http_read_len(int &total_len);
    esp_modem::command_result http_data_input(const std::string &data,
                                               int timeout_sec = 1000);
    esp_modem::command_result http_post_file(const std::string &filename,
                                              int path = 1,
                                              std::optional<HttpMethod> method = {},
                                              bool send_header = false);
    esp_modem::command_result http_read_file(const std::string &filename,
                                              int path = 1);

    // ── 18. MQTT(S) — argtopic-Modus ─────────────────────────────────────────
    //
    // WICHTIG: Alle MQTT-Operationen setzen voraus, dass nach mqtt_accq()
    // mqtt_cfg_argtopic() aufgerufen wurde. Dieser Modus ändert das
    // Befehlsformat von CMQTTPUB und CMQTTSUB sowie das URC-Format.
    //
    // Getesteter Flow:
    //   mqtt_start() → mqtt_accq(0,"id",SSL) → mqtt_cfg_argtopic(0,1,1)
    //   → mqtt_cfg_version(0,4) → [ssl_cfg_*] → mqtt_connect(...)
    //   → mqtt_subscribe(0,"topic/#",QOS1) → [Nachrichten empfangen via CB]
    //   → mqtt_publish(0,"topic","payload",QOS1,timeout,retained)
    //   → mqtt_disconnect(0) → mqtt_rel(0) → mqtt_stop()

    // cid=-1 → Execution, cid≥1 → Write (AT+CMQTTSTART=<cid>)
    esp_modem::command_result mqtt_start(int cid = -1);
    // Kein Timeout-Parameter! Nur: AT+CMQTTSTOP oder AT+CMQTTSTOP=<cid>
    esp_modem::command_result mqtt_stop(int cid = -1);

    esp_modem::command_result mqtt_accq(int client_index,
                                         const std::string &client_id,
                                         MqttServerType type = MqttServerType::TCP);
    // Kein Timeout-Parameter! Nur: AT+CMQTTREL=<client_index>
    esp_modem::command_result mqtt_rel(int client_index);

    esp_modem::command_result mqtt_ssl_cfg(int session_id, int ssl_ctx_index);

    esp_modem::command_result mqtt_connect(int client_index,
                                            const std::string &server_addr,
                                            int keepalive_sec,
                                            bool clean_session,
                                            const std::string &user = "",
                                            const std::string &pass = "");
    esp_modem::command_result mqtt_disconnect(int client_index,
                                               int timeout_sec = 120);

    // AT+CMQTTCFG="argtopic",<idx>,<show_len>,<payload_len>
    // Muss nach mqtt_accq() aufgerufen werden. Mit (1,1): Topic+Payload
    // erscheinen inline im Befehl/URC → empfohlene Konfiguration.
    esp_modem::command_result mqtt_cfg_argtopic(int index,
                                                  int show_len_flag    = 1,
                                                  int payload_len_flag = 1);
    esp_modem::command_result mqtt_cfg_check_utf8(int index, bool enable);
    esp_modem::command_result mqtt_cfg_optimeout(int index, int timeout_sec);
    esp_modem::command_result mqtt_cfg_version(int index, int version); // 3=MQTT3.1, 4=3.1.1
    esp_modem::command_result mqtt_cfg_cid(int cid);
    esp_modem::command_result mqtt_cfg_scid(int index, int cid);

    // Publish (argtopic-Modus):
    //   AT+CMQTTPUB=<idx>,"<topic>",<qos>,<len>,<retained>[,<dup>]
    //   → Modem antwortet mit '>'
    //   → payload wird gesendet (ohne \r)
    //   → OK, dann async +CMQTTPUB: <idx>,<err>
    esp_modem::command_result mqtt_publish(int client_index,
                                            const std::string &topic,
                                            const std::string &payload,
                                            MqttQos qos,
                                            int timeout_sec,
                                            bool retained = false,
                                            bool dup      = false);

    // Subscribe (argtopic-Modus):
    //   AT+CMQTTSUB=<idx>,"<topic>",<qos>
    //   → OK, dann async +CMQTTSUB: <idx>,<err>
    esp_modem::command_result mqtt_subscribe(int client_index,
                                              const std::string &topic,
                                              MqttQos qos);

    // ── 19. SSL ──────────────────────────────────────────────────────────────
    esp_modem::command_result ssl_cfg_set_version(int ctx_id, SslVersion v);
    esp_modem::command_result ssl_cfg_set_auth_mode(int ctx_id, SslAuthMode m);
    esp_modem::command_result ssl_cfg_set_ignore_time(int ctx_id, bool ignore);
    esp_modem::command_result ssl_cfg_set_negotiate_timeout(int ctx_id, int sec);
    esp_modem::command_result ssl_cfg_set_ca(int ctx_id, const std::string &file);
    esp_modem::command_result ssl_cfg_set_client_cert(int ctx_id, const std::string &file);
    esp_modem::command_result ssl_cfg_set_client_key(int ctx_id, const std::string &file);
    esp_modem::command_result ssl_cfg_set_password(int ctx_id, const std::string &file);
    esp_modem::command_result ssl_cfg_set_sni(int ctx_id, bool enable);
    esp_modem::command_result ssl_cfg_set_ignore_cn(int ctx_id, bool ignore);
    esp_modem::command_result ssl_cfg_get(int ctx_id, SslContext &ctx);

    // ── 23. GNSS ─────────────────────────────────────────────────────────────
    // power: 0=off, 1=on; ap_flash/dynamic_load: -1=weglassen
    esp_modem::command_result gnss_power(int power,
                                          int ap_flash     = -1,
                                          int dynamic_load = -1);
    esp_modem::command_result gnss_mode_set(GnssMode mode);
    esp_modem::command_result gnss_mode_get(GnssMode &mode);
    esp_modem::command_result gnss_nmea_set(int gga, int gll, int gsa, int gsv,
                                             int rmc, int vtg, int zda, int gst);
    esp_modem::command_result gnss_nmea_get(int &gga, int &gll, int &gsa, int &gsv,
                                             int &rmc, int &vtg, int &zda, int &gst);
    esp_modem::command_result gnss_info(GnssPosition &pos);
    // time_sec=0 → periodische Abfrage stoppen
    esp_modem::command_result gnss_info_periodic(int time_sec);

    // ── 34. eDRX ─────────────────────────────────────────────────────────────
    esp_modem::command_result edrx_set(int mode,
                                        EDrxActType act_type           = EDrxActType::NOT_USING,
                                        const std::string &req_value   = "");
    esp_modem::command_result edrx_get(EDrxActType &act_type, std::string &req_val);
    esp_modem::command_result edrx_rdp(EDrxParams &params);

    // ── URC Callbacks ────────────────────────────────────────────────────────
    void set_mqtt_message_cb(MqttMessageCb cb);
    void set_mqtt_conn_lost_cb(MqttConnLostCb cb);
    void set_gnss_ready_cb(std::function<void()> cb);
    void set_gnss_info_cb(std::function<void(const GnssPosition&)> cb);

private:
    std::unique_ptr<A7670eUrcHandler> urc_handler_;

    // Hilfsroutine: schickt <cmd>, wartet auf '>' oder 'DOWNLOAD',
    // sendet dann <data> als Rohdaten, wartet auf <expected_final>.
    esp_modem::command_result send_data_after_prompt(const std::string &cmd,
                                                      const std::string &data,
                                                      const std::string &expected_final,
                                                      uint32_t timeout_ms);
};

} // namespace a7670e
```

---

## 6. Command-Implementierungsregeln

### 6.1 Allgemeine Muster

```cpp
#include "a7670e_module.hpp"
using namespace esp_modem;
using namespace a7670e;
using CR = command_result;
```

**Muster A — Einfacher Set-Command:**
```cpp
CR A7670E::reset_module() {
    return command("AT+CRESET\r", [](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}
```

**Muster B — Read-Command mit Parsing:**
```cpp
CR A7670E::get_cgatt(int &state) {
    return command("AT+CGATT?\r", [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+CGATT:");
        if (pos != std::string_view::npos) {
            sscanf(r.data() + pos, "+CGATT: %d", &state);
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 9000);
}
```

**Muster C — Prompt-Dateneingabe (`>` oder `DOWNLOAD`):**
```cpp
CR A7670E::send_data_after_prompt(const std::string &cmd,
                                   const std::string &data,
                                   const std::string &expected_final,
                                   uint32_t timeout_ms)
{
    // Phase 1: Command senden, auf Prompt warten
    auto r = command(cmd, [](uint8_t *d, size_t l) -> CR {
        std::string_view resp(reinterpret_cast<char*>(d), l);
        if (resp.find(">")        != std::string_view::npos) return CR::OK;
        if (resp.find("DOWNLOAD") != std::string_view::npos) return CR::OK;
        if (resp.find("ERROR")    != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, timeout_ms);

    if (r != CR::OK) return CR::FAIL;

    // Phase 2: Rohdaten senden, auf finales OK warten
    std::string out;
    return at_raw(data, out, expected_final, "ERROR", timeout_ms);
}
```

**Muster D — Zweiphasige Async-Response** (OK sofort, URC verzögert):
```cpp
// Kein separater AGAIN-Loop nötig: command() akkumuliert alle Daten
// bis die Callback-Bedingung erfüllt ist.
CR A7670E::mqtt_connect(int idx, const std::string &addr,
                         int keepalive, bool clean,
                         const std::string &user, const std::string &pass)
{
    std::string cmd = "AT+CMQTTCONNECT=" + std::to_string(idx)
                    + ",\"" + addr + "\","
                    + std::to_string(keepalive) + ","
                    + (clean ? "1" : "0");
    if (!user.empty()) cmd += ",\"" + user + "\",\"" + pass + "\"";
    cmd += "\r";

    int err = -1;
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        // Auf "+CMQTTCONNECT: <idx>,<err>" warten; OK vorher ignorieren
        auto pos = r.find("+CMQTTCONNECT:");
        if (pos != std::string_view::npos) {
            int recv_idx;
            sscanf(r.data() + pos, "+CMQTTCONNECT: %d,%d", &recv_idx, &err);
            return (err == 0) ? CR::OK : CR::FAIL;
        }
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 60000);
}
```

### 6.2 Parsing-Hinweise

- `string_view` bevorzugen (kein Alloc, kein Copy)
- `AGAIN` für jede Zeile zurückgeben, die kein finales OK/ERROR/URC ist
- Für numerische Werte: `sscanf` oder `strtol`

---

## 7. Spezifikation der Commands

### 7.1 Status Control

| Methode | AT-Command | Timeout | Besonderheiten |
|---|---|---|---|
| `power_off(-1)` | `AT+CPOF\r` | 9000 ms | wartet auf `POWERD DOWN` |
| `power_off(0/1)` | `AT+CPOF=<mode>\r` | 9000 ms | URC `+CGEV:` vorher mit AGAIN ignorieren |
| `reset_module()` | `AT+CRESET\r` | 9000 ms | `OK` → CR::OK |

---

### 7.2 Network

**`set_creg(n)`:** `AT+CREG=<n>\r` → `OK`. Timeout: 9000 ms.

**`get_creg(n, stat, lac, ci)`:** `AT+CREG?\r` → parst `+CREG: <n>,<stat>[,<lac>,<ci>]`. `lac`/`ci` nur bei n=2 befüllt. Timeout: 9000 ms.

**`scan_operators(ops)`:** `AT+COPS=?\r` → **Timeout 60 s**. Parst CSV-Liste von `(stat,"long","short","numeric",act)`. Während des Scans keine anderen Commands.

**`get_operator(mode, fmt, oper, act)`:** `AT+COPS?\r` → parst `+COPS: <mode>[,<format>,<oper>[,<AcT>]]`. Timeout: 9000 ms.

**`set_operator(...)`:** Baut `AT+COPS=<mode>[,<format>[,<oper>[,<AcT>]]]\r`. Timeout: 60 s.

---

### 7.3 Packet Domain

Alle Timeouts: 9000 ms.

**`set/get_cgreg`:** `AT+CGREG=<n>\r` / `AT+CGREG?\r` → `+CGREG: <n>,<stat>[,<lac>,<ci>]`.

**`set/get_cereg`:** `AT+CEREG=<n>\r` / `AT+CEREG?\r` → `+CEREG: <n>,<stat>[,<tac>,<ci>]`.

**`set_cgatt(state)` / `get_cgatt(state)`:**
- Set: `AT+CGATT=<state>\r`
- Get: `AT+CGATT?\r` → parst `+CGATT: <state>`

**`set_cgerep(mode, bfr)` / `get_cgerep(mode, bfr)`:**
- Set: `AT+CGEREP=<mode>,<bfr>\r`
- Get: `AT+CGEREP?\r` → parst `+CGEREP: <mode>,<bfr>`

---

### 7.4 Serial Interface

Alle Timeouts: 9000 ms.

**Baudrate:** `AT+IPR=<speed>\r` (temp) / `AT+IPREX=<speed>\r` (permanent, AUTO_SAVE).

**Character Framing:** `AT+ICF=<format>,<parity>\r` / `AT+ICF?\r`.

**Flow Control:** `AT+IFC=<DCE>,<DTE>\r` / `AT+IFC?\r`.

**UART Sleep:** `AT+CSCLK=<mode>\r` / `AT+CSCLK?\r`.

**CMUX:** `AT+CMUX=0,,<speed_idx>,<n1>,,<t2>\r` — **nicht für normalen Betrieb aktivieren!**

**URC-Port:** `AT+CATR=<port>\r`. Empfohlen: `AT+CATR=1` (UART) in Init-Sequenz.

**RI-Pin:** `AT+CFGRI=<0|1>,<urc_ms>,<sms_ms>\r` / `AT+CFGRI?\r`.

**URC Delay:** `AT+CURCD=<delay_ms>,<cache_size>\r` (`cache_size` immer 1).

---

### 7.5 File System und File Transmission

Nur drei Operationen werden benötigt. FSOPEN, FSREAD, FSWRITE, FSCLOSE, FSLS, FSDEL entfallen.

#### `fs_attri(filename, result)`

```
AT+FSATTRI="<filename>"\r
→ +FSATTRI: <file_size>
→ OK
```

Parst `size_bytes` aus dem Response. Timeout: 5000 ms.

**Beispiel aus dem Log:**
```
AT+FSATTRI="ca_cert2.pem"  →  +FSATTRI: 3800  OK
AT+FSATTRI="C:/ca_cert2.pem"  →  +FSATTRI: 3800  OK
```

#### `cftranrx(filepath, data, location)`

Muster C. Command: `AT+CFTRANRX="<filepath>",<len>[,100,<location>]\r`

- `<len>` = `data.size()`
- Wenn `location != 0`: `,100,<location>` anhängen (100 ist der `reserved`-Wert)
- Wartet auf `>`, sendet dann `data` als Rohdaten, wartet auf `OK`
- Timeout: 60000 ms (UART-Übertragung kann bei großen Dateien dauern)

**Hinweis:** Datei darf nicht bereits existieren, wenn von Anfang geschrieben wird. Bei `location > 0` muss die Datei bereits vorhanden und groß genug sein.

#### `cftrantx(filepath, out, location, size, trans_mode)`

Command-Format:
- `size >= 0`: `AT+CFTRANTX="<filepath>",<location>,<size>,<trans_mode>\r`
- `size < 0`:  `AT+CFTRANTX="<filepath>",<location>,,<trans_mode>\r` (bis Dateiende)

**Response-Muster (trans_mode=0, normal):**
```
+CFTRANTX: DATA,<len>
<len Bytes Rohdaten>
+CFTRANTX: 0
OK
```

Parsing:
1. Auf `+CFTRANTX: DATA,<n>` warten → `n` Bytes akkumulieren in `out`
2. AGAIN zurückgeben bis `+CFTRANTX: 0` und `OK` erscheinen
3. Mehrere DATA-Blöcke werden akkumuliert

**Chunked-Beispiel aus dem Log** (8 sequenzielle Calls für 3800-Byte-Datei):
```
AT+CFTRANTX="C:/ca_cert2.pem",0,475,0    → DATA,475 ... +CFTRANTX: 0 OK
AT+CFTRANTX="C:/ca_cert2.pem",475,475,0  → DATA,475 ... +CFTRANTX: 0 OK
AT+CFTRANTX="C:/ca_cert2.pem",950,475,0  → DATA,475 ... +CFTRANTX: 0 OK
...
AT+CFTRANTX="C:/ca_cert2.pem",3325,,0    → DATA,475 ... +CFTRANTX: 0 OK
```

Timeout: 60000 ms pro Call (bei großen Chunks entsprechend erhöhen).

---

### 7.6 HTTP(S)

**`http_init(cid)`:**
- `cid == -1`: `AT+HTTPINIT\r` → `OK`
- `cid >= 1`: `AT+HTTPINIT=<cid>\r` → parst `+HTTPINIT: <errcode>,<cid>`
- Timeout: 120000 ms. Ein `AT+HTTPTERM` vor `AT+HTTPINIT` kann `ERROR` zurückgeben — ist normal (ignorieren).

**`http_term(cid)`:** Analog. Timeout: 120000 ms.

**`http_set_*()` Methoden:** Alle `AT+HTTPPARA="<KEY>",<value>\r`. Timeout: 120000 ms.

| Methode | Key | Typ / Bereich |
|---|---|---|
| `http_set_url` | `"URL"` | `http://...` oder `https://...` |
| `http_set_connect_timeout` | `"CONNECTTO"` | int, 20–120 s |
| `http_set_recv_timeout` | `"RECVTO"` | int, 2–120 s |
| `http_set_content_type` | `"CONTENT"` | String, max 256 |
| `http_set_accept` | `"ACCEPT"` | String, max 256 |
| `http_set_ssl_cfg` | `"SSLCFG"` | int, 0–9 |
| `http_set_user_data` | `"USERDATA"` | String, max 256 |
| `http_set_read_mode` | `"READMODE"` | int, 0 oder 1 |

**`http_action(method, result)`:**
`AT+HTTPACTION=<method>\r` → initiales `OK` (mit AGAIN ignorieren) → `+HTTPACTION: <method>,<statuscode>,<datalen>` parsen. Timeout: 120000 ms gesamt.

**`http_head(header_data)`:** `AT+HTTPHEAD\r` → parst `+HTTPHEAD: <len>`, liest `len` Bytes.

**`http_read(start, byte_size, data)`:** `AT+HTTPREAD=<start>,<byte_size>\r` → `+HTTPREAD: <len>` → Daten → `+HTTPREAD: 0`.

**`http_read_len(total)`:** `AT+HTTPREAD?\r` → parst `+HTTPREAD: LEN,<len>`.

**`http_data_input(data, timeout_sec)`:** Muster C: `AT+HTTPDATA=<len>,<timeout_sec>\r` → `DOWNLOAD` → data → `OK`.

**`http_post_file`:** `AT+HTTPPOSTFILE="<fn>",<path>[,<method>[,<send_header>]]\r` → `+HTTPPOSTFILE: ...`. Timeout: 120000 ms.

**`http_read_file(filename, path)`:** `AT+HTTPREADFILE="<filename>"[,<path>]\r` → parst `+HTTPREADFILE: <errcode>`. Timeout: 120000 ms.

---

### 7.7 MQTT(S) — argtopic-Modus

> **Grundlegendes zur argtopic-Konfiguration:**
>
> `AT+CMQTTCFG="argtopic",<idx>,1,1` schaltet den argtopic-Modus ein. Dieser Modus
> **ändert das Befehlsformat** von `AT+CMQTTPUB` und `AT+CMQTTSUB` sowie das
> **URC-Format** eingehender Nachrichten. Er ist **Voraussetzung** für die nachfolgend
> dokumentierten Befehle. Ohne argtopic wäre ein anderer (nicht getesteter) Ablauf nötig.

#### Getesteter Initialisierungsablauf

```
AT+CMQTTSTART
→ OK
→ +CMQTTSTART: 0

AT+CMQTTACCQ=0,"A76XX",1          ← client_index=0, server_type=1 (SSL)
→ OK

AT+CMQTTCFG="argtopic",0,1,1      ← Pflicht vor Connect
→ OK
AT+CMQTTCFG="version",0,4         ← MQTT 3.1.1
→ OK

[SSL konfigurieren via ssl_cfg_*]

AT+CMQTTCONNECT=0,"tcp://host:8883",100,1,"user","pass"
→ OK
→ +CMQTTCONNECT: 0,0              ← err=0 = Erfolg
```

#### `mqtt_start(cid)` / `mqtt_stop(cid)`

```
AT+CMQTTSTART         (cid=-1)
AT+CMQTTSTART=<cid>   (cid≥1)
→ OK
→ +CMQTTSTART: <err>   (err=0 = Erfolg)

AT+CMQTTSTOP          (kein Timeout-Parameter!)
AT+CMQTTSTOP=<cid>
→ OK
→ +CMQTTSTOP: <err>
```

Timeout: 12000 ms.

#### `mqtt_accq(idx, client_id, type)`

```
AT+CMQTTACCQ=<idx>,"<client_id>",<type>\r
→ OK
```

Timeout: 5000 ms.

#### `mqtt_rel(idx)`

```
AT+CMQTTREL=<idx>\r        ← KEIN weiterer Parameter!
→ OK
```

Timeout: 5000 ms. **Hinweis:** `AT+CMQTTREL=0,20` liefert ERROR — Timeout-Parameter existiert nicht.

#### `mqtt_ssl_cfg(session_id, ssl_ctx_idx)`

```
AT+CMQTTSSLCFG=<session_id>,<ssl_ctx_idx>\r
→ OK
```

Timeout: 5000 ms. Vor `mqtt_connect()` aufrufen.

#### `mqtt_connect(idx, addr, keepalive, clean, user, pass)`

```
AT+CMQTTCONNECT=<idx>,"<addr>",<keepalive>,<clean>[,"<user>","<pass>"]\r
→ OK                      ← AGAIN
→ +CMQTTCONNECT: <idx>,<err>   ← CR::OK wenn err=0
```

Timeout: 60000 ms (Muster D).

#### `mqtt_disconnect(idx, timeout_sec)`

```
AT+CMQTTDISC=<idx>,<timeout_sec>\r
→ OK                      ← AGAIN
→ +CMQTTDISC: <idx>,0
```

Timeout: `(timeout_sec + 10) * 1000` ms.

#### `mqtt_cfg_argtopic(index, show_len_flag, payload_len_flag)`

```
AT+CMQTTCFG="argtopic",<index>,<show_len>,<payload_len>\r
→ OK
```

Timeout: 5000 ms. Empfohlener Aufruf: `mqtt_cfg_argtopic(0, 1, 1)`.

#### `mqtt_cfg_*()`

| Methode | AT-Command |
|---|---|
| `mqtt_cfg_check_utf8(idx, en)` | `AT+CMQTTCFG="checkUTF8",<idx>,<0\|1>\r` |
| `mqtt_cfg_optimeout(idx, sec)` | `AT+CMQTTCFG="optimeout",<idx>,<val>\r` |
| `mqtt_cfg_version(idx, v)` | `AT+CMQTTCFG="version",<idx>,<3\|4>\r` |
| `mqtt_cfg_cid(cid)` | `AT+CMQTTCFG="CID",<cid>\r` |
| `mqtt_cfg_scid(idx, cid)` | `AT+CMQTTCFG="SCID",<idx>,<cid>\r` |

Alle Timeout: 5000 ms.

#### `mqtt_publish(idx, topic, payload, qos, timeout_sec, retained, dup)`

**Befehlsformat mit argtopic:**
```
AT+CMQTTPUB=<idx>,"<topic>",<qos>,<payload_len>,<retained>[,<dup>]\r
→ >
<payload_bytes>         ← ohne \r, Länge exakt payload_len Bytes
→ OK                    ← AGAIN
→ +CMQTTPUB: <idx>,<err>   ← CR::OK wenn err=0
```

Timeout Phase 1 (bis `>`): 5000 ms.
Timeout Phase 2 (bis `+CMQTTPUB:`): `(timeout_sec + 10) * 1000` ms.

**Log-Beispiele:**
```
AT+CMQTTPUB=0,"state/config/bat_low_mv",1,4,1
>
3800
OK
+CMQTTPUB: 0,0

AT+CMQTTPUB=0,"cmd/cancel_overrides/set",1,3,1
>
ACK
OK
+CMQTTPUB: 0,0
```

Implementierung: `send_data_after_prompt()` für Phase 1+2, dann separater Callback-Loop für das `+CMQTTPUB:`-URC. Einfacher: Gesamten Ablauf (Prompt + Daten + URC-Warten) in einem `command()`-Call mit akkumulierter Response.

#### `mqtt_subscribe(idx, topic, qos)`

**Befehlsformat mit argtopic:**
```
AT+CMQTTSUB=<idx>,"<topic>",<qos>\r
→ OK                    ← AGAIN
→ +CMQTTSUB: <idx>,<err>   ← CR::OK wenn err=0
```

Timeout: 30000 ms (Muster D).

**Log-Beispiel:**
```
AT+CMQTTSUB=0,"cmd/#",1
OK
+CMQTTSUB: 0,0
```

---

### 7.8 SSL

**`ssl_cfg_set_*(ctx_id, value)`:** Alle `AT+CSSLCFG="<key>",<ctx_id>,<value>\r`. Timeout: 120000 ms.

| Methode | AT-Key | Wertebereich |
|---|---|---|
| `set_version` | `"sslversion"` | 0–4 |
| `set_auth_mode` | `"authmode"` | 0–3 |
| `set_ignore_time` | `"ignorelocaltime"` | 0–1 |
| `set_negotiate_timeout` | `"negotiatetime"` | 10–300 |
| `set_ca` | `"cacert"` | Dateiname-String (.pem/.der) |
| `set_client_cert` | `"clientcert"` | Dateiname-String |
| `set_client_key` | `"clientkey"` | Dateiname-String |
| `set_password` | `"password"` | Dateiname-String |
| `set_sni` | `"enableSNI"` | 0–1 |
| `set_ignore_cn` | `"ignorecertCN"` | 0–1 |

**`ssl_cfg_get(ctx_id, ctx)`:** `AT+CSSLCFG=<ctx_id>\r` → parst alle Felder.

---

### 7.9 GNSS

**`gnss_power(power, ap_flash, dynamic_load)`:**
```
AT+CGNSSPWR=<power>[,<ap_flash>[,<dynamic_load>]]\r
→ OK
→ (async) +CGNSSPWR: READY!    ← URC, vom Handler gefeuert
```

Timeout (für OK): 9000 ms. Das `READY!`-URC kommt asynchron — Callback via `set_gnss_ready_cb`.

**`gnss_mode_set/get`:** `AT+CGNSSMODE=<mode>\r` / `AT+CGNSSMODE?\r`. Timeout: 9000 ms.

**`gnss_nmea_set/get`:** `AT+CGNSSNMEA=<gga>,<gll>,<gsa>,<gsv>,<rmc>,<vtg>,<zda>,<gst>\r`. Timeout: 9000 ms.

**`gnss_info(pos)`:** `AT+CGNSSINFO\r` → parst 18 Komma-separierte Felder.

**`gnss_info_periodic(time_sec)`:** `AT+CGNSSINFO=<time>\r` → `OK`. Danach periodische URCs via `set_gnss_info_cb`. `time_sec=0` stoppt die Ausgabe.

**GNSS Info Feld-Format** (aus Log validiert):
```
+CGNSSINFO: <mode>,<gps-sv>,<beidou-sv>,<glonass-sv>,<galileo-sv>,
            <lat>,<N/S>,<lon>,<E/W>,<date>,<UTC>,
            <alt>,<speed>,<course>,<PDOP>,<HDOP>,<VDOP>,<NoSV>
```

Felder können leer sein (z.B. `glonass-sv` bei GLONASS-Modus ohne GLONASS-Fix, `course` wenn Geschwindigkeit=0). Bei leerem `lat`-Feld → `pos.valid = false`.

**Log-Beispiel (3D-Fix mit GPS+GLONASS):**
```
+CGNSSINFO: 3,10,00,,00,48.5393715,N,12.1240492,E,250426,095854.00,482.0,1.203,,6.02,3.51,4.88,04
```
= mode=3, gps-sv=10, beidou=00, glonass=leer, galileo=00, lat=48.5393715N, lon=12.1240492E,
  date=250426, utc=095854.00, alt=482.0m, speed=1.203kn, course=leer, PDOP=6.02, HDOP=3.51, VDOP=4.88, NoSV=4

**Kein Fix:**
```
+CGNSSINFO: ,,,,,,,,
```
(Alle Felder leer → `pos.valid = false`)

---

### 7.10 eDRX

**`edrx_set(mode, act_type, req_value)`:**
`AT+CEDRXS=<mode>[,<eDrxAct>[,"<value>"]]\r`. Timeout: 9000 ms. AUTO_SAVE.

**`edrx_get(act, req_val)`:** `AT+CEDRXS?\r` → parst `+CEDRXS: <act>[,"<val>"]`.

**`edrx_rdp(params)`:** `AT+CEDRXRDP\r` → parst `+CEDRXRDP: <AcT>[,"<req>","<nw>","<ptw>"]`.

---

## 8. URC-Handler (`a7670e_urc_handler.hpp` / `.cpp`)

### 8.1 Registrierung

```cpp
// Nach DCE-Erstellung:
dce->set_enhanced_urc(handler_fn, nullptr);
// Oder legacy:
dce->set_urc(handler_fn);
```

`init_urc_handler(dte_ref)` erstellt `A7670eUrcHandler` und registriert ihn.

### 8.2 Klasse `A7670eUrcHandler`

```cpp
class A7670eUrcHandler {
public:
    void handle(uint8_t *data, size_t len);

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
    void handle_line(const std::string &line);
    GnssPosition parse_gnss_info(const std::string &payload);
};
```

### 8.3 MQTT URC — `+CMQTTRECV:` (argtopic-Modus)

Im argtopic-Modus (`AT+CMQTTCFG="argtopic",<idx>,1,1`) erscheinen eingehende Nachrichten als **einzeilige** URCs:

```
+CMQTTRECV: <client_index>,"<topic>",<qos>,"<payload>"
```

**Log-Beispiele:**
```
+CMQTTRECV: 0,"cmd/config/heater_ss_min_on_sec/set",2,"40"
+CMQTTRECV: 0,"cmd/cancel_overrides/set",2,"GO"
+CMQTTRECV: 0,"cmd/config/wake_interval_sec/set",3,"630"
+CMQTTRECV: 0,"cmd/cancel_overrides/set",0,""
```

**Parsing:**
```cpp
bool try_parse_cmqttrecv(const std::string &line, MqttMessage &msg) {
    // Erwartet: +CMQTTRECV: <idx>,"<topic>",<qos>,"<payload>"
    int idx, qos;
    char topic[512], payload[2048];
    int n = sscanf(line.c_str() + strlen("+CMQTTRECV: "),
                   "%d,\"%511[^\"]\",%d,\"%2047[^\"]\"",
                   &idx, topic, &qos, payload);
    if (n < 3) return false;
    msg.client_index = idx;
    msg.topic        = topic;
    msg.qos          = qos;
    msg.payload      = (n == 4) ? payload : "";
    return true;
}
```

**Kein mehrteiliger State (kein CMQTTRXSTART/TOPIC/PAYLOAD/END)** — die ursprüngliche State-Machine der v1-Spec entfällt.

### 8.4 Alle URC-Muster

| URC-Prefix | Parsing | Aktion |
|---|---|---|
| `+CMQTTRECV:` | `idx,"topic",qos,"payload"` | `on_mqtt_message(msg)` |
| `+CMQTTSTART:` | `<err>` oder `<err>,<cid>` | `on_mqtt_start(err)` |
| `+CMQTTSTOP:` | `<err>` | intern |
| `+CMQTTCONNECT:` | `<idx>,<err>` | `on_mqtt_connect(idx, err)` |
| `+CMQTTDISC:` | `<idx>,<err>` | `on_mqtt_disconnect(idx, err)` |
| `+CMQTTCONNLOST:` | `<idx>,<cause>` | `on_mqtt_conn_lost(idx, cause)` |
| `+CMQTTNONET` | — | `on_mqtt_conn_lost(-1, 3)` |
| `+CMQTTSUB:` | `<idx>,<err>` | intern (bei synchronem Wait) |
| `+CMQTTPUB:` | `<idx>,<err>` | intern (bei synchronem Wait) |
| `+CGNSSPWR: READY!` | — | `on_gnss_ready()` |
| `+CGNSSINFO:` | 18-Felder-CSV | parse → `on_gnss_info(pos)` |
| `+HTTPACTION:` | `<method>,<code>,<len>` | `on_http_action(result)` |
| `+HTTPPOSTFILE:` | wie HTTPACTION | `on_http_action(result)` |
| `+HTTPREADFILE:` | `<errcode>` | `on_http_read_file(errcode)` |
| `+HTTP_PEER_CLOSED` | — | Log-Event |
| `+HTTP_NONET_EVENT` | — | Log-Event |
| `+CGEV:` | je nach Subtyp | optional Callback |
| `+NETOPEN:` | `<err>` | Log-Event / optional CB |

---

## 9. Instanziierung (`a7670e_module.cpp`)

```cpp
#include "cxx_include/esp_modem_api.hpp"
#include "cxx_include/esp_modem_dce_factory.hpp"
#include "a7670e_module.hpp"

using namespace esp_modem;
using namespace esp_modem::dce_factory;

std::unique_ptr<DCE> create_a7670e_dce(
    const dce_config *dce_cfg,
    const dte_config *dte_cfg)
{
    auto uart_dte = create_uart_dte(dte_cfg);
    // netif=nullptr → AT-only, kein PPP
    auto dce = Factory::create_unique_dce_from<a7670e::A7670E>(
        dce_cfg, uart_dte, nullptr);

    auto *mod = static_cast<a7670e::A7670E*>(dce->get_module());
    mod->init_urc_handler(uart_dte);
    return dce;
}
```

**Applikationscode — typischer Init-Ablauf** (abgeleitet aus Log):

```cpp
// 1. DCE erstellen
auto dce = create_a7670e_dce(&dce_cfg, &dte_cfg);
auto *mod = static_cast<a7670e::A7670E*>(dce->get_module());

// 2. URC-Port, GPRS-Events, Echo aus
mod->set_urc_port(UrcPort::UART);          // AT+CATR=1
mod->set_cgerep(CgerepMode::BUFFER_IF_BUSY, CgerepBfr::FLUSH); // AT+CGEREP=2,1
// dce->set_echo(false);                   // ATE0 — via GenericModule oder eigener Befehl

// 3. PDP-Kontexte
// AT+CGDCONT / AT+CGAUTH via eigene Methoden oder GenericModule::set_pdp_context()

// 4. Netzwerk
mod->set_cgatt(1);

// 5. Schlaf, RI, URC-Delay, eDRX
mod->set_uart_sleep(UartSleep::DTR);       // AT+CSCLK=1
mod->set_cfgri(true, 1500, 120);           // AT+CFGRI=1,1500,120
mod->set_curcd(4000, 1);                   // AT+CURCD=4000,1
mod->edrx_set(2, EDrxActType::EUTRAN_WB, "0001"); // AT+CEDRXS=2,4,0001

// 6. Zertifikat herunterladen (HTTP → EFS)
mod->http_init();
mod->http_set_url("http://example.com/ca.pem");
HttpActionResult hr;
mod->http_action(HttpMethod::GET, hr);
mod->http_read_file("ca_cert.pem", 1);    // → C:/ca_cert.pem
mod->http_term();
// Größe verifizieren
FsAttriResult ar;
mod->fs_attri("ca_cert.pem", ar);

// 7. SSL konfigurieren
mod->ssl_cfg_set_version(0, SslVersion::TLS12);   // AT+CSSLCFG="sslversion",0,3
mod->ssl_cfg_set_auth_mode(0, SslAuthMode::SERVER_AUTH);
mod->ssl_cfg_set_ca(0, "ca_cert.pem");
mod->ssl_cfg_set_sni(0, true);

// 8. MQTT Callbacks registrieren
mod->set_mqtt_message_cb([](const a7670e::MqttMessage &msg) {
    ESP_LOGI("MQTT", "RECV topic=%s payload=%s", msg.topic.c_str(), msg.payload.c_str());
});

// 9. MQTT Start
mod->mqtt_start();
mod->mqtt_accq(0, "esp32-device", MqttServerType::SSL_TLS);
mod->mqtt_cfg_argtopic(0, 1, 1);           // AT+CMQTTCFG="argtopic",0,1,1
mod->mqtt_cfg_version(0, 4);              // MQTT 3.1.1
// SSL nochmal für MQTT-Session konfigurieren (aus Log: vor Connect)
mod->ssl_cfg_set_auth_mode(0, SslAuthMode::SERVER_AUTH);
mod->ssl_cfg_set_version(0, SslVersion::TLS12);
mod->ssl_cfg_set_sni(0, true);
mod->ssl_cfg_set_ca(0, "ca_cert.pem");
mod->mqtt_connect(0, "tcp://broker.example.com:8883", 100, true, "user", "pass");

// 10. Subscribe
mod->mqtt_subscribe(0, "cmd/#", MqttQos::AT_LEAST_ONCE);

// 11. Publish
mod->mqtt_publish(0, "state/sensor", "42.5",
                  MqttQos::AT_LEAST_ONCE, 60, true);

// 12. Trennen
mod->mqtt_disconnect(0);
mod->mqtt_rel(0);
mod->mqtt_stop();
```

---

## 10. Hinweise und bekannte Einschränkungen

### 10.1 argtopic-Modus ist Pflicht

Ohne `AT+CMQTTCFG="argtopic",<idx>,1,1` wäre das Befehlsformat von `CMQTTPUB` und `CMQTTSUB` anders (Topic müsste separat über `AT+CMQTTTOPIC` / `AT+CMQTTSUBTOPIC` gesetzt werden — nicht getestet). Die vorliegende Implementierung basiert ausschließlich auf dem argtopic-Modus.

### 10.2 `AT+CMQTTREL` und `AT+CMQTTSTOP` — kein Timeout-Parameter

Beide Commands akzeptieren **keinen** Timeout-Parameter. `AT+CMQTTREL=0,20` liefert `ERROR`. Korrekte Syntax: `AT+CMQTTREL=<idx>` / `AT+CMQTTSTOP` / `AT+CMQTTSTOP=<cid>`.

### 10.3 Filesystem reduziert auf drei Operationen

Für das Projektanwendungsfall (Zertifikat via HTTP laden, aus EFS lesen/verifizieren) reichen `fs_attri`, `cftranrx` und `cftrantx`. FSOPEN/FSREAD/FSWRITE/FSCLOSE/FSLS/FSDEL sind nicht implementiert.

### 10.4 `AT+CFTRANTX` — Chunked-Betrieb

Für große Dateien: mehrere sequenzielle `cftrantx()`-Calls mit jeweils `location`+`size`. Jeder Call ist vollständig synchron (wartet auf `+CFTRANTX: 0` + `OK`). Die Chunk-Größe sollte ≤475 Bytes bleiben (aus Log), um UART-Buffer-Overflow zu vermeiden. Tatsächliche Maximalgröße hängt von der Dateiübertragungsgeschwindigkeit ab.

### 10.5 `AT+COPS=?` Scan — 60 Sekunden Timeout

Kein kürzeres Timeout setzen. Während des Scans keine anderen Commands.

### 10.6 CMUX — nicht aktivieren

Umschaltet den UART in einen anderen Modus und ist mit dem normalen DTE nicht kompatibel. Für AT-only-Betrieb nicht verwenden.

### 10.7 Thread-Safety

`GenericModule::command()` ist intern über einen Mutex serialisiert — nie gleichzeitig aus verschiedenen Tasks aufrufen. URC-Handler läuft im DTE-Thread — Callbacks müssen thread-safe sein (z.B. via `xQueueSend`).

### 10.8 Echo-Modus

Nach `ATE0` sendet das Modem kein Echo mehr zurück. Der DTE muss entsprechend konfiguriert sein. Falls `GenericModule` keine eigene `set_echo()`-Methode hat, als Custom-Command implementieren: `AT E0\r` → `OK`.

### 10.9 GNSS — Kein Fix liefert kurzes Response

Das Modem liefert bei fehlendem Fix `+CGNSSINFO: ,,,,,,,,` (nur 8 Kommas statt 17). Parsing muss mit variabler Feldanzahl umgehen und bei leerem ersten Feld `pos.valid = false` setzen.

---

## 11. Validierungscheckliste

- [ ] `AT+CATR=1` — URC auf UART-Port umgeleitet
- [ ] `AT+CGEREP=2,1` — GPRS-Events aktiv
- [ ] Netzwerkregistrierung (`get_creg`, `get_cereg`) → stat=1 oder 5
- [ ] PS-Attach (`set_cgatt(1)`) erfolgreich
- [ ] HTTP GET — Zertifikat herunterladen und in EFS speichern (`http_read_file`)
- [ ] `fs_attri` — Dateigröße stimmt mit HTTP-Response-Länge überein
- [ ] SSL-Kontext konfiguriert (Version, AuthMode, CA, SNI)
- [ ] MQTT TLS-Verbindung aufbauen (`mqtt_connect` → `+CMQTTCONNECT: 0,0`)
- [ ] `mqtt_cfg_argtopic(0,1,1)` gesetzt **vor** `mqtt_connect`
- [ ] Subscribe (`mqtt_subscribe(0,"topic/#",QOS1)`) → `+CMQTTSUB: 0,0`
- [ ] Eingehende Nachricht via `MqttMessageCb` empfangen
- [ ] Publish (`mqtt_publish(0,"topic","data",QOS1,60,false)`) → `+CMQTTPUB: 0,0`
- [ ] Retained Publish → Nachricht kommt als URC zurück (`+CMQTTRECV:`)
- [ ] Graceful Disconnect: `mqtt_disconnect` → `mqtt_rel` → `mqtt_stop`
- [ ] GNSS: Power on → `READY!`-URC → Mode → NMEA → periodische Info → Fix nach ≤2 min
- [ ] eDRX konfiguriert (`AT+CEDRXS=2,4,"0001"`)
- [ ] `set_baud_permanent` — nach Neustart gleiche Baudrate
- [ ] `cftrantx` — Datei aus EFS gelesen, Inhalt korrekt (PEM-Format verifizierbar)
