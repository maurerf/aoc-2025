#include "aoc.h"
#include "utils/parsing.h"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <optional>

namespace aoc {

    std::vector<DaySolver> SolutionRegistry::solvers_(13);

    void SolutionRegistry::registerDay(int day, DaySolver solver) {
        if (day >= 1 && day <= maxDays()) {
            solvers_[day] = std::move(solver);
        }
    }

    bool SolutionRegistry::runDay(int day) noexcept {
        // Pure validation with optional
        const auto validateDay = [](int d) -> std::optional<int> {
            return (d >= 1 && d <= maxDays()) ? std::make_optional(d) : std::nullopt;
        };
        
        // Pure solver lookup
        const auto getSolver = [](int d) -> std::optional<DaySolver> {
            return solvers_[d] ? std::make_optional(solvers_[d]) : std::nullopt;
        };
        
        // Pure file content reading
        const auto readInputContent = [](int d) -> std::optional<std::string> {
            const auto path = std::filesystem::path{"input"} / ("day_" + std::to_string(d) + ".txt");
            if (std::filesystem::exists(path)) {
                return aoc::utils::readFile(path.string());
            }
            return std::nullopt;
        };
        
        // Monadic chain with early returns
        if (const auto valid_day = validateDay(day)) {
            if (const auto solver = getSolver(*valid_day)) {
                if (const auto content = readInputContent(*valid_day)) {
                    if (content->empty()) {
                        std::cerr << "Input file is empty for day " << day << "\n";
                        return false;
                    }
                    std::cout << "=== Advent of Code 2025 - Day " << day << " ===\n";
                    try {
                        const auto result = (*solver)(*content);
                        std::cout << result;
                        return true;
                    } catch (const std::exception& e) {
                        std::cerr << "Error running day " << day << ": " << e.what() << "\n";
                        return false;
                    }
                } else {
                    std::cerr << "Input file not found for day " << day << "\n";
                }
            } else {
                std::cerr << "Day " << day << " not implemented yet!\n";
            }
        } else {
            std::cerr << "Invalid day: " << day << " (must be 1-" << maxDays() << ")\n";
        }
        
        return false;
    }

    void SolutionRegistry::listDays() noexcept {
        std::cout << "Available days:\n";
        for (int i = 1; i <= maxDays(); ++i) {
            if (solvers_[i]) {
                std::cout << "  Day " << std::setw(2) << i << " ✓\n";
            }
        }
    }

}
