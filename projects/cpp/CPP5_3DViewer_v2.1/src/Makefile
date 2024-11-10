CC = g++
CFLAGS = -Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17
TEST_LIBS = -lgtest
ARCHIVE = archive-3dviewer
BUILD = build
INSTALL_DIR = ~/Desktop/
OS = $(shell uname)

ifeq (${OS}, Linux)
	TEST_LIBS += -lsubunit -lrt
endif

all: install dist tests check

install:
	mkdir -p ${BUILD}
	cd ${BUILD} && cmake ../3DViewer/CMakeLists.txt && ${MAKE} && rm -rf ${INSTALL_DIR}/3DViewer.app && mv -f 3DViewer.app ${INSTALL_DIR}
	rm -rf ${BUILD}

open:
	open ~/Desktop/3DViewer.app

uninstall:
	rm -rf ~/Desktop/3DViewer.app

clean:
	rm -rf ${ARCHIVE}*
	rm -rf 3DViewer/Unit-tests/report 3DViewer/Unit-tests/Tests

dvi:
	open dvi.md -a Visual\ Studio\ Code

dist:
	mkdir -p ${ARCHIVE}
	cp -R 3DViewer/ ${ARCHIVE}/
	tar -cf ${ARCHIVE}.tar ${ARCHIVE}
	gzip -9f ${ARCHIVE}.tar
	rm -rf ${ARCHIVE}

tests:
	cd 3DViewer/Unit-tests && mkdir -p build && cd build && \
	cmake .. && cmake --build . --target all && \
	mv Tests ../ && cd .. && rm -rf build && ./Tests

gcov_report: clean
	cd 3DViewer/Unit-tests && mkdir -p build && cd build && \
	cmake -DCMAKE_BUILD_TYPE=Coverage .. && cmake --build . --target all && \
	mv Tests ../ && cd .. && chmod +x Tests && ./Tests && \
	lcov -t "Tests" -o gcov_test.info --include */src/* -c -d . && \
	genhtml -o report/ gcov_test.info && \
	open ./report/index.html && \
	rm -rf ./*.gcno ./*.gcda ./gcov* build/

check:
	cp ../materials/linters/.clang-format .
	cd 3DViewer/ && clang-format -n Parsing/singleton.cc		\
									Parsing/singleton.h			\
									Controller/controller.cc 	\
									Controller/controller.h 	\
									GLWidget/scene.cc 			\
									GLWidget/scene.h 			\
									Viewer/viewer.cc 			\
									Viewer/viewer.h 			\
									Unit-tests/main.cc			\
									Unit-tests/tst_parsing.cc	\
									GIFCreation/gifImage/*.cpp  \
									GIFCreation/gifImage/*.h 	\
									GIFCreation/gifLib/*.c 		\
									GIFCreation/gifLib/*.h		\
									main.cc
	rm -f .clang-format