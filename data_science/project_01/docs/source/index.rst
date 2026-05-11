data_science/project_01 — "Tweets" NLP
========================================

Sentiment-analysis classifier on a labelled tweet corpus. The
notebooks (``notebooks/preprocessing.ipynb`` and
``notebooks/analysis.ipynb``) walk through the pipeline end-to-end;
this API reference covers the reusable helpers extracted into
``src/``.

Pipeline overview
-----------------

1. **Preprocess** raw text: ``TextPreprocessor.clean_text`` strips
   punctuation/digits (keeping apostrophes for downstream contraction
   handling), then ``correct_text`` runs SymSpell, ``tokenize_text``
   uses spaCy, and ``lemmatize_text`` / ``stem_text`` give two
   normalisation flavours.
2. **Featurise**: ``TextToFeaturesConverter`` produces one-hot,
   bag-of-words, TF-IDF, and Word2Vec embeddings of the cleaned
   corpus.
3. **Compare**: ``top_similar_vectors`` finds the ``n`` highest-
   cosine pairs across the feature matrix — useful for sanity-
   checking that semantically-close tweets cluster.

.. toctree::
   :maxdepth: 2
   :caption: Contents

   modules

Indices
=======

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
