#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <algorithm>
#include <numeric>

// https://adventofcode.com/2025/day/1

namespace Day1 {

constexpr char input_data[] = {
#embed "../../input/day_1.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

struct Move { int delta; int rotations; };

constexpr Move parseMove(const std::string& line) {
    int number = aoc::utils::parseNumber<int>(line.substr(1));
    return {
        .delta = (line[0] == 'L') ? (100 - number % 100) % 100 : number % 100,
        .rotations = number / 100
    };
}

constexpr std::vector<Move> parseMoves(std::string_view input) {
    auto lines = aoc::utils::split(input, '\n');
    std::vector<Move> moves;
    moves.reserve(lines.size());
    std::ranges::transform(lines, std::back_inserter(moves), parseMove);
    return moves;
}

consteval int solvePart1(std::string_view input) {
    auto moves = parseMoves(input);

    auto dialPositions = std::vector<int>{};
    dialPositions.reserve(moves.size());
    std::inclusive_scan(moves.begin(), moves.end(), std::back_inserter(dialPositions),
        [](int dial, Move m) { return (dial + m.delta) % 100; }, 50);

    return std::ranges::count(dialPositions, 0);
}

consteval int solvePart2(std::string_view input) {
    auto moves = parseMoves(input);
    return std::accumulate(moves.begin(), moves.end(), 0,
        [](int total, Move m) { return total + m.rotations; });
}

constexpr int part1_answer = solvePart1(input_string_view);
constexpr int part2_answer = solvePart2(input_string_view);

} // namespace Day1

std::string checkDay01([[maybe_unused]] std::string_view inputContent) {
    static_assert(Day1::part1_answer == 1029);
    static_assert(Day1::part2_answer == 3864);
    return ""; // TODO: change signature to () -> void and call it checkDayXY() for all days
}

REGISTER_DAY(1, checkDay01);
