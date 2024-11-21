CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra

INCLUDE_DIRS = -Iinclude -Iexternal/eigen

LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/project

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	@echo "Cleaning build directories..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	@echo "Running $(TARGET)..."
	@./$(TARGET)

check-eigen:
	@if [ ! -d "external/eigen" ]; then \
		echo "Error: Eigen directory not found in 'external/eigen'. Please download Eigen and place it there."; \
		exit 1; \
	fi

build: check-eigen all

.PHONY: all clean run check-eigen build
