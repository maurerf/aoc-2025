#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <cmath>
#include <tuple>
#include <iostream>

// https://adventofcode.com/2025/day/8

namespace Day8 {

constexpr char input_data[] = {
#embed "../../input/day_8.txt"
};

constexpr std::string_view input_string_view{input_data, sizeof(input_data)};

class Point {
    public:
        int x;
        int y;
        int z;

        constexpr size_t distanceTo(const Point& other) const {
            // squared distance (avoids non-constexpr sqrt/pow, ordering is preserved)
            int64_t dx = other.x - x;
            int64_t dy = other.y - y;
            int64_t dz = other.z - z;
            return static_cast<size_t>(dx*dx + dy*dy + dz*dz);
        }
};

enum class Part {
    ONE,
    TWO
};

template <Part part>
constexpr int64_t connectWires(const std::vector<std::string>& lines) {
    std::vector<Point> points;
    for (auto& line : lines) {
        // parse line into Point and add to points
        const Point p{
            .x = aoc::utils::parseNumber<int>(line.substr(0, line.find(','))),
            .y = aoc::utils::parseNumber<int>(line.substr(line.find(',') + 1, line.rfind(',') - line.find(',') - 1)),
            .z = aoc::utils::parseNumber<int>(line.substr(line.rfind(',') + 1))
        };
        points.push_back(p);
    }

    // compute distance matrix
    std::vector<std::vector<size_t>> distances;
    for (size_t i = 0; i < points.size(); ++i) {
        distances.push_back(std::vector<size_t>());
        for (size_t j = 0; j < points.size(); ++j) {
            if (i != j) {
                distances[i].push_back(points[i].distanceTo(points[j]));
            }
            else {
                distances[i].push_back(INT_MAX);
            }
        }
    }

    std::unordered_map<size_t, size_t> circuitMap;
    std::vector<size_t> sizes;
    size_t lastI, lastJ;

    size_t iteration = 0;
    while (true) {
        iteration++;
        // minimum distance in the matrix
        size_t minDist = INT_MAX;
        size_t minI = 0;
        size_t minJ = 0;
        for (size_t j = 0; j < distances.size(); ++j) {
            for (size_t k = 0; k < distances[j].size(); ++k) {
                if(distances[j][k] < minDist) {
                    minDist = distances[j][k];
                    minI = j;
                    minJ = k;
                }
            }
        }
        // set distance to INT_MAX to avoid picking the same points again
        distances[minI][minJ] = INT_MAX;
        distances[minJ][minI] = INT_MAX;

        if (circuitMap.count(minI) && circuitMap.count(minJ)) { 
            // Both in circuits: merge if not in same circuit already
            size_t circuitI = circuitMap[minI], circuitJ = circuitMap[minJ];
            if (circuitI != circuitJ) {
                for (auto& [key, value] : circuitMap)
                    if (value == circuitJ) value = circuitI;
            }
        } else if (circuitMap.count(minI)) { // 
            // Only minI is already in a circuit
            circuitMap[minJ]  = circuitMap[minI];
        } else if (circuitMap.count(minJ)) { 
            // Only minJ is already in a circuit
            circuitMap[minI] = circuitMap[minJ];
        } else {
            // Else add both to a new circuit
            size_t maxCircuitId = 0;
            for (const auto& [key, value] : circuitMap) {
                if (value > maxCircuitId) {
                    maxCircuitId = value;
                }
            }
            circuitMap[minI] = maxCircuitId + 1;
            circuitMap[minJ] = maxCircuitId + 1;
        }

        // Update sizes
        std::unordered_map<size_t, size_t> circuitSizes;
        for (const auto& [key, value] : circuitMap) {
            circuitSizes[value]++;
        }
        sizes.clear();
        for (const auto& [key, value] : circuitSizes) {
            sizes.push_back(value);
        }
        if constexpr (part == Part::ONE) {
            if (iteration >= 1000) break;
        } else {
            // All points must be in circuitMap AND in the same circuit
            if (circuitMap.size() == points.size() && circuitSizes.size() == 1) {
                lastI = minI;
                lastJ = minJ;
                break;
            }
        }
    }


    if constexpr(part == Part::ONE) {
        // Part ONE: Multiply the sizes of the three largest circuits.

        std::sort(sizes.begin(), sizes.end(), std::greater<size_t>());
        size_t result = 1;
        for (size_t i = 0; i < std::min(sizes.size(), static_cast<size_t>(3)); ++i) {
            result *= sizes[i];
        }
        
        return static_cast<int64_t>(result);
    } else {
        // Part TWO: Multiply the X coordinates of the last two junction boxes you need to connect so that all boxes are connected in one circuit.
        std::cout << "Last points connected: (" << points[lastI].x << ", " << points[lastI].y << ", " << points[lastI].z << ") and ("
                  << points[lastJ].x << ", " << points[lastJ].y << ", " << points[lastJ].z << ")\n";
        return static_cast<int64_t>(points[lastI].x * points[lastJ].x);
    }
}

// TODO: hits maximum constexpr step limit in part 2
// consteval std::tuple<int64_t, int64_t> solveDay08(std::string_view inputContent) {
//     const auto lines = aoc::utils::split(inputContent, '\n', true);

//     const auto part1 = connectWires<Part::ONE>(lines);
//     const auto part2 = connectWires<Part::TWO>(lines);

//     return {part1, part2};
// }

// constexpr auto answers = solveDay08(input_string_view);
// constexpr int64_t part1_answer = std::get<0>(answers);
// constexpr int64_t part2_answer = std::get<1>(answers);

// void checkDay08() {
//     static_assert(part1_answer == 57564);
//     static_assert(part2_answer == 133296744);
// }

// Register this day's solution
// REGISTER_DAY(8, checkDay08);

} // namespace Day8