#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <tuple>

// https://adventofcode.com/2025/day/6

namespace Day6 {

constexpr char input_data[] = {
#embed "../../input/day_6.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

constexpr long long solveDay06_Part1(const std::vector<std::vector<std::string>>& grid) {
    long long totalSum = 0;

    const auto& operators = grid.back();
    const size_t numCols = operators.size();

    for (size_t col = 0; col < numCols; ++col) {
        const auto& op = operators[col];
        long long colResult = (op == "*") ? 1 : 0; // Initialize based on operation

        for (size_t row = 0; row < grid.size() - 1; ++row) {            
            long long value = aoc::utils::parseNumber<long long>(grid[row][col]);
            
            if (op == "+") {
                colResult += value;
            } else if (op == "*") {
                colResult *= value;
            }
        }
        
        totalSum += colResult;
    }

    return totalSum;
}

constexpr long long solve_Day06_Part2(const std::vector<std::vector<std::string>>& grid) {
    // TODO
    return 0;
}

consteval std::tuple<long long, long long> solveDay06(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n', true);

    // Parse all lines into a 2D grid of strings
    std::vector<std::vector<std::string>> grid;
    for (const auto& line : lines) {
        auto words = aoc::utils::split(line, ' ', true);
        grid.push_back(std::move(words));
    }
    
    const auto part1 = solveDay06_Part1(grid);
    const auto part2 = solve_Day06_Part2(grid);

    return {part1, part2};
}

constexpr auto answers = solveDay06(input_string_view);
constexpr int64_t part1_answer = std::get<0>(answers);
// constexpr int64_t part2_answer = std::get<1>(answers);

void checkDay06() {
    static_assert(part1_answer == 4583860641327);
    // static_assert(part2_answer == ...);
}

// Register this day's solution
REGISTER_DAY(06, checkDay06);

} // namespace Day6