# Necessary modules:
import os.path
import sys

import support

# Add our files:
sys.path.append(os.path.abspath(os.pardir))


# The test functions:
def test_correct():
    assert support.greetings() is None
