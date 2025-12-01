#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace aoc {
namespace utils {

    // File I/O operations - not constexpr :(
     
    std::vector<std::string> readLines(std::string_view filename);
    std::optional<std::string> readFile(std::string_view filename) noexcept;

}
}
