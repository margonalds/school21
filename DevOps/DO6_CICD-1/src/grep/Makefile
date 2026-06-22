SHELL := /bin/bash
FLAG = -Wall -Werror -Wextra
FILE=test_files/*.txt
CHECK=2>&1 valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all

all: s21_grep
s21_grep: clean
	gcc $(FLAGS) s21_grep.c -o s21_grep

testing: tests tests_leaks

tests:
	@echo "Running flag tests..."
	-diff <(./s21_grep He $(FILE)) <(grep He $(FILE))
	-diff <(./s21_grep -e He $(FILE)) <(grep -e He $(FILE))
	-diff <(./s21_grep -i He $(FILE)) <(grep -i He $(FILE))
	-diff <(./s21_grep -v He $(FILE)) <(grep -v He $(FILE))
	-diff <(./s21_grep -c He $(FILE)) <(grep -c He $(FILE))
	-diff <(./s21_grep -l He $(FILE)) <(grep -l He $(FILE))
	-diff <(./s21_grep -n He $(FILE)) <(grep -n He $(FILE))
	-diff <(./s21_grep -h He $(FILE)) <(grep -h He $(FILE))
	-diff <(./s21_grep -s He $(FILE)) <(grep -s He $(FILE))
	-diff <(./s21_grep -f test_files/patterns.reg $(FILE)) <(grep -f test_files/patterns.reg $(FILE))
	-diff <(./s21_grep -s He $(FILE)) <(grep -s He $(FILE))
	-diff <(./s21_grep -iv He $(FILE)) <(grep -iv He $(FILE))
	-diff <(./s21_grep -in He $(FILE)) <(grep -in He $(FILE))
	-diff <(./s21_grep -io He $(FILE)) <(grep -io He $(FILE))
	-diff <(./s21_grep -ie He $(FILE)) <(grep -ie He $(FILE))
	-diff <(./s21_grep -ic He $(FILE)) <(grep -ic He $(FILE))
	-diff <(./s21_grep -il He $(FILE)) <(grep -il He $(FILE))
	-diff <(./s21_grep -ih He $(FILE)) <(grep -ih He $(FILE))
	-diff <(./s21_grep -is He $(FILE)) <(grep -is He $(FILE))
	-diff <(./s21_grep -ie He $(FILE)) <(grep -ie He $(FILE))
	-diff <(./s21_grep -ve He $(FILE)) <(grep -ve He $(FILE))
	-diff <(./s21_grep -vc He $(FILE)) <(grep -vc He $(FILE))
	-diff <(./s21_grep -vl He $(FILE)) <(grep -vl He $(FILE))
	-diff <(./s21_grep -vn He $(FILE)) <(grep -vn He $(FILE))
	-diff <(./s21_grep -vh He $(FILE)) <(grep -vh He $(FILE))
	-diff <(./s21_grep -vs He $(FILE)) <(grep -vs He $(FILE))
	-diff <(./s21_grep -vo He $(FILE)) <(grep -vo He $(FILE))
	-diff <(./s21_grep -cl He $(FILE)) <(grep -cl He $(FILE))
	-diff <(./s21_grep -cn He $(FILE)) <(grep -cn He $(FILE))
	-diff <(./s21_grep -ch He $(FILE)) <(grep -ch He $(FILE))
	-diff <(./s21_grep -cs He $(FILE)) <(grep -cs He $(FILE))
	-diff <(./s21_grep -co He $(FILE)) <(grep -co He $(FILE))
	-diff <(./s21_grep -ln He $(FILE)) <(grep -ln He $(FILE))
	-diff <(./s21_grep -lh He $(FILE)) <(grep -lh He $(FILE))
	-diff <(./s21_grep -ls He $(FILE)) <(grep -ls He $(FILE))
	-diff <(./s21_grep -lo He $(FILE)) <(grep -lo He $(FILE))
	-diff <(./s21_grep -le He $(FILE)) <(grep -le He $(FILE))
	-diff <(./s21_grep -ne He $(FILE)) <(grep -ne He $(FILE))
	-diff <(./s21_grep -nh He $(FILE)) <(grep -nh He $(FILE))
	-diff <(./s21_grep -ns He $(FILE)) <(grep -ns He $(FILE))
	-diff <(./s21_grep -no He $(FILE)) <(grep -no He $(FILE))
	-diff <(./s21_grep -he He $(FILE)) <(grep -he He $(FILE))
	-diff <(./s21_grep -ho He $(FILE)) <(grep -ho He $(FILE))
	-diff <(./s21_grep -se He $(FILE)) <(grep -se He $(FILE))
	-diff <(./s21_grep -so He $(FILE)) <(grep -so He $(FILE))

tests_leaks:
	@echo "Running Valgrind tests..."
	$(CHECK) ./s21_grep he $(FILE) | grep ERROR || exit 0
	$(CHECK) ./s21_grep he no.txt | grep ERROR || exit 0
	$(CHECK) ./s21_grep -o he $(FILE) | grep ERROR || exit 0
	$(CHECK) ./s21_grep -h he $(FILE) | grep ERROR || exit 0
	$(CHECK) ./s21_grep -e He -e he $(FILE) | grep ERROR || exit 0
	$(CHECK) ./s21_grep -f patterns.reg $(FILE) | grep ERROR || exit 0

clean:
	rm -f s21_grep