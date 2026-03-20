"""
Text preprocessing Python module.

:Usage example:
    >>> text_preprocessor: TextPreprocessor = TextPreprocessor()

    >>> text_preprocessor.initialize_tools(
    ...     lang_dict_file="word_frequency_en.txt",
    ...     lang_dict_file_path="data/txt/",
    ... )

    >>> clean_text: str = text_preprocessor.clean_text(
    ...     "This is, an example! 123",
    ... )
    >>> corr_text: str = text_preprocessor.correct_text(clean_text, )
    >>> tokenized_text: str = text_preprocessor.tokenize_text(clean_text, )
    >>> lemmatized_text: str = text_preprocessor.lemmatize_text(clean_text, )
    >>> stemmed_text: str = text_preprocessor.stem_text(clean_text, )
"""


import os
import sys
import string

sys.path.append(
    os.path.abspath(
        os.path.join(
            os.path.dirname(__file__, ),
            "..",
        ),
    ),
)

from spacy import load
from symspellpy import SymSpell
from spacy.lang.en import English
from nltk.stem import PorterStemmer

from utilities import handle_errors


class TextPreprocessor:
    """
    A class for preprocessing text data.

    :Attributes:
        nlp (English | None): NLP model for tokenization and lemmatization.
                              Default: None.
        sym_spell (SymSpell | None): Text correction model.
                                     Default: None.
        stemmer (PorterStemmer | None): Model for stemming text.
                                        Default: None.
    """

    def __init__(self) -> None:
        """
        Initializes the text processing class.
        """

        self.nlp: English | None = None
        self.sym_spell: SymSpell | None = None
        self.stemmer: PorterStemmer | None = None

    @staticmethod
    @handle_errors
    def clean_text(text: str) -> str | None:
        """
        Clean a text string.

        :Parameters:
            text (str): Text string to be cleaned.

        :Returns:
            str: Cleaned text string: no digits, no punctuation.
            None: An error occurs.

        :Exceptions:
            TypeError: The text is not a string.
        """

        try:
            symbs_to_del: str = string.punctuation.replace("'", "", )
            translator: dict[int, int] = str.maketrans(
                '',
                '',
                symbs_to_del + string.digits,
            )
            clean_text: str = text.lower().translate(translator, )

            return " ".join(clean_text.split(), )
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )

    @handle_errors
    def initialize_tools(
        self,
        lang_dict_file: str,
        lang_dict_file_path: str,
        pref_len: int = 6,
        max_edit_dist: int = 3,
        nlp_model_name: str = "en_core_web_lg"
    ) -> None:
        """
        Initialize text processing tools.

        :Parameters:
            lang_dict_file (str): Name of the dictionary file.
            lang_dict_file_path (str): Path to the dictionary file.
            pref_len (int): Length of word prefixes for dictionary lookup.
                            Default: 6.
            max_edit_dist (int): Maximum edit distance for spell correction.
                                 Default: 3.
            nlp_model_name (str): Name of the NLP model.
                                  Default: "en_core_web_lg".

        :Exceptions:
            FileNotFoundError: The dictionary file was not found.
            OSError: The model can not be loaded.
            ValueError: Receives invalid parameters.
        """

        try:
            self.stemmer = PorterStemmer()
            self.nlp = load(nlp_model_name, )
            self.sym_spell = SymSpell(max_edit_dist, pref_len, )

            self.sym_spell.load_dictionary(
                lang_dict_file_path + lang_dict_file,
                term_index=0,
                count_index=1,
            )
        except FileNotFoundError as file_not_found_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {file_not_found_err}",
            )
        except OSError as os_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {os_err}",
            )
        except ValueError as val_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {val_err}",
            )

    @handle_errors
    def correct_text(self, text: str) -> str | None:
        """
        Correct misspellings in the text string.

        :Parameters:
            text (str): Text string.

        :Returns:
            str: Corrected text string.
            None: An error occurs.

        :Exceptions:
            TypeError: The input text string is not a valid type.
        """

        try:
            suggs: list = self.sym_spell.lookup_compound(
                text,
                max_edit_distance=2,
            )

            return suggs[0].term if suggs else text
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )

    @handle_errors
    def tokenize_text(self, text: str) -> str | None:
        """
        Tokenize a text string.

        :Parameters:
            text (str): An input text string.

        :Returns:
            str: A string of tokens.
            None: An error occurs.

        :Exceptions:
            OSError: An issue with the model.
        """

        try:
            text_tokens: list[str] = self.nlp(text.lower(), )
            text_tokens = [
                text_token.text
                for text_token in text_tokens
                if not (
                    text_token.is_punct or
                    text_token.is_space or
                    text_token.like_num
                )
            ]

            return " ".join(text_tokens, )
        except OSError as os_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {os_err}",
            )

    @handle_errors
    def lemmatize_text(self, text: str) -> str | None:
        """
        Lemmatize a text string.

        :Parameters:
            text (str): Input text string.

        :Returns:
            str: A lemmatized text string.
            None: An error occurs.

        :Exceptions:
            OSError: An issue with the model.
        """

        try:
            text_lemms: list[str] = self.nlp(text.lower(), )

            return " ".join([
                lemm_token.lemma_ for
                lemm_token in
                text_lemms if not
                lemm_token.is_punct and not
                lemm_token.is_space
            ], )
        except OSError as os_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {os_err}",
            )

    @handle_errors
    def stem_text(self, text: str) -> str | None:
        """
        Stem a text string.

        :Parameters:
            text (str): Input text string to be stemmed.

        :Returns:
            str: A stemmed text string.
            None: An error occurs.

        :Exceptions:
            TypeError: The input text is not a string.
        """

        try:
            text_stems: list[str] = [
                self.stemmer.stem(token, ) for
                token in
                text.split()
            ]

            return " ".join(text_stems, )
        except TypeError as type_err:
            print(
                f"\nError file: {__file__}" +
                f"\nError message: {type_err}",
            )
