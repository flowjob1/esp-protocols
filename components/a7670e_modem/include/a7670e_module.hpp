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

