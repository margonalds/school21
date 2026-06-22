CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TARGET_LIB = s21_matrix.a
CHECK_LIBS = -lm -lpthread $(shell pkg-config --libs check)

SRC_FILES = s21_matrix.c s21_utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

TESTS_DIR = tests
TESTS = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJS = $(patsubst $(TESTS_DIR)/%.c,$(TESTS_DIR)/%.o,$(TESTS))

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

test: CFLAGS += $(GCOV_FLAGS)
test: $(TARGET_LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o test_runner $(TEST_OBJS) $(TARGET_LIB) $(CHECK_LIBS)
	./test_runner

gcov_report: test 
	@echo "Generating gcov report..."
	lcov --capture --directory . --output-file coverage.info --include '*.c' 
	genhtml coverage.info --output-directory gcov_report

clean:
	rm -f *.o $(TARGET_LIB) test_runner *.gcda *.gcno *.gcov coverage.info
	rm -rf gcov_report $(TESTS_DIR)/*.o $(TESTS_DIR)/*.gcda $(TESTS_DIR)/*.gcno $(TESTS_DIR)/*.gcov

.PHONY: all test gcov_report clean
