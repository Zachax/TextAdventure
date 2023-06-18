# Compiler options
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable file
EXEC := $(BIN_DIR)/textgame

# Phony targets
.PHONY: all clean

# Default target
all: $(EXEC)

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(EXEC)