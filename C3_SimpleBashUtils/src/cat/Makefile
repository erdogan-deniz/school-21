all: s21_cat

s21_cat: s21_cat.o
	gcc s21_cat.o -o s21_cat

s21_cat.o:
	gcc -c s21_cat.c -Wall -Wextra -Werror

s21_cat_test: s21_cat
	chmod 777 test_cat_main.sh test_cat_memory.sh
	sh *.sh
	./test_cat_main.sh
	sleep 5
	./test_cat_memory.sh
	sleep 5

rebuild: clean all

clean:
	rm -rf *.o s21_cat
