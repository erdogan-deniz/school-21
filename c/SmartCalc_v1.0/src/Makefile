WWW = -Werror -Wextra -Wall -std=c11 -g
G = gcc
OS = $(shell uname)

ifeq ($(OS), Linux)
	FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	BD = ./view/view
	DEL = view
else
	FLAGS = -lcheck
	BD = open view/view.app
	DEL = view.app
endif

.PHONY: all gui install uninstall

all: uninstall clean install

# Build the Qt GUI only (view.pro: TARGET = view); CI uses this target.
gui:
	cd view && qmake view.pro && $(MAKE)

# Build the GUI and start it.
install: gui
	$(BD)

uninstall:
	rm -rf view/$(DEL)
	rm -rf view/.qmake.stash
	rm -rf view/Makefile

test:
	$(G) $(WWW)  tests/*.c s21_calculator.c validation/*.c stack/*.c \
	parser/*.c additional/*.c list/*.c transform/*.c calculate/*.c  $(FLAGS) -o test
	./test

clean:
	rm -rf *.o *.a *.gch *.gcno *.gcna *.gcda *.info *.dSYM test test_html

dvi: 
	open index.html

dist: # doesn't work
	tar -cf SmartCalc_v1.0.tar *.h build Calc Smart_Calc index.html

gcov_report: test
	lcov -t "test_html" -o unit_test.info -c -d .
	genhtml -o test_html unit_test.info
	open test_html/index.html

leaks:
	leaks -atExit -- ./test

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test

style_i:
	clang-format -style=google -i *.c *.h additional/*.c additional/*.h bonus/*.c bonus/*.h calculate/*.c calculate/*h \
	list/*.c list/*.h parser/*.c parser/*.h stack/*.c stack/*.h tests/*.c tests/*.h transform/*.c transform/*.h \
	validation/*.c validation/*.h *.c *.h 

style_n:
	clang-format -style=google -n *.c *.h additional/*.c additional/*.h bonus/*.c bonus/*.h calculate/*.c calculate/*h \
	list/*.c list/*.h parser/*.c parser/*.h stack/*.c stack/*.h tests/*.c tests/*.h transform/*.c transform/*.h \
	validation/*.c validation/*.h *.c *.h 