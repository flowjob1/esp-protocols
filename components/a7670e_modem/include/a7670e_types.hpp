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

