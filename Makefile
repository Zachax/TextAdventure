# Compiler options
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
CXX_WIN := i686-w64-mingw32-g++
CXXFLAGS_WIN := $(CXXFLAGS)
LDFLAGS_WIN := -static-libgcc -static-libstdc++

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable file names
EXEC_LINUX := $(BIN_DIR)/textgame
EXEC_WINDOWS := $(BIN_DIR)/textgame.exe

# Determine the host platform
UNAME_S := $(shell uname -s)

# Phony targets
.PHONY: all clean

# Default target
all: $(EXEC_LINUX) $(EXEC_WINDOWS)

# Rule to compile object files for Linux
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile object files for Windows
$(OBJ_DIR)/%.wo: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX_WIN) $(CXXFLAGS_WIN) -c $< -o $@

# Rule to link the Linux executable
$(EXEC_LINUX): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to cross-compile the Windows executable
$(EXEC_WINDOWS): $(OBJS:.o=.wo)
	$(CXX_WIN) $(CXXFLAGS_WIN) $^ $(LDFLAGS_WIN) -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(EXEC_LINUX) $(EXEC_WINDOWS)