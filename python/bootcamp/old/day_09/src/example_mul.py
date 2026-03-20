# Necessary functions:
from itertools import tee


# The main mult function:
def mul(a, b):
    b_iter = tee(zip(*b), len(a))

    return [
        [
            sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b))

            for col_b in b_iter[i]
        ] for i, row_a in enumerate(a)
    ]
