# Necessary modules:
import sys
import os.path

# Add our files:
sys.path.append(os.path.abspath(os.pardir))

import support


# The test functions:
def test_correct():
    assert support.greetings() is None
