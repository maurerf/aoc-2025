CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
TARGET = aoc2025
SRCDIR = src
BUILDDIR = build

# Find all source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILDDIR) $(BUILDDIR)/days $(BUILDDIR)/utils)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Run with day number (make run DAY=1)
run: $(TARGET)
	./$(TARGET) $(DAY)

# List available days
list: $(TARGET)
	./$(TARGET) list

.PHONY: all clean debug run list