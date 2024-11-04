# Main function for multiplaing:
cpdef list mul(matrix_one: list, matrix_two: list):
    cdef int rowsA = len(matrix_one)
    cdef int colsA = len(matrix_one[0])
    cdef int rowsB = len(matrix_two)
    cdef int colsB = len(matrix_two[0])


    if colsA != rowsB:
        print("ERROR! INCORRECT SIZES.")

        return -1

    cdef list result = [[0 for row in range(colsB)] for col in range(rowsA)]

    for i in range(rowsA):
        for j in range(colsB):
            for k in range(colsA):
                result[i][j] += matrix_one[i][k] * matrix_two[k][j]

    return result
