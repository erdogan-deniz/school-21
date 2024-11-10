.PHONY : all clean test clang valgrind gcov_report rebuild

CC=gcc
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
TEST_FLAGS:=$(CFLAGS) -g #-fsanitize=address -O1 -fno-omit-frame-pointer
LINUX_FLAGS =-lrt -lpthread -lm
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
LIBS=-lgtest
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
HEADER=s21_containers.h
TEST_SRC=tests.cc

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: test gcov_report

rebuild:
	make clean
	make all

test: 
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o test
else
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(CPPFLAGS) -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o gcov_report 
else
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
endif
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n tests.cc s21_containers.h \
	s21_containers/list/* s21_containers/queue/* \
	s21_containers/stack/* s21_containers/array/* \
	s21_containers/map/* s21_containers/set/* \
	s21_containers/multiset/* s21_containers/vector/*
	rm .clang-format

leaks: test
	leaks -atExit -- ./test

valgrind: clean 
	${CC} $(TEST_FLAGS) ${TEST_SRC}  $(CPPFLAGS) -o valgrind_test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test
	$(OPEN_CMD) ./RESULT_VALGRIND.txt

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
	rm -rf gcov_report
	rm -rf valgrind_test
	rm -rf *.dSYM

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf test
	rm -rf RESULT_VALGRIND.txt
