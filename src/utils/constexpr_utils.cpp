#include "constexpr_utils.h"

// All constexpr functions are implemented in the header file
// This file exists to ensure proper compilation and linking

namespace aoc {
namespace utils {
    // Template instantiations for common types
    template int parseNumber<int>(std::string_view) noexcept;
    template long parseNumber<long>(std::string_view) noexcept;
    template long long parseNumber<long long>(std::string_view) noexcept;
    
    template std::vector<int> parseNumbers<int>(const std::vector<std::string>&);
    template std::vector<long> parseNumbers<long>(const std::vector<std::string>&);
    template std::vector<long long> parseNumbers<long long>(const std::vector<std::string>&);
}
}
