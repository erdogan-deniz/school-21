CXX = g++
CXXFLAGS = -g -std=c++17
CALCULATOR_TESTS_SRCS = UnitTests/calculator_tests.cc
CALCULATOR_HEADERS = Controller/calculatorcontroller.h
CALCULATOR_SRC = Model/calculatormodel.cc
APP_ARCHIVE = Archive_SmartCalc_v2.0
OS := $(shell uname)

ifeq ($(OS),Linux)
TEST_FLAGS = -lgtest -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
TEST_FLAGS = -lgtest -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: install

install: uninstall
	mkdir build
	@cd build && qmake -r ../View/View.pro && make
	@rm build/*.cpp
	@rm build/*.o
	@rm build/*.h
	@rm build/*Makefile
	@mv View.app build/View.app

uninstall:
	@rm -rf build

dist:
	@rm -rf $(APP_ARCHIVE)/
	@mkdir $(APP_ARCHIVE)
	@mkdir $(APP_ARCHIVE)/src/
	@cp -r build/View.app $(APP_ARCHIVE)/src/View.app
	@tar -cvzf $(APP_ARCHIVE).tgz $(APP_ARCHIVE)/
	@rm -rf $(APP_ARCHIVE)

tests: $(CALCULATOR_TESTS_SRCS) $(CALCULATOR_HEADERS) $(CALCULATOR_SRC)
	@$(CXX) $(CXXFLAGS) $^ $(TEST_FLAGS) -o ./unit_tests
	@./unit_tests

leaks: tests
	CK_FORK=no leaks --atExit -- ./unit_tests

dvi:
	@open Description/dvi.html

clean:
	@rm -rf build
	@rm -rf $(APP_ARCHIVE).tgz
	@rm ./unit_tests
	@rm -rf unit_tests.dSYM
	@rm *.gcno
	@rm *.gcda

check:
	@clang-format -style=Google -n Controller/*.h Model/*.h Model/*.cc View/*.h View/*.cc