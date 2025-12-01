#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <functional>

namespace aoc {

    // DaySolver takes file content, not file path
    using DaySolver = std::function<std::string(std::string_view)>;

    class SolutionRegistry {
    public:
        static void registerDay(int day, DaySolver solver);
        static bool runDay(int day) noexcept;
        static void listDays() noexcept;
        static constexpr int maxDays() noexcept { return 12; }
        
    private:
        static std::vector<DaySolver> solvers_;
    };

    // Helper macro to register day solutions
    #define REGISTER_DAY(day_num, solver_func) \
        namespace { \
            struct DayRegistrar##day_num { \
                DayRegistrar##day_num() { \
                    aoc::SolutionRegistry::registerDay(day_num, solver_func); \
                } \
            }; \
            static DayRegistrar##day_num registrar##day_num; \
        }

}
