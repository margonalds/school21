CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror $(shell pkg-config --cflags check)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
AR = ar
ARFLAGS = rcs
TARGET_LIB = s21_decimal.a
CHECK_LIBS = -lm -lpthread $(shell pkg-config --libs check)
SRC_FILES = s21_convertors.c s21_other.c s21_utils.c s21_math.c s21_compare.c s21_helpers.c
OBJ_FILES = $(SRC_FILES:.c=.o)
TESTS_DIR = tests
TESTS = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJS = $(patsubst %.c,%.o,$(TESTS))

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c s21_decimal.h
	$(CC) $(CFLAGS) -c $< -o $@

test: CFLAGS += $(GCOV_FLAGS)
test: $(TARGET_LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o test_runner $(TEST_OBJS) $(TARGET_LIB) $(CHECK_LIBS)
	./test_runner

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c s21_decimal.h
	$(CC) $(CFLAGS) -c $< -o $@

# gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: test
	@echo "Generating gcov report..."
	gcov -o . $(SRC_FILES) $(TESTS)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

clean:
	rm -f *.o $(TARGET_LIB) test_runner *.gcda *.gcno *.gcov coverage.info
	rm -rf gcov_report $(TESTS_DIR)/*.o $(TESTS_DIR)/*.gcda $(TESTS_DIR)/*.gcno $(TESTS_DIR)/*.gcov

.PHONY: all test gcov_report clean

