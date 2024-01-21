CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
OS := $(shell uname)
TESTFILE = tests/unit_tests.cc model/objectmod.cc model/transform.cc

ifeq ($(OS),Linux)
FLAGS = -lgtest -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
PROG = 3DViewer
FYLE = view/$(PROG)
PROGOPEN = ./build/$(PROG)


else
FLAGS = -lgtest -lm -lpthread -fprofile-arcs -ftest-coverage
PROG = 3DViewer.app
FYLE = view/$(PROG)
PROGOPEN = ./build/$(PROG)/Contents/MacOS/3DViewer
endif

all: install open

install: uninstall
	make clean
	mkdir build
	cd view && qmake && make -j6 && make clean && rm Makefile && cd ../ && mv $(FYLE) build

uninstall:
	rm -rf build/

clean:
	@rm -rf *.o *.a unit_test
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf ./view/.qmake.stash


dvi: 
	@open description/dvi.html


dist:
	rm -rf Archive_3DViewer_v2.0/
	mkdir Archive_3DViewer_v2.0/
	mkdir Archive_3DViewer_v2.0/src
	cp -r ./build/$(PROG) Archive_3DViewer_v2.0/src/
	tar cvzf Archive_3DViewer_v1.0.tgz Archive_3DViewer_v2.0/
	rm -rf Archive_3DViewer_v2.0/


tests: clean
	$(CC) $(CFLAGS) $(TESTFILE) $(FLAGS) -o unit_test
	./unit_test


leak:
	leaks --atExit -- ./build/$(PROG)/Contents/MacOS/3DViewer

open:
	$(PROGOPEN)

clang:
	@cp ../materials/linters/.clang-format ./
	find . \( -name '*.h' -o -name '*.cc' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n
	@rm -rf .clang-format

