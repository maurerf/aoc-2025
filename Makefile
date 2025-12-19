CXX = g++
CXXFLAGS = -std=c++2b -Wall -Wextra -Wno-c23-extensions -O0 -fconstexpr-steps=10000000
TARGET = build/aoc2025
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
	rm -rf $(BUILDDIR)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean debug