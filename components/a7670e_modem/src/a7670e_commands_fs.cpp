#include "a7670e_module.hpp"
#include "a7670e_parse_utils.hpp"

using namespace esp_modem;
using namespace a7670e;
using CR = command_result;

CR A7670E::fs_attri(const std::string &filename, FsAttriResult &result)
{
    const std::string cmd = "AT+FSATTRI=\"" + filename + "\"\r";
    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        const auto line = detail::find_line(response, "+FSATTRI:");
        if (!line.empty()) {
            uint64_t size = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+FSATTRI:").size()), size)) {
                return CR::FAIL;
            }
            result.size_bytes = size;
        }
        if (response.find("OK") != std::string_view::npos) {
            return CR::OK;
        }
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }
        return CR::TIMEOUT;
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

CR A7670E::cftrantx(const std::string &filepath, std::string &out, int location, int size, int trans_mode)
{
    std::string cmd = "AT+CFTRANTX=\"" + filepath + "\"," + std::to_string(location);
    if (size >= 0) {
        cmd += "," + std::to_string(size);
    } else {
        cmd += ",";
    }
    cmd += "," + std::to_string(trans_mode) + "\r";

    out.clear();

    return dte->command(cmd, [&](uint8_t *d, size_t l) -> CR {
        const std::string_view response(reinterpret_cast<char *>(d), l);
        if (response.find("ERROR") != std::string_view::npos) {
            return CR::FAIL;
        }

        std::string collected;
        size_t cursor = 0;
        while (true) {
            const auto marker = response.find("+CFTRANTX: DATA,", cursor);
            if (marker == std::string_view::npos) {
                break;
            }

            const auto line_end = response.find('\n', marker);
            if (line_end == std::string_view::npos) {
                return CR::TIMEOUT;
            }

            const auto line = detail::trim_ascii(response.substr(marker, line_end - marker));
            int block_len = 0;
            if (!detail::parse_integer(line.substr(std::string_view("+CFTRANTX: DATA,").size()), block_len) || block_len < 0) {
                return CR::FAIL;
            }

            const auto data_start = line_end + 1;
            const auto data_end = data_start + static_cast<size_t>(block_len);
            if (response.size() < data_end) {
                return CR::TIMEOUT;
            }

            collected.append(response.data() + data_start, static_cast<size_t>(block_len));
            cursor = data_end;
        }

        const auto done_pos = response.find("+CFTRANTX: 0", cursor);
        if (done_pos == std::string_view::npos || response.find("OK", done_pos) == std::string_view::npos) {
            return CR::TIMEOUT;
        }

        out = std::move(collected);
        return CR::OK;
    }, 60000);
}
