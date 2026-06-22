SHELL := /bin/bash
FLAGS = -Wall -Werror -Wextra
FILE=test_files/*.txt
CHECK=2>&1 valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all

all: s21_cat
s21_cat: clean
	gcc $(FLAGS) s21_cat.c -o s21_cat

testing: tests tests_leaks

tests:
	@echo "Running flag tests..."
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))

tests_leaks:
	@echo "Running Valgrind tests..."\
	$(CHECK) ./s21_cat -n $(FILE) || exit 0
	$(CHECK) ./s21_cat -e $(FILE) || exit 0
	$(CHECK) ./s21_cat -t $(FILE) || exit 0
	$(CHECK) ./s21_cat -b $(FILE) || exit 0
	$(CHECK) ./s21_cat -s $(FILE) || exit 0
	$(CHECK) ./s21_cat $(FILE) || exit 0
	$(CHECK) ./s21_cat non_ex.txt || exit 0
	$(CHECK) ./s21_cat -s non_ex.txt || exit 0

clean:
	rm -f s21_cat