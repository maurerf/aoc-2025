#include <cstddef>
#include <cstdint>
#include <numeric>
#include "../aoc.h"
#include "../utils/constexpr_utils.h"

// https://adventofcode.com/2025/day/3

constexpr int64_t int64_pow(int64_t base, int exp) {
    if (exp == 0) return 1;    
    return base * int64_pow(base, exp - 1);
}

constexpr int64_t maxJoltage(std::string_view joltageString, int digit_count = 2) {
    // Current digit: max digit, but not the last digit_count - 1 digits
    const auto current_digit_it = std::ranges::max_element(
        joltageString.begin(),
        joltageString.end() - (digit_count - 1),
        {/*default comparator*/},
        [](char c) constexpr { return c - '0'; } 
    );

    const auto current_digit = static_cast<int64_t>(*current_digit_it - '0');

    if (digit_count == 1) {
        return current_digit;
    }

    const size_t current_digit_index = static_cast<size_t>(current_digit_it - joltageString.begin());
    const int64_t recursive_result = maxJoltage(
        joltageString.substr(current_digit_index + 1),
        digit_count - 1
    );
    
    const int64_t power_of_10 = int64_pow(10L, digit_count - 1);
    const int64_t current_digit_contribution = power_of_10 * current_digit;
    return current_digit_contribution + recursive_result;
}

constexpr std::string solveDay_03_BothParts(std::string_view inputContent, int digit_count = 2) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    const int64_t totalJoltage = std::accumulate(
        lines.begin(), lines.end(), int64_t{0},
        [digit_count](int64_t acc, const std::string& line) constexpr {
            const int64_t line_result = maxJoltage(line, digit_count);
            return acc + line_result;
        }
    );
    return std::to_string(totalJoltage);
}

constexpr std::string solveDay03(std::string_view inputContent) {
    const auto part1 = solveDay_03_BothParts(inputContent, 2);
    const auto part2 = solveDay_03_BothParts(inputContent,12);
    return "Part 1: " + part1 + "\nPart 2: " + part2 + "\n";
}

// Register this day's solution
REGISTER_DAY(3, solveDay03);
