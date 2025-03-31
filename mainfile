CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Target executable
TARGET = game

# Source files (only .cpp files, excluding header-only templates)
SRCS = main.cpp Story.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)