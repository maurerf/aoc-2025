#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <numeric>
#include <ranges>

// https://adventofcode.com/2025/day/1

class DialState {
    private:
        int _dial;
        int _full_rotation_count;
    public:
        constexpr DialState(int number, int full_rotation_count = 0) {
            _dial = number % 100;
            _full_rotation_count = full_rotation_count;
        }

        constexpr DialState(std::string_view str){
            // Assume format R/L XY where R=right, L=left, XY= one to two digit number
            const char direction = str[0];
            const int number_raw = aoc::utils::parseNumber<int>(str.substr(1));
            const int number = (direction == 'L') ? (100 - number_raw) : number_raw;
            _dial = number % 100;
            _full_rotation_count = number_raw > 0 ? number_raw / 100 : number_raw / -100;
        }
        constexpr DialState operator+(DialState other_number) const {
            return DialState(_dial + other_number._dial); 
        }

        constexpr int getFullRotationCount() const { return _full_rotation_count; }

        constexpr bool operator==(const DialState& other) const {
            return _dial == other._dial;
        }
};

constexpr std::string solveDay01_Part1(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    const DialState dial_start{50};
    const auto moves = lines
        | std::views::transform([](const std::string& line) { return DialState{line}; });

    std::vector<DialState> positions;
    positions.reserve( lines.size() );
    std::inclusive_scan(moves.begin(), moves.end(), std::back_inserter(positions), 
        std::plus<DialState>{}, dial_start);

    const auto zero_count = std::ranges::count(positions, DialState{0});

    return std::to_string(zero_count);
}

// TODO: Fix for moves of length less than 100
constexpr std::string solveDay01_Part2(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    const auto moves = lines
        | std::views::transform([](const std::string& line) { return DialState{line}; });


    const auto total_full_dial_count = std::accumulate(
        moves.begin(), moves.end(), 0,
        [](int acc, const DialState& move) {
            return acc + move.getFullRotationCount();
        }
    );

    return std::to_string(total_full_dial_count);
}

constexpr std::string solveDay01(std::string_view inputContent) {
    const auto part1_result = solveDay01_Part1(inputContent);
    const auto part2_result = solveDay01_Part2(inputContent);
    
    return "Part 1: " + part1_result + "\nPart 2: " + part2_result + "\n";
}

// Register this day's solution
REGISTER_DAY(1, solveDay01);
