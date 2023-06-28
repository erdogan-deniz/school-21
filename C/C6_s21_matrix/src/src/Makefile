GCOV_FLAGS ?= -fprofile-arcs -ftest-coverage
TARGET = s21_matrix.a
SRC = $(wildcard s21_*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
TEST_SRC = $(wildcard ./tests/s21_*.c)
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	CC = gcc -Wall -Werror -Wextra -std=c11 -lsubunit -lrt -lpthread -lm
	OPEN_CMD = xdg-open
else ifeq ($(OS), Darwin)
	CC = gcc -Wall -Werror -Wextra -std=c11
	OPEN_CMD = open
endif

all: clean $(TARGET) test

$(TARGET): $(SRC)
	$(CC) -c $() $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

test: $(TARGET)
	$(CC) $(TEST_SRC) $< -o lib_test -lcheck
	./lib_test

gcov_report: clean_test
	$(CC) $(GCOV_FLAGS) $(TEST_SRC) $(SRC) -o test -lcheck
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

leaks: $(TARGET)
	$(CC) -g $(TEST_SRC) $< -o test -lcheck
	leaks -atExit -- ./test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.c *.h */*.c */*.h
	clang-format -style=Google -n *.c *.h */*.c */*.h

lcov:
ifeq ($(OS),Linux)
	sudo apt install lcov
endif
ifeq ($(OS),Darwin)
	brew install lcov
endif

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf test.dSYM

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf lib_test

.PHONY: all clean check lcov