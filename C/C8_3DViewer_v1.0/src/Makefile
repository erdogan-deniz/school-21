CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c11
CHECKFLAGS = -lcheck -lsubunit -coverage -pthread -lrt
APP = build/s21_3dviewer.app


all: install test

clean:
	rm -rf *.o *.a *.css *.out *.html *.gcno *.gcda *.gcov tests  3d_viewer docs

build:
	mkdir build
	cd ./build/ && qmake ../qt_viewer && make && mv opengl s21_3dviewer.app

install: build
	@mkdir $(HOME)/Desktop/3d_viewer_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/3d_viewer_v1.0/
	make clean

uninstall:
	@rm -rf build
	@rm -rf $(HOME)/Desktop/3d_viewer_v1.0/


dist:
	rm -rf Archive_3d_viewer_v1.0/
	mkdir Archive_3d_viewer_v1.0/
	mkdir Archive_3d_viewer_v1.0/src
	cp -R Makefile qt_viewer *.c *.h Archive_3d_viewer_v1.0/src/
	tar cvzf Archive_3d_viewer_v1.0.tgz Archive_3d_viewer_v1.0/
	mv Archive_3d_viewer_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_3d_viewer_v1.0/

dvi:
	open dvi.html

test: clean
	$(CC) $(GCC) $(FLAGS) 3d_viewer.c 3d_viewer_test.c 3d_viewer.h -o 3d_viewer_test.o $(UBUNTU_FLAG)
	# 3d_viewer.h 
	./3d_viewer_test.o


gcov_report: test
	$(CC) $(FLAGS) -c -fprofile-arcs -ftest-coverage *.c
	$(CC) $(FLAGS) -fprofile-arcs *.o -o tests -lcheck -lsubunit -lm -pthread
	./tests
	# rm -rf *.gcda *.gcno
	gcovr -r . --html --html-details -o coverage_report.html
	# rm *.o
	
clang:
	clang-format -n *.c *.h

valgrind: 
	valgrind  --track-origins=yes --leak-check=full --show-leak-kinds=all -v ./3d_viewer_test.o
