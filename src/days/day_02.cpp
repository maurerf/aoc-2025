#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <tuple>
#include <numeric>
#include <ranges>

// https://adventofcode.com/2025/day/2

enum class Part {
    ONE,
    TWO
};

constexpr std::vector<std::tuple<long, long>> parseRanges(std::string_view inputRanges) {
    const std::vector<std::string> rangeStrings = aoc::utils::split(inputRanges, ',');
    std::vector<std::tuple<long, long>> ranges;
    for (const auto& rangeStr : rangeStrings) {
        const auto bounds = aoc::utils::split(rangeStr, '-');
        if (bounds.size() == 2) {
            const long start = aoc::utils::parseNumber<long>(bounds[0]);
            const long end = aoc::utils::parseNumber<long>(bounds[1]);
            ranges.emplace_back(start, end);
        }
    }
    return ranges;
}

template <Part part>
constexpr bool isIllegalID(long id)
{
    if constexpr(part == Part::ONE) {
        // Part 1: An ID X is illegal iff any Y exists such that X = YY.
        const std::string idStr = std::to_string(id);
        const size_t len = idStr.length();
        if (len % 2 == 0) {
            const std::string firstHalf = idStr.substr(0, len / 2);
            const std::string secondHalf = idStr.substr(len / 2);
            return firstHalf == secondHalf;
        } 
        return false;
    }
    else {
        // Part 2: An ID X is illegal iff any Y exists such that X = Y^n for n >= 1.
        const std::string idStr = std::to_string(id);
        const size_t len = idStr.length();
        // TODO: refactor this using std::views
        for (size_t subLen = 1; subLen <= len / 2; ++subLen) {
            if (len % subLen == 0) {
                const std::string subStr = idStr.substr(0, subLen);
                size_t repeatCount = len / subLen;
                std::string constructed;
                for (size_t i = 0; i < repeatCount; ++i) {
                    constructed += subStr;
                }
                if (constructed == idStr) {
                    return true;
                }
            }
        }
        return false;
    }    
}

template<Part part>
constexpr long illegalIDSum(const std::tuple<long, long>& range)
{
    const auto [start, end] = range;
    const auto iota = std::views::iota(start, end + 1);
    const long sum = std::accumulate(
        iota.begin(), iota.end(), 0L,
        [](long acc, long id) constexpr {
            return acc + (isIllegalID<part>(id) ? id : 0L);
        }
    );
    return sum;
}

template<Part part>
constexpr std::string solveDay02_Parts(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    const auto ranges = parseRanges(lines[0]);

    const auto totalIllegalSum = std::accumulate(
        ranges.begin(), ranges.end(), 0L,
        [](long acc, const std::tuple<long, long>& range) constexpr {
            return acc + illegalIDSum<part>(range);
        }
    );

    return std::to_string(totalIllegalSum);
}

constexpr std::string solveDay02(std::string_view inputContent) {
    const auto part1Result = solveDay02_Parts<Part::ONE>(inputContent);
    const auto part2Result = solveDay02_Parts<Part::TWO>(inputContent);

    return "Part 1:\n" + part1Result + "\nPart 2:\n" + part2Result + "\n";
}

// Register this day's solution
REGISTER_DAY(2, solveDay02);
