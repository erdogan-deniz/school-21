COMP = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_FLAGS=-lgtest -pthread

all: clean s21_matrix_oop.a test

clean:
	rm -rf s21_*o
	rm -rf *.a
	rm -rf a.out*
	rm -rf *.gch
	rm -rf gtest.*o
	rm -rf report
	rm -rf test*
	rm -rf *.gcda
	rm -rf *.dSYM

test: clean
	$(COMP) $(FLAGS) *.cc *.h additional/*.cc methods/*.cc operations/*.cc properties/*.cc -o test $(TEST_FLAGS)
	./test

s21_matrix_oop.a:
	$(COMP) $(FLAGS) -c *.cc *.h additional/*.cc methods/*.cc operations/*.cc properties/*.cc
	ar r s21_matrix_oop.a *.o
	rm *.o

leaks:
	leaks -atExit -- ./test

valgrind:
	valgrind --leak-check=full --leak-resolution=med ./test

clang_n:
	clang-format -n *.cc *.h additional/*.cc methods/*.cc operations/*.cc properties/*.cc

clang_i:
	clang-format -i *.cc *.h additional/*.cc methods/*.cc operations/*.cc properties/*.cc