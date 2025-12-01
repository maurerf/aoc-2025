#include "parsing.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace aoc {
namespace utils {

    std::vector<std::string> readLines(std::string_view filename) {
        std::ifstream file{std::string{filename}};
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + std::string{filename});
        }
        
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.emplace_back(std::move(line));
        }
        return lines;
    }

    std::optional<std::string> readFile(std::string_view filename) noexcept {
        try {
            if (std::ifstream file{std::string{filename}}; file.is_open()) {
                return std::string{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
            }
        } catch (...) {
        }
        return std::nullopt;
    }

}
}
