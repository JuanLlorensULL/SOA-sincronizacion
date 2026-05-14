CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O0 -g -pthread
INCLUDES := -Iinclude

SRC_DIR  := src
OBJ_DIR  := build
DOC_DIR  := docs

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := prodcons

.PHONY: all clean valgrind run-caso1 run-caso2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

-include $(DEPS)

run-caso1: $(TARGET)
	./$(TARGET) --items 30 --buffer 5 --prod-sleep 100 --cons-sleep 300

run-caso2: $(TARGET)
	./$(TARGET) --items 30 --buffer 5 --prod-sleep 300 --cons-sleep 100

valgrind: $(TARGET) | $(DOC_DIR)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	         --error-exitcode=1 ./$(TARGET) --items 30 --buffer 5 \
	         > /dev/null 2> $(DOC_DIR)/valgrind.log

$(DOC_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
