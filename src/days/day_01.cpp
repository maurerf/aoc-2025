#include "../aoc.h"
#include "../utils/constexpr_utils.h"

constexpr std::string solveDay01(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    const auto first_line = lines.empty() ? "" : lines[0];
    return first_line.empty() ? "Day 01: No input data\n" : "Day 01: First line is '" + first_line + "'\n";
}

// Register this day's solution
REGISTER_DAY(1, solveDay01);
