"""
Functions Python module.
"""


from numpy import ndarray
from pandas import DataFrame
from sklearn.metrics.pairwise import cosine_similarity

from .decorators import handle_errors


@handle_errors
def top_similar_vectors(vecs: DataFrame, n: int = 10) -> list[list[int]] | None:
    """
    Find the top N similar vector pairs.

    :Parameters:
        vecs (DataFrame): A vectors.
        n (int): Number of top pairs to return.
                 Default: 10.

    :Returns:
        list[list[int]]: A list of index of a top pairs.
        None: An error occurs.

    :Exceptions:
        ValueError: The input data is empty.
    """

    try:
        vecs_idxs: list = []
        vecs_sim_mtrx: ndarray = cosine_similarity(vecs.values, )

        for idx in range(len(vecs, ), ):
            for jdx in range(idx + 1, len(vecs, ), ):
                vecs_idxs.append((
                    vecs.index[idx],
                    vecs.index[jdx],
                    vecs_sim_mtrx[idx, jdx],
                ), )

        vecs_idxs.sort(key=lambda cos_sim_val: cos_sim_val[2], reverse=True, )

        return [[idxs[0], idxs[1]] for idxs in vecs_idxs[: n]]
    except ValueError as val_err:
        print(
            f"\nError file: {__file__}" +
            f"\nError message: {val_err}",
        )
