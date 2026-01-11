#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

// https://adventofcode.com/2025/day/7

namespace Day7 {

constexpr char input_data[] = {
#embed "../../input/day_7.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

constexpr std::tuple<std::vector<bool>, size_t, std::vector<size_t>> parseLine(const std::string& line, const std::vector<bool> prev_beam, const std::vector<size_t>& prev_timelines_at_index) {
    if(line.length() != prev_beam.size()) {
        throw std::runtime_error("Line length does not match beam length");
    }
    std::vector<bool> new_beam = prev_beam;
    std::vector<size_t> timeslines_at_index = prev_timelines_at_index;
    size_t splitters_count = 0;
    for(size_t i = 0; i < line.length(); ++i) {
        if(line[i] == 'S') { // beam source
            new_beam[i] = true;
            timeslines_at_index[i]++;
        } else if (line[i] == '^' && prev_beam[i]) { // beam splitter
            new_beam[i] = false;
            new_beam[i - 1] = true;
            new_beam[i + 1] = true;
            splitters_count++;
            timeslines_at_index[i - 1] += timeslines_at_index[i];
            timeslines_at_index[i + 1] += timeslines_at_index[i];
            timeslines_at_index[i] = 0;
        }
    }

    return {new_beam, splitters_count, timeslines_at_index};
}

constexpr int64_t solveDay07_Part1(const std::vector<std::string>& lines) {
    auto beam = std::vector<bool>(lines[0].length(), false);
    int64_t ans = 0;
    for (const auto& line : lines) {
        auto [new_beam, splitters_count, _] = parseLine(line, beam, std::vector<size_t>(beam.size(), 0) /* not used in part 1*/);
        beam = new_beam;
        ans += splitters_count;
    }
    return ans;
}

constexpr int64_t solveDay07_Part2(const std::vector<std::string>& lines) {
    auto beam = std::vector<bool>(lines[0].length(), false);
    std::vector<size_t> timeslines_at_index(beam.size(), 0);
    for (const auto& line : lines) {
        auto [new_beam, splitters_count, new_timeslines_at_index] = parseLine(line, beam, timeslines_at_index);
        beam = new_beam;
        timeslines_at_index = new_timeslines_at_index;
    }
    int64_t ans = 0;
    for (const auto& count : timeslines_at_index) {
        ans += count;
    }
    return ans;
}

consteval std::tuple<int64_t, int64_t> solveDay07(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n', true);

    const auto part1 = solveDay07_Part1(lines);
    const auto part2 = solveDay07_Part2(lines);

    return {part1, part2};
}

constexpr auto answers = solveDay07(input_string_view);
constexpr int64_t part1_answer = std::get<0>(answers);
constexpr int64_t part2_answer = std::get<1>(answers);

void checkDay07() {
    static_assert(part1_answer == 1613);
    static_assert(part2_answer == 48021610271997);
}

// Register this day's solution
REGISTER_DAY(7, checkDay07);

} // namespace Day7
