#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include "../utils/parsing.h"

// https://adventofcode.com/2025/day/4


#include <cstddef>
#include <vector>
#include <array>

namespace Day4 {

constexpr char input_data[] = {
#embed "../../input/day_4.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

enum class Part {
    ONE,
    TWO
};

constexpr auto countAdjacentPaperRolls(int x, int y, const std::vector<std::vector<bool>>& wall) {
    if (wall.empty()) return 0L;
    
    const auto rows = static_cast<int>(wall.size());
    const auto cols = static_cast<int>(wall[0].size());
    
    constexpr std::array<std::pair<int,int>, 8> deltas{{
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    }}; // std::cartesian_product would be nice here, but its C++23
    
    return std::ranges::count_if(deltas, [&](auto d) {
        const int nx = x + d.second;
        const int ny = y + d.first;
        return nx >= 0 && nx < cols 
            && ny >= 0 && ny < rows 
            && wall[static_cast<size_t>(ny)][static_cast<size_t>(nx)];
    });
}

// TODO: functional approach with views and no copyWall
template<Part part>
constexpr long processWall(std::vector<std::vector<bool>> wall) {
    auto copyWall = wall; 
     
    int ans = 0;
    for (size_t y = 0; y < wall.size(); ++y) {
        for (size_t x = 0; x < wall[y].size(); ++x) {
            if (wall[y][x]) {
                const auto adjacent_rolls = countAdjacentPaperRolls(static_cast<int>(x), static_cast<int>(y), wall);
                if(adjacent_rolls < 4) {
                    ++ans;
                    copyWall[y][x] = false;
                }
            }
        }
    }
    
    if constexpr(part == Part::TWO) {
        if(ans > 0) {
            ans += processWall<Part::TWO>(std::move(copyWall));
        }
    }

    return ans;
}

// TODO: functional approach with views for input parsing
template<Part part>
constexpr long solveDay04_BothParts(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    
    std::vector<std::vector<bool>> wall;

    for (const auto& line : lines) {
        std::vector<bool> row;
        row.reserve(line.size());
        for (const char c : line) {
            row.push_back(c == '@');
        }
        wall.push_back(std::move(row));
    }

    const auto ans = processWall<part>(std::move(wall));
    
    return ans;
}

// Part 1 fits within constexpr step limit
constexpr long part1_answer = solveDay04_BothParts<Part::ONE>(input_string_view);

} // namespace Day4

void checkDay04() {
    static_assert(Day4::part1_answer == 1604);
    
    // TODO: Refactor Part 2 to compile-time evaluation: currently very slow
    const auto inputContent = *aoc::utils::readFile("input/day_4.txt");
    const long part2_answer = Day4::solveDay04_BothParts<Day4::Part::TWO>(inputContent);
    if (part2_answer != 9397) {
        throw std::runtime_error("Day 04 Part 2 check failed");
    }
}

// Register this day's solution
REGISTER_DAY(4, checkDay04);
