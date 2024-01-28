import sys
import os.path

# Add our files:
sys.path.append(os.path.abspath(os.pardir))

import support


# Test data:
questions = {
    "first": " So... let's start with a simple one. How are you feeling?",
    "second": " Good. Tell me, are you worried or nervous right now?",
    "third": " Imagine the following. You are in the desert, there is a turtle lying on its back in front of you," +
             " You are not helping it. Why?",
    "fourth": " OK. You were given a gold watch, what will you do with it?",
    "fifth": " Do you think animals experience pain when they die?",
    "sixth": " Hm. Do you agree that everyone gets what they deserve?",
    "seventh": " Who is your best friend?",
    "eighth": " Let's say. Now try to remember what was your favorite toy as a child?",
    "ninth": " Have you ever eaten a dog or live mussels?",
    "tenth": " The last question. Are you afraid of death?"
}

answers = {
    "first": [
        "  Not bad.",
        "  Delightfully!",
        "  Let's not ask stupid questions..."
    ],
    "second": [
        "  No.",
        "  Why would I...",
        "  Aha, of course.... no."
    ],
    "third": [
        "  I don't know.",
        "  How did I end up in the desert?",
        "  How am I not helping?"
    ],
    "fourth": [
        "  I will refuse the gift.",
        "  Mmm... I will not accept the gift and ask you not to give anything.",
        "  I will accept the gift, how can I refuse it, it's rude!"
    ],
    "fifth": [
        "  I don't know.",
        "  It's a strange question, but I think so.",
        "  How can you ask such a thing!"
    ],
    "sixth": [
        "  Yes.",
        "  I'm not sure...",
        "  The hell with it! Life is unfair."
    ],
    "seventh": [
        "  I don't have a best friend.",
        "  Yes, it is... Bilbo Baggins.",
        "  Aah... no! I don't have a best friend."
    ],
    "eighth": [
        "  LEGO.",
        "  I don't remember much, but it looks like a teddy bear.",
        "  Probably... probably... A typewriter, yes, a yellow typewriter!"
    ],
    "ninth": [
        "  I do not remember.",
        "  Probably, yes.",
        "  What? Oh, yes, of course..."
    ],
    "tenth": [
        "  Yes.",
        "  It's hard to say...",
        "  ...Kha, most likely."
    ]
}


# The test functions:
def test_input_arguments():
    assert support.read_json(12) == -1
    assert support.read_json([1, 2, 3]) == -1
    assert support.read_json(True) == -1
    assert support.read_json("") == -1
    assert support.read_json(2.4) == -1
    assert support.read_json("../answers") != -1


def test_files():
    assert support.read_json("../answers") == answers
    assert support.read_json("../questions") == questions
    assert support.read_json("wrong") == -1
    assert support.read_json("empty") == -1


def test_correct():
    assert support.read_json("../answers") == answers
    assert support.read_json("../questions") == questions
