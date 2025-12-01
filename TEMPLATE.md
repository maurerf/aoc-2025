# Day Template for Advent of Code

Copy this template to create new day solutions:

```cpp
#include "../aoc.h"
#include "../utils/constexpr_utils.h"
#include <algorithm>
#include <numeric>

constexpr std::string solveDayXX(std::string_view inputContent) {
    const auto lines = aoc::utils::split(inputContent, '\n');
    
    if (lines.empty()) {
        return "No input data found\\n";
    }
    
    const auto part1_result = [&lines]() constexpr -> long {
        // TODO: Implement Part 1 solution here
        return 0L;
    }();
    
    const auto part2_result = [&lines]() constexpr -> long {
        // TODO: Implement Part 2 solution here  
        return 0L;
    }();
    
    return "Processing " + std::to_string(lines.size()) + " lines...\\n" +
           "Part 1: " + std::to_string(part1_result) + "\\n" +
           "Part 2: " + std::to_string(part2_result) + "\\n";
}

// Register this day's solution
REGISTER_DAY(XX, solveDayXX);
```

## Steps to add a new day:

1. Copy the template above
2. Replace XX with the day number
3. Save as `src/days/day_XX.cpp`
4. Add input file as `input/day_XX.txt`
5. Rebuild the project with `make`