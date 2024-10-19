all: s21_grep

s21_grep: s21_grep.o
	gcc s21_grep.o -o s21_grep

s21_grep.o:
	gcc -Wall -Werror -Wextra -c s21_grep.c

s21_grep_test: s21_grep
	chmod 777 test_grep.sh test_grep_main.sh test_grep_memory.sh
	sh *.sh
	./test_grep.sh
	sleep 5
	./test_grep_main.sh
	sleep 5
	./test_grep_memory.sh

clean:
	rm -rf *.o s21_grep

utils:
	sudo apt install gcc
	sudo apt install make
	sudo apt install clang-format

rebuild: clean all

