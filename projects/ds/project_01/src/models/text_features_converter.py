"""
Text-to-features conversion Python module.

:Usage example:
    >>> converter: TextToFeaturesConverter = TextToFeaturesConverter()

    >>> converter.initialize_tools()

    >>> one_hot_df: DataFrame = converter.one_hot_texts_encoding(texts, )
    >>> count_df: DataFrame = converter.word_count_texts_encoding(texts, )
    >>> tfidf_df: DataFrame = converter.tfidf_texts_encoding(texts, )
    >>> token_vec: DataFrame = converter.vectorize_text_tokens(texts, )
    >>> vectorized_texts_df: DataFrame = converter.vectorize_texts(texts, )
"""


import os
import sys

sys.path.append(
    os.path.abspath(
        os.path.join(
            os.path.dirname(__file__, ),
            "..",
        ),
    ),
)

from gensim.models import Word2Vec
from pandas import Series, DataFrame
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from numpy import (
    ndarray,

    mean,
    zeros,
)

from utilities import handle_errors


class TextToFeaturesConverter:
    """
    A class for converting text data into features.

    :Attributes:
        vectorizer (Word2Vec): A model for generating word embeddings.
                               Default: None.
        tfidf_model (TfidfVectorizer): TF-IDF model for converting a text into
                                       features.
                                       Default: None.
        cnt_vectorizer (CountVectorizer): A model for generating bag-of-words
                                          features.
                                          Default: None.
        bin_cnt_vectorizer (CountVectorizer): A model for generating binary
                                              features.
                                              Default: None.
    """

    def __init__(self) -> None:
        """
        Initializes the text feature extraction class.
        """

        self.vectorizer: Word2Vec | None = None
        self.tfidf_model: TfidfVectorizer | None = None
        self.cnt_vectorizer: CountVectorizer | None = None
        self.bin_cnt_vectorizer: CountVectorizer | None = None

    @handle_errors
    def initialize_tools(
        self,
        vec_size: int = 250,
        window_size: int = 5
    ) -> None:
        """
        Initialize text features extraction tools.

        :Parameters:
            vec_size (int): Dimensionality of the vector.
                            Default: 250.
            window_size (int): Maximum distance between the current and
                               predicted word.
                               Default: 5.
        """

        self.tfidf_model = TfidfVectorizer()
        self.cnt_vectorizer = CountVectorizer()
        self.bin_cnt_vectorizer = CountVectorizer(binary=True, )
        self.vectorizer = Word2Vec(**{
            "sg": 1,
            "epochs": 100,
            "min_count": 1,
            "window": window_size,
            "vector_size": vec_size,
        }, )

    @handle_errors
    def one_hot_texts_encoding(self, texts: Series) -> DataFrame | None:
        """
        Convert text documents into a one-hot encoded DataFrame.

        :Parameters:
            texts (Series): A text documents to be encoded.

        :Returns:
            DataFrame: Each row a document and each column vector.
            None: An error occurs.

        :Exceptions:
            TypeError: The input text string is not a valid type.
        """

        try:
            encoded_texts: DataFrame = DataFrame(
                self.bin_cnt_vectorizer.fit_transform(texts, ).toarray(),
                columns=self.bin_cnt_vectorizer.get_feature_names_out(),
            )

            return encoded_texts
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )

    @handle_errors
    def word_count_texts_encoding(self, texts: Series) -> DataFrame | None:
        """
        Convert texts into a word-count encoded DataFrame.

        :Parameters:
            texts (Series): Texts to be encoded.

        :Returns:
            DataFrame: Each row a vector, each column is a dimension.
            None: An error occurs.
        """

        encoded_texts: DataFrame = DataFrame(
            self.cnt_vectorizer.fit_transform(texts, ).toarray(),
            columns=self.cnt_vectorizer.get_feature_names_out(),
        )

        return encoded_texts

    @handle_errors
    def tfidf_texts_encoding(self, texts: Series) -> DataFrame | None:
        """
        Convert texts into a TF-IDF encoded DataFrame.

        :Parameters:
            texts (Series): Texts to be encoded.

        :Returns:
            DataFrame: Each row a vector, each column is a TF-IDF feature.
            None: An error occurs.
        """

        encoded_texts: DataFrame = DataFrame(
            self.tfidf_model.fit_transform(texts, ).toarray(),
            columns=self.tfidf_model.get_feature_names_out(),
        )

        return encoded_texts

    @handle_errors
    def vectorize_text_tokens(self, text_tokens: list[str]) -> ndarray | None:
        """
        Convert a text tokens into a vector.

        :Parameters:
            text_tokens (list[str]): List of text tokens.

        :Returns:
            ndarray: Vector of the text.
            None: An error occurs.

        :Exceptions:
            TypeError: Input tokens are not a valid.
        """

        try:
            vec: ndarray = [
                self.vectorizer.wv[text_token] for
                text_token in
                text_tokens if
                text_token in self.vectorizer.wv
            ]

            if vec:
                return mean(vec, axis=0, )

            return zeros(self.vectorizer.vector_size, )
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )

    @handle_errors
    def vectorize_texts(self, texts: Series) -> DataFrame | None:
        """
        Convert a texts into vectors.

        :Parameters:
            texts (Series): Texts to be vectorized.

        :Returns:
            DataFrame: Each row a text, each column is a vector dimension.
            None: An error occurs.

        :Exceptions:
            TypeError: Input texts are not a valid.
        """

        try:
            word_corpus: list[list] = texts.str.split().tolist()
            self.vectorizer = Word2Vec(**{
                "epochs": 100,
                "sentences": word_corpus,
                "sg": self.vectorizer.sg,
                "window": self.vectorizer.window,
                "min_count": self.vectorizer.min_count,
                "vector_size": self.vectorizer.vector_size,
            }, )
            vecs: list[list[float]] = texts.apply(
                str.split,
            ).apply(
                lambda tokens: self.vectorize_text_tokens(tokens, ),
            )
            encoded_texts: DataFrame = DataFrame(
                vecs.tolist(),
                columns=[
                    f"dimension_{idx}" for
                    idx in
                    range(vecs[0].shape[0], )
                ],
            )

            return encoded_texts
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )
