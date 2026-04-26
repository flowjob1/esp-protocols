#pragma once

#include <charconv>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

namespace a7670e::detail {

inline bool starts_with(std::string_view value, std::string_view prefix)
{
    return value.size() >= prefix.size() && value.compare(0, prefix.size(), prefix) == 0;
}

inline std::string_view trim_ascii(std::string_view value)
{
    while (!value.empty() && (value.front() == ' ' || value.front() == '\r' || value.front() == '\n' || value.front() == '\t')) {
        value.remove_prefix(1);
    }
    while (!value.empty() && (value.back() == ' ' || value.back() == '\r' || value.back() == '\n' || value.back() == '\t')) {
        value.remove_suffix(1);
    }
    return value;
}

inline std::string_view find_line(std::string_view response, std::string_view prefix)
{
    const auto pos = response.find(prefix);
    if (pos == std::string_view::npos) {
        return {};
    }
    const auto end = response.find('\n', pos);
    return trim_ascii(response.substr(pos, end == std::string_view::npos ? response.size() - pos : end - pos));
}

inline std::vector<std::string_view> split_csv(std::string_view input)
{
    std::vector<std::string_view> fields;
    size_t field_start = 0;
    bool in_quotes = false;

    for (size_t i = 0; i <= input.size(); ++i) {
        if (i == input.size()) {
            fields.emplace_back(trim_ascii(input.substr(field_start)));
            break;
        }

        if (input[i] == '"') {
            if (in_quotes && i + 1 < input.size() && input[i + 1] == '"') {
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
            continue;
        }

        if (input[i] == ',' && !in_quotes) {
            fields.emplace_back(trim_ascii(input.substr(field_start, i - field_start)));
            field_start = i + 1;
        }
    }

    return fields;
}

inline std::string unquote(std::string_view input)
{
    input = trim_ascii(input);
    if (input.size() >= 2 && input.front() == '"' && input.back() == '"') {
        input.remove_prefix(1);
        input.remove_suffix(1);
    }

    std::string output;
    output.reserve(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '"' && i + 1 < input.size() && input[i + 1] == '"') {
            output.push_back('"');
            ++i;
            continue;
        }
        if (input[i] == '\\' && i + 1 < input.size()) {
            output.push_back(input[i + 1]);
            ++i;
            continue;
        }
        output.push_back(input[i]);
    }
    return output;
}

template <typename IntT>
inline bool parse_integer(std::string_view input, IntT &output)
{
    input = trim_ascii(input);
    if (input.empty()) {
        return false;
    }
    const auto *begin = input.data();
    const auto *end = begin + input.size();
    const auto result = std::from_chars(begin, end, output);
    return result.ec == std::errc() && result.ptr == end;
}

inline bool parse_double(std::string_view input, double &output)
{
    input = trim_ascii(input);
    if (input.empty()) {
        return false;
    }
    const auto copy = std::string(input);
    char *end = nullptr;
    output = std::strtod(copy.c_str(), &end);
    return end == copy.c_str() + copy.size();
}

} // namespace a7670e::detail
