CC=gcc -std=c11
CFLAGS=-Wall -Werror -Wextra
GCOVFLAGS=-fprofile-arcs -ftest-coverage
SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)
TESTSFLAGS_MAC=-lcheck -lm -fsanitize=address -g
TESTSFLAGS_LINUX=-lcheck -lm -lpthread -lrt -lsubunit -fsanitize=address -g

all: clean s21_matrix.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_matrix.a: $(OBJS)
	ar rc s21_matrix.a $^
	ranlib s21_matrix.a
	rm -rf *.o

test: s21_matrix.a 
	$(CC) $(CFLAGS) test.c -L. s21_matrix.a $(TESTSFLAGS_MAC) -o test
	./test

test_linux: s21_matrix.a 
	$(CC) $(CFLAGS) test.c -L. s21_matrix.a $(TESTSFLAGS_LINUX) -o test
	./test

add_coverage_flag:
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag test
	./test
	lcov -t "test" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov *.a
	open ./report/index-sort-f.html

gcov_report_linux: add_coverage_flag test_linux
	./test
	lcov -t "test" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov *.a
	open ./report/index-sort-f.html

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.out *.info report

rebuild: all

style:
	clang-format -i *.c *.h

leaks:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test