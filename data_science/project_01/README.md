# `data_science/project_01`

[![CI](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml)
[![codecov](https://codecov.io/gh/erdogan-deniz/school-21/branch/main/graph/badge.svg?flag=data_science-project_01)](https://codecov.io/gh/erdogan-deniz/school-21?flags%5B0%5D=data_science-project_01)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](../../LICENSE)

> *"Tweets" — NLP project: sentiment-analysis classifier on labelled tweets via bag-of-words / TF-IDF / word2vec, with stemming, lemmatisation, cosine-similarity top-10 and ≥ 0.832 accuracy target.*

## Quick start

```bash
cd data_science/project_01

# Cross-platform Makefile creates .venv and installs pinned deps
# (numpy / scipy / pandas / scikit-learn / nltk / spacy / gensim /
#  symspellpy / ipykernel — all semver-bounded).
make install

# spaCy's English model is needed for tokenize_text / lemmatize_text.
# Fetch the large variant the project trains on (~700 MB).
.venv/bin/python -m spacy download en_core_web_lg

# Open the notebooks.
.venv/bin/jupyter notebook notebooks/preprocessing.ipynb
.venv/bin/jupyter notebook notebooks/analysis.ipynb

# Run the pytest suite (25 tests over the lightweight API surface).
.venv/bin/pytest -v src/tests/

# Drop the venv when done.
make clear
```

## Demo

> **TODO** — short asciinema cast / sample run with similarity-output preview is planned in the python/ Phase 2 demo slice.

## Documentation

- Sphinx API reference: [erdogan-deniz.github.io/school-21/sphinx/data_science/project_01/](https://erdogan-deniz.github.io/school-21/sphinx/data_science/project_01/)
  (autodoc over `src/models/` + `src/utilities/`; rebuilt by [`pages.yml`](../../.github/workflows/pages.yml) on every push).
- [Workflow](#workflow) section below.
- Notebooks: `notebooks/preprocessing.ipynb`, `notebooks/analysis.ipynb`.
- Source modules under `src/models/` (TextPreprocessor, TextToFeaturesConverter)
  and `src/utilities/` (handle_errors decorator, top_similar_vectors).

## Tests

- **25 pytest unit tests** under `src/tests/` covering the lightweight
  API surface — `TextPreprocessor.clean_text` (10, incl. the apostrophe-
  preservation contract that lets the downstream spaCy tokenizer split
  contractions correctly), `TextPreprocessor.stem_text` (4, PorterStemmer-
  backed), `TextToFeaturesConverter` one-hot / word-count / TF-IDF
  encoders + `initialize_tools` (8), `top_similar_vectors` (3).
- Heavy methods (spaCy / SymSpell / gensim Word2Vec model loads)
  deliberately uncovered — they belong to a slow-test suite, not the
  per-PR gate.
- Notebook-level acceptance: ≥ 0.832 accuracy on the test dataset
  (baseline), ≥ 0.873 (bonus).
- CI: pytest matrix entry `data_science-project_01` in
  [`.github/workflows/python.yml`](../../.github/workflows/python.yml);
  per-flag Codecov badge above.

## License & attribution

This project was developed as part of the **School 21** curriculum (analogue of
School 42). The repository as a whole is licensed under the **MIT License** —
see the root [`LICENSE`](../../LICENSE).

The `LICENSE` file inside this subproject is preserved as educational
attribution and historical artefact; it does not override the repo-wide MIT
licence.

---

## Original task (School 21)

Summary: project is an introduction to *Natural Language Processing*: *bag of
words*, *TFIDF*, *Stemming*, *Lemmatization*, stop-words, *Cosine Similarity*,
n-grams, *word2vec*.

## Foreword

We use language to transmit thoughts.
Did you know that it not only reflects reality, shapes it?
If it has no word, it does not exist for people.
The Amondawa language has no words for: time, month, year.
People do not refer to age, but take different names at stages of lives
[source](https://www.bbc.com/news/science-environment-13452711).
The language can change the way we see colors.
The Himba of northern *Namibia* call the sky black and the water white, for them
blue and green the same word.
They have five words for color
<https://www.bbc.co.uk/blogs/tv/entries/24bbc4b8-58f9-373d-a896-274ae453ef2a>.
Aboriginal community in *Australia* — the Kuuk Thaayorre people.
They don't use words "left" and "right", everything is in cardinal directions:
north, south, east, west.
Say "hello" in Kuuk Thaayorre is to say: "Which way are you going?"
<https://www.ted.com/talks/lera_boroditsky_how_language_shapes_the_way_we_think/transcript?language=en>.

## Introduction

**NLP** (Natural Language Processing) - it is: a field of knowledge, a
techniques, an algorithms that process textual data and extract information.
Text is a semi-structured data.
Solving a *Classification* task with texts: predict a class.
Words are features, is technique *the bag of words*.
Create a matrix: the rows are document ID's, the columns are words.
Put `1` if the word is in the document, `0` if it is not.
Count the words in the documents and use the numbers as values.
Use *TFIDF* (term frequency inverse document frequency).
It gives higher weights to the words that are specific and lower to the words
that are regular.
**Stemming** - it is tecgnique that removes: suffixes, prefixes, endings.
Word "cats" becomes "cat".
**Lemmatization** - it is tecgnique that transforms a word into its base form.
"Better" becomes "good".
Another problem is that texts are full of misspellings.
Use *Levenshtein distance* to find the words with the minimum number of
corrections to transform word into correct one.
Try to catch "do" and "do not" — they are different things in texts.
The main idea is transform texts into vector formats to find features for task.

## Datasets

Work with the datasets of tweets.
The tweets labeled as: `positive`, `negative`, `neutral`.

## Workflow

General:

- Use the *NLTK* or other library.
- You can enrich the dataset with other datasets.

Similarity:

- Use the datasets and *cosine similarity* to find the top `10` pairs of tweets.

Preprocessing:

- Try approaches:

  ![processing approaches](./content/images/tables/processing_options.png)

- Split on the train and test datasets with stratification `20` %.

*Machine Learning*:

- Try algorithms and datasets to solve the classification task — *sentiment*
  *analysis*.

## Bonus functionality

- Use `word2vec` to get vectorization of text.
- Get *accuracy* on the test dataset bigger then `0.873`.

## Submission

- Achieve an *accuracy* `0.832` on the test dataset.
- The top `10` similar tweets for each of a preprocessing.
