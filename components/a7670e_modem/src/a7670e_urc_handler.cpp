#include "a7670e_urc_handler.hpp"
#include <cstring>
#include <sstream>

using namespace a7670e;

void A7670eUrcHandler::handle(uint8_t *data, size_t len)
{
    if (!data || len == 0) return;

    std::string response(reinterpret_cast<char*>(data), len);

    // Split by lines and process each
    std::istringstream stream(response);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty()) {
            // Remove trailing \r if present
            if (line.back() == '\r') {
                line.pop_back();
            }
            handle_line(line);
        }
    }
}

void A7670eUrcHandler::handle_line(const std::string &line)
{
    // MQTT Messages - argtopic format
    if (line.find("+CMQTTRECV:") != std::string::npos) {
        if (on_mqtt_message) {
            MqttMessage msg;
            int idx, qos;
            char topic_buf[512] = {0};
            char payload_buf[2048] = {0};

            int n = sscanf(line.c_str() + strlen("+CMQTTRECV: "),
                          "%d,\"%511[^\"]\"%*c%d,\"%2047[^\"]\"",
                          &idx, topic_buf, &qos, payload_buf);

            if (n >= 1) {
                msg.client_index = idx;
                if (n >= 2) msg.topic = topic_buf;
                if (n >= 3) msg.qos = qos;
                if (n >= 4) msg.payload = payload_buf;
                on_mqtt_message(msg);
            }
        }
        return;
    }

    // MQTT Start
    if (line.find("+CMQTTSTART:") != std::string::npos) {
        if (on_mqtt_start) {
            int err;
            if (sscanf(line.c_str(), "+CMQTTSTART: %d", &err) == 1) {
                on_mqtt_start(err);
            }
        }
        return;
    }

    // MQTT Stop
    if (line.find("+CMQTTSTOP:") != std::string::npos) {
        // Handle internally, optional callback
        return;
    }

    // MQTT Connect
    if (line.find("+CMQTTCONNECT:") != std::string::npos) {
        if (on_mqtt_connect) {
            int idx, err;
            if (sscanf(line.c_str(), "+CMQTTCONNECT: %d,%d", &idx, &err) == 2) {
                on_mqtt_connect(idx, err);
            }
        }
        return;
    }

    // MQTT Disconnect
    if (line.find("+CMQTTDISC:") != std::string::npos) {
        if (on_mqtt_disconnect) {
            int idx, err;
            if (sscanf(line.c_str(), "+CMQTTDISC: %d,%d", &idx, &err) == 2) {
                on_mqtt_disconnect(idx, err);
            }
        }
        return;
    }

    // MQTT Connection Lost
    if (line.find("+CMQTTCONNLOST:") != std::string::npos) {
        if (on_mqtt_conn_lost) {
            int idx, cause;
            if (sscanf(line.c_str(), "+CMQTTCONNLOST: %d,%d", &idx, &cause) == 2) {
                on_mqtt_conn_lost(idx, cause);
            }
        }
        return;
    }

    // MQTT No Network
    if (line.find("+CMQTTNONET") != std::string::npos) {
        if (on_mqtt_conn_lost) {
            on_mqtt_conn_lost(-1, 3);  // No network
        }
        return;
    }

    // GNSS Power Ready
    if (line.find("+CGNSSPWR: READY!") != std::string::npos) {
        if (on_gnss_ready) {
            on_gnss_ready();
        }
        return;
    }

    // GNSS Info
    if (line.find("+CGNSSINFO:") != std::string::npos) {
        if (on_gnss_info) {
            GnssPosition pos = parse_gnss_info(line);
            on_gnss_info(pos);
        }
        return;
    }

    // HTTP Action
    if (line.find("+HTTPACTION:") != std::string::npos) {
        if (on_http_action) {
            int method, status, len;
            if (sscanf(line.c_str(), "+HTTPACTION: %d,%d,%d", &method, &status, &len) == 3) {
                HttpActionResult result;
                result.method = static_cast<HttpMethod>(method);
                result.status_code = status;
                result.data_len = len;
                on_http_action(result);
            }
        }
        return;
    }

    // HTTP PostFile
    if (line.find("+HTTPPOSTFILE:") != std::string::npos) {
        if (on_http_action) {
            int method, status, len;
            if (sscanf(line.c_str(), "+HTTPPOSTFILE: %d,%d,%d", &method, &status, &len) == 3) {
                HttpActionResult result;
                result.method = static_cast<HttpMethod>(method);
                result.status_code = status;
                result.data_len = len;
                on_http_action(result);
            }
        }
        return;
    }

    // HTTP ReadFile
    if (line.find("+HTTPREADFILE:") != std::string::npos) {
        if (on_http_read_file) {
            int errcode;
            if (sscanf(line.c_str(), "+HTTPREADFILE: %d", &errcode) == 1) {
                on_http_read_file(errcode);
            }
        }
        return;
    }

    // Other URCs - just log or ignore
    if (line.find("+HTTP_PEER_CLOSED") != std::string::npos) {
        // HTTP peer closed connection
        return;
    }

    if (line.find("+HTTP_NONET_EVENT") != std::string::npos) {
        // HTTP no network
        return;
    }

    if (line.find("+CGEV:") != std::string::npos) {
        // GPRS/Network events
        return;
    }

    if (line.find("+NETOPEN:") != std::string::npos) {
        // Network open event
        return;
    }
}

GnssPosition A7670eUrcHandler::parse_gnss_info(const std::string &payload)
{
    GnssPosition pos;
    pos.valid = false;

    char ns_ch = 'N', ew_ch = 'E';
    char date_buf[32] = {0};
    char utc_buf[32] = {0};

    int n = sscanf(payload.c_str(),
                   "+CGNSSINFO: %d,%d,%d,%d,%d,%lf,%c,%lf,%c,%31[^,],%31[^,],"
                   "%lf,%lf,%lf,%lf,%lf,%lf,%d",
                   &pos.mode, &pos.gps_svs, &pos.beidou_svs, &pos.glonass_svs,
                   &pos.galileo_svs, &pos.lat, &ns_ch, &pos.lon, &ew_ch,
                   date_buf, utc_buf, &pos.alt_m, &pos.speed_knots,
                   &pos.course_deg, &pos.pdop, &pos.hdop, &pos.vdop,
                   &pos.num_sv);

    if (n >= 18 && pos.lat > 0.0) {
        pos.valid = true;
        pos.ns = ns_ch;
        pos.ew = ew_ch;
        pos.date = date_buf;
        pos.utc = utc_buf;
    }

    return pos;
}

