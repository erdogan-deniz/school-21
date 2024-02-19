# Necessary modules:
import time
import multiply
import example_mul


# Data for tests:
A_matrix = [
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
           ]

B_matrix = [
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [9, 8, 7, 6, 5, 4, 3, 2, 1],
           ]


# Function for my tests:
def make_my_test(matrix_one: list, matrix_two: list):
    if (not isinstance(matrix_one, list)) or (not isinstance(matrix_two, list)):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    start = time.time()

    for i in range(1000000):
        multiply.mul(matrix_one, matrix_two)

    end = time.time()
    process_time = end - start

    print(f"My test time = {process_time}")

    return process_time


# Function for example tests:
def make_example_test(matrix_one: list, matrix_two: list):
    if (not isinstance(matrix_one, list)) or (not isinstance(matrix_two, list)):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    start = time.time()

    for i in range(1000000):
        example_mul.mul(matrix_one, matrix_two)

    end = time.time()
    process_time = end - start

    print(f"Python time = {process_time}")

    return process_time


# Check which code is faster:
def make_comparison(first_matrix: list, second_matrix: list):
    if (not isinstance(first_matrix, list)) or (not isinstance(second_matrix, list)):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    print(f"Speedup = {make_example_test(first_matrix, second_matrix) / make_my_test(first_matrix, second_matrix)}")


# Launch test:
if __name__ == "__main__":
    make_comparison(A_matrix, B_matrix)
