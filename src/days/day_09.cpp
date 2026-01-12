#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <tuple>

// https://adventofcode.com/2025/day/9

namespace Day09 {

constexpr char input_data[] = {
#embed "../../input/day_9.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

template<typename T>
constexpr T constexpr_abs(T x) {
    return (x < 0) ? -x : x;
}

struct Point {
    int64_t x;
    int64_t y;
};

constexpr int64_t solveDay09_Part1(const std::vector<std::string>& lines) {
    std::vector<Point> points;
    for (const auto& line : lines) {
        const auto commaPos = line.find(',');
        const int64_t x = aoc::utils::parseNumber<int64_t>(line.substr(0, commaPos));
        const int64_t y = aoc::utils::parseNumber<int64_t>(line.substr(commaPos + 1));
        points.push_back(Point{x, y});
    }

    int64_t maxArea = 0;
    for (const auto& p1 : points) {
        for (const auto& p2 : points) {
            int64_t area = (constexpr_abs(p2.x - p1.x) + 1) * (constexpr_abs(p2.y - p1.y) + 1);
            maxArea = std::max(maxArea, area);
        }
    }
    return maxArea;
}

constexpr int64_t solveDay09_Part2(const std::vector<std::string>& lines) {
    // TODO
    return 0;
}

consteval std::tuple<int64_t, int64_t> solveDay09(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n', true);

    const auto part1 = solveDay09_Part1(lines);
    const auto part2 = solveDay09_Part2(lines);

    return {part1, part2};
}

constexpr auto answers = solveDay09(input_string_view);
constexpr int64_t part1_answer = std::get<0>(answers);
// constexpr int64_t part2_answer = std::get<1>(answers);

void checkDay09() {
    static_assert(part1_answer == 4760959496);
    // static_assert(part2_answer == ...);
}

// Register this day's solution
REGISTER_DAY(9, checkDay09);

} // namespace Day09
