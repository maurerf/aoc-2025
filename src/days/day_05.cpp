#include <cstdint>
#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <tuple>
#include <numeric>

// https://adventofcode.com/2025/day/5

namespace Day5 {

constexpr char input_data[] = {
#embed "../../input/day_5.txt"
};
constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

consteval int64_t solveDay05_Part1(const std::vector<std::tuple<int64_t, int64_t>> fresh_ranges, const std::vector<int64_t> ids) {
    const auto fresh_count = std::accumulate(
            ids.begin(), ids.end(), int64_t{0},
            [&fresh_ranges](int64_t acc, int64_t id) constexpr {
                const bool is_fresh = std::ranges::any_of(
                    fresh_ranges,
                    [id](const std::tuple<int64_t, int64_t>& range) constexpr {
                        const auto [start, end] = range;
                        return id >= start && id <= end;
                    }
                );
                return acc + (is_fresh ? 1 : 0);
            }
        );

    return fresh_count;
}

consteval int64_t solveDay05_Part2(const std::vector<std::tuple<int64_t, int64_t>> fresh_ranges) {
    // Sort ranges and merge overlapping ones
    std::vector<std::tuple<int64_t, int64_t>> sorted_ranges = fresh_ranges;
    std::sort(sorted_ranges.begin(), sorted_ranges.end(),
        [](const auto& a, const auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        }
    );
    
    std::vector<std::tuple<int64_t, int64_t>> merged_ranges;;
    for (const auto& range : sorted_ranges) {
        if (merged_ranges.empty()) {
            merged_ranges.push_back(range);
        } else {
            auto& last_range = merged_ranges.back();
            if (std::get<0>(range) <= std::get<1>(last_range)) {
                std::get<1>(last_range) = std::max(std::get<1>(last_range), std::get<1>(range));
            } else {
                merged_ranges.push_back(range);
            }
        }
    }

    const auto total_fresh_count = std::accumulate(
        merged_ranges.begin(), merged_ranges.end(), int64_t{0},
        [](int64_t acc, const std::tuple<int64_t, int64_t>& range) constexpr {
            const auto [start, end] = range;
            return acc + (end - start + 1);
        }
    );
    
    
    return total_fresh_count;
}

consteval std::tuple<int64_t, int64_t> solveDay05(std::string_view inputContent) {
    const auto blocks = aoc::utils::split(inputContent, "\n\n");
    
    const auto fresh_ranges_lines = aoc::utils::split(blocks[0], '\n');
    const auto ids_lines = aoc::utils::split(blocks[1], '\n');

    const std::vector<std::tuple<int64_t, int64_t>> fresh_ranges = aoc::utils::parseRange<int64_t>(fresh_ranges_lines);
    const std::vector<int64_t> ids = aoc::utils::parseNumbers<int64_t>(ids_lines);

    const auto part1_result = solveDay05_Part1(fresh_ranges, ids);
    const auto part2_result = solveDay05_Part2(fresh_ranges);

    return {part1_result, part2_result};
}

constexpr auto answers = solveDay05(input_string_view);
constexpr int64_t part1_answer = std::get<0>(answers);
constexpr int64_t part2_answer = std::get<1>(answers);

} // namespace Day5

void checkDay05() {
    static_assert(Day5::part1_answer == 607);
    static_assert(Day5::part2_answer == 342433357244012);
}

// Register this day's solution
REGISTER_DAY(5, checkDay05);
