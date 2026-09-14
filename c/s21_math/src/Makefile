WWW = -Werror -Wextra -Wall -std=c11
G = gcc
# Check's link line differs per platform (Linux additionally needs
# -lsubunit -lrt -lpthread); ask pkg-config and fall back to the bare
# -lcheck for setups without pkg-config (e.g. Homebrew on macOS).
CHECK_LIBS = $(shell pkg-config --libs check 2>/dev/null || echo -lcheck)

all : clean s21_math.a test gcov_report

clean: 
	rm -rf *.o *.a *.gch *.gcno *.gcna *.gcda *.info test test_html

test: clean
	$(G) $(WWW) s21_*.c unit_test.c $(CHECK_LIBS) -lm -o test

s21_math.a:
	$(G) $(WWW) -c s21_*.c
	ar r s21_math.a *.o
	rm *.o

gcov_report:
	$(G) $(WWW) -fprofile-arcs -ftest-coverage unit_test.c s21_*.c $(CHECK_LIBS) -lm -o test
	./test
	lcov -t "test_html" -o unit_test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o test_html unit_test.info
	@[ -n "$$CI" ] || open test_html/index.html || true

leaks:
	leaks -atExit -- ./test