CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g -O0
COVERAGE_FLAGS = --coverage
LIB_NAME = s21_string.a
SRC_DIR = string_functions
BUILD_DIR = ../materials/build
GCOV_DIR = $(BUILD_DIR)/gcov
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
COVERAGE_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/coverage_%.o, $(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/s21_test_*.c)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_FILES))

.PHONY: all clean s21_string.a test gcov_report

all: s21_string.a

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/coverage_%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)

$(BUILD_DIR)/coverage_$(LIB_NAME): $(COVERAGE_OBJ_FILES)
	ar rcs $@ $(COVERAGE_OBJ_FILES)

s21_string.a: $(BUILD_DIR)/$(LIB_NAME)
	cp $< $@

test: s21_string.a $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do ./$$test || exit 1; done

$(BUILD_DIR)/%: $(TEST_DIR)/%.c s21_string.a | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ -L$(BUILD_DIR) -l:s21_string.a -lcheck -lsubunit -pthread -lrt -lm

$(BUILD_DIR)/coverage_%: $(TEST_DIR)/%.c $(BUILD_DIR)/coverage_$(LIB_NAME) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $< -o $@ -L$(BUILD_DIR) -l:coverage_$(LIB_NAME) -lcheck -lsubunit -pthread -lrt -lm

clang_format:
	clang-format -n *.h $(SRC_DIR)/*.c $(TEST_DIR)/*.c

gcov_report: $(BUILD_DIR)/coverage_$(LIB_NAME) $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/coverage_%, $(TEST_FILES))
	@for test in $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/coverage_%, $(TEST_FILES)); do ./$$test || exit 1; done
	@mkdir -p $(GCOV_DIR)
	@echo "Generating gcov report..."
	@find $(BUILD_DIR) -name "*.gcda" -exec gcov -o $(BUILD_DIR) {} +
	@echo "Generated .gcov files:"
	@find $(BUILD_DIR) -name "*.gcov"
	@lcov --directory $(BUILD_DIR) --capture --output-file $(GCOV_DIR)/coverage.info
	@genhtml $(GCOV_DIR)/coverage.info --output-directory $(GCOV_DIR)/html
	@echo "Coverage report generated at $(GCOV_DIR)/html/index.html"
	rm -rf $(BUILD_DIR)/*.gcno $(BUILD_DIR)/*.gcda *.gcov

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/s21_test_* $(BUILD_DIR)/$(LIB_NAME) $(BUILD_DIR)/coverage_* $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno $(BUILD_DIR)/$(SRC_DIR)/*.gcno $(BUILD_DIR)/$(SRC_DIR)/*.o $(BUILD_DIR)/$(SRC_DIR) $(LIB_NAME) $(GCOV_DIR)

