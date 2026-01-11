#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <charconv>

namespace aoc {
namespace utils {

    // Pure string processing functions
    
    constexpr bool isEmptyOrWhitespace(std::string_view str) {
        if (str.empty()) return true;
        for (char c : str) {
            if (c != ' ' && c != '\t') return false;
        }
        return true;
    }

    constexpr std::vector<std::string> split(std::string_view str, char delimiter, bool skipWhitespace = false) {
        std::vector<std::string> result;
        
        for (std::string_view::size_type start = 0; start < str.length();) {
            const auto end = str.find(delimiter, start);
            if (end != std::string_view::npos) {
                auto part = str.substr(start, end - start);
                if (!(skipWhitespace && isEmptyOrWhitespace(part))) {
                    result.emplace_back(part);
                }
                start = end + 1;
            } else {
                auto part = str.substr(start);
                if (!(skipWhitespace && isEmptyOrWhitespace(part))) {
                    result.emplace_back(part);
                }
                break;
            }
        }
        return result;
    }
    
    constexpr std::vector<std::string> split(std::string_view str, std::string_view delimiter, bool skipWhitespace = false) {
        std::vector<std::string> result;
        
        for (std::string_view::size_type start = 0; start < str.length();) {
            const auto end = str.find(delimiter, start);
            if (end != std::string_view::npos) {
                auto part = str.substr(start, end - start);
                if (!(skipWhitespace && isEmptyOrWhitespace(part))) {
                    result.emplace_back(part);
                }
                start = end + delimiter.length();
            } else {
                auto part = str.substr(start);
                if (!(skipWhitespace && isEmptyOrWhitespace(part))) {
                    result.emplace_back(part);
                }
                break;
            }
        }
        return result;
    }
    
    template<typename T>
    constexpr T parseNumber(std::string_view str) noexcept {
        if (str.empty()) return T{};
        
        T result{};
        const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
        
        return ec == std::errc{} ? result : T{};
    }
    
    template<typename T>
    constexpr std::vector<T> parseNumbers(const std::vector<std::string>& lines) {
        std::vector<T> numbers;
        numbers.reserve(lines.size());
        
        const auto parseNum = [](const std::string& line) constexpr -> T {
            return parseNumber<T>(line);
        };
        
        std::transform(lines.begin(), lines.end(), std::back_inserter(numbers), parseNum);
        
        numbers.erase(
            std::remove_if(numbers.begin(), numbers.end(),
                [](const T& val) constexpr { return val == T{}; }),
            numbers.end());
        
        return numbers;
    }

    template<typename T>
    constexpr std::vector<std::tuple<T, T>> parseRange(const std::vector<std::string>& rangeStrings) {
        std::vector<std::tuple<T, T>> ranges;
        for (const auto& rStr : rangeStrings) {
            const auto bounds = split(rStr, '-');
            if (bounds.size() == 2) {
                const T start = parseNumber<T>(bounds[0]);
                const T end = parseNumber<T>(bounds[1]);
                ranges.emplace_back(start, end);
            }
        }
        return ranges;
    }
}
}
