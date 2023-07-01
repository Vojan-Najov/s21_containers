TEST = test

CXX = g++
RMDIR = rm -rf
RM = rm -f
MKDIR = mkdir -p

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_LIBS = -lgtest

INCLUDE_DIR = ./include
TEST_SRC_DIR = ./tests
TEST_OBJ_DIR = $(TEST_SRC_DIR)/obj

INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cc)
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.cc=.o)))

echo:
	@echo $(TEST_SRC)
	@echo $(TEST_OBJ)
	@echo $(INCLUDE_DIR)

$(TEST): $(TEST_OBJ)
	$(CXX) -g -o $@ $? $(TEST_LIBS)
	./$(TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

format:
	cp materials/linters/.clang-format .
	clang-format -i include/*.h
	rm .clang-format

clean:
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) $(TEST)

.PHONY: format clean $(TEST)

