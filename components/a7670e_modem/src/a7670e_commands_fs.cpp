#include "a7670e_module.hpp"
#include <cstring>

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

// ── 12 + 13. File System / File Transmission ─────────────────────────────────

CR A7670E::fs_attri(const std::string &filename, FsAttriResult &result)
{
    std::string cmd = "AT+FSATTRI=\"" + filename + "\"\r";
    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);
        auto pos = r.find("+FSATTRI:");
        if (pos != std::string_view::npos) {
            uint64_t size_val;
            sscanf(r.data() + pos, "+FSATTRI: %llu", &size_val);
            result.size_bytes = size_val;
        }
        if (r.find("OK")    != std::string_view::npos) return CR::OK;
        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 5000);
}

CR A7670E::cftranrx(const std::string &filepath, const std::string &data, int location)
{
    std::string cmd = "AT+CFTRANRX=\"" + filepath + "\"," + std::to_string(data.size());
    if (location != 0) {
        cmd += ",100," + std::to_string(location);
    }
    cmd += "\r";

    return send_data_after_prompt(cmd, data, "OK", 60000);
}

CR A7670E::cftrantx(const std::string &filepath, std::string &out,
                     int location, int size, int trans_mode)
{
    std::string cmd = "AT+CFTRANTX=\"" + filepath + "\"," + std::to_string(location);

    if (size >= 0) {
        cmd += "," + std::to_string(size);
    } else {
        cmd += ",";
    }
    cmd += "," + std::to_string(trans_mode) + "\r";

    out.clear();

    return command(cmd, [&](uint8_t *d, size_t l) -> CR {
        std::string_view r(reinterpret_cast<char*>(d), l);

        // Look for DATA marker
        auto data_pos = r.find("+CFTRANTX: DATA,");
        if (data_pos != std::string_view::npos) {
            // Parse the length
            int data_len = 0;
            sscanf(r.data() + data_pos, "+CFTRANTX: DATA,%d", &data_len);

            // Find where actual data starts (after the newline following the marker)
            auto marker_end = r.find('\n', data_pos);
            if (marker_end != std::string_view::npos) {
                const char *data_start = r.data() + marker_end + 1;
                // Collect data_len bytes
                if (data_start + data_len <= r.data() + l) {
                    out.append(data_start, data_len);
                }
            }
        }

        // Check for end marker
        if (r.find("+CFTRANTX: 0") != std::string_view::npos) {
            if (r.find("OK") != std::string_view::npos) {
                return CR::OK;
            }
        }

        if (r.find("ERROR") != std::string_view::npos) return CR::FAIL;
        return CR::AGAIN;
    }, 60000);
}

