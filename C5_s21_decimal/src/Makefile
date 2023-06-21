CC=gcc
FLAGS=-Wall -Wextra -Werror

OS = $(shell uname)

ifeq ($(OS), Linux)
	TEST_FLAGS=-lcheck -lgcov -lm -lsubunit
else
	TEST_FLAGS = -lcheck -lgcov
endif

SRC_DECIMAL=./s21_util/util.c ./s21_another/s21_another.c ./s21_another/s21_floor.c ./s21_another/s21_negate.c ./s21_another/s21_round.c \
./s21_arithmetic/s21_arithmetic.c ./s21_arithmetic/s21_mul.c ./s21_arithmetic/s21_add.c ./s21_arithmetic/s21_div.c ./s21_arithmetic/s21_mod.c ./s21_arithmetic/s21_sub.c \
./s21_comparison/s21_cmp.c ./s21_comparison/s21_is_equal.c ./s21_comparison/s21_is_greater_or_equal.c ./s21_comparison/s21_is_greater.c \
./s21_comparison/s21_is_less.c ./s21_comparison/s21_is_less_or_equal.c ./s21_comparison/s21_is_not_equal.c ./s21_another/s21_truncate.c \
 ./s21_convertors/s21_from_decimal_to_float.c ./s21_convertors/s21_from_decimal_to_int.c \
./s21_convertors/s21_from_int_to_decimal.c ./s21_convertors/s21_from_float_to_decimal.c

OBJ=$(SRC_DECIMAL:.c=.o)

.PHONY: all clean test gcov_report

all: test s21_decimal.a gcov_report

test:CFLAGS += -coverage
test: s21_test.o $(OBJ) s21_decimal.h
	$(CC) $(FLAGS) $(OBJ) s21_test.o $(TEST_FLAGS) -o test
	./test

s21_test.o: s21_test.c
	$(CC) -c $(FLAGS) s21_test.c

s21_decimal.a: s21_decimal.h $(OBJ)
	ar rcs s21_decimal.a $(OBJ)
	ranlib s21_decimal.a

gcov_report: test
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open report/index.html

cpplint:
	python3 ../materials/linters/cpplint.py s21_util/*.c s21_convertors/*.c s21_comparison/*.c s21_arithmetic/*.c s21_another/*.c *.h *.c

clean: 
	rm -rf s21_test report test *.o $(OBJ) ./s21_util/*.gcno ./s21_util/*.gcda ./s21_another/*.gcno ./s21_another/*.gcda ./s21_arithmetic/*.gcno \
	./s21_arithmetic/*.gcda ./s21_comparison/*.gcno ./s21_comparison/*.gcda ./s21_convertors/*.gcno ./s21_convertors/*.gcda *.info s21_decimal.a