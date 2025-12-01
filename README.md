# Advent of Code 2025 - C++ Solutions

This project contains C++ solutions for Advent of Code 2025 challenges.

## Project Structure

```
├── src/
│   ├── days/          # Daily challenge solutions
│   ├── utils/         # Utility functions
│   └── main.cpp       # Main entry point
├── input/             # Input files for challenges
├── build/             # Build output directory
├── .gitignore         # Git ignore file
├── Makefile           # Build configuration
└── README.md          # This file
```

## Building the Project

### Prerequisites
- C++17 compatible compiler (g++, clang++)
- Make

### Build Instructions

```bash
make           # Build the project
make clean     # Clean build files
make debug     # Build with debug symbols
```

## Running Solutions

After building, run specific day solutions:

```bash
./aoc2025 <day_number>
```

Example:
```bash
./aoc2025 1       # Run day 1 solution
./aoc2025 list    # List all available days
make run DAY=1    # Alternative way to run day 1
```

## Adding New Days

1. Create `src/days/day_XX.cpp` for the solution
2. Add input file as `input/day_XX.txt`
3. The day auto-registers itself (no manual registry needed)

## Utilities

The `src/utils/` directory contains:
- `readLines()` for file reading when needed
- Add more utilities as you need them for your solutions

Happy coding and good luck with AoC 2025! 🎄