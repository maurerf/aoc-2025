#include "aoc.h"
#include <iostream>
#include <string>

// Day solution declarations will be linked automatically
// No need to include .cpp files here

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <day_number>\n"
                  << "       " << argv[0] << " list\n";
        return 1;
    }

    const std::string arg = argv[1];
    
    if (arg == "list") {
        aoc::SolutionRegistry::listDays();
        return 0;
    }

    try {
        const int day = std::stoi(arg);
        aoc::SolutionRegistry::runDay(day);
    } catch (const std::exception&) {
        std::cerr << "Invalid day number: " << arg << '\n';
        return 1;
    }

    return 0;
}
