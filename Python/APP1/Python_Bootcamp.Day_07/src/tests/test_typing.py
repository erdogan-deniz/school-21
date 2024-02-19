import sys
import os.path
import support

# Add our files:
sys.path.append(os.path.abspath(os.pardir))


# The test functions:
def test_input_arguments():
    assert support.typing(2) == -1
    assert support.typing(True) == -1
    assert support.typing(['d', 's', 3]) == -1
    assert support.typing("Hello") != -1


def test_correct():
    assert support.typing("Hello") is None
    assert support.typing("") is None
