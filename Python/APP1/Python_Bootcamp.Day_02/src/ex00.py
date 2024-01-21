import unittest  # Module for testing


class Key(object):
    def __init__(self, len_in_bytes: int = 1337, value_404: int = 3, value: int = 10000, passphrase: str = "zax2rulez",
                 string: str = "GeneralTsoKeycard"):

        if len_in_bytes < 0:
            self.len_in_bytes = 0
        else:
            self.len_in_bytes = len_in_bytes

        # Variables for functions:
        self.value_404 = value_404
        self.value = value
        self.passphrase = passphrase
        self.string = string

    def __len__(self):
        return self.len_in_bytes

    def __getitem__(self, index: int):
        if index == 404:
            return self.value_404
        else:
            return 0

    def __gt__(self, neighbour: int):
        return self.value > neighbour

    def __str__(self):
        return self.string


if __name__ == "__main__":  # Case if we don't import module (tests)
    class TestsEx00(unittest.TestCase):

        def test_one(self):  # Test from task
            key = Key()

            self.assertEqual(len(key), 1337)
            self.assertEqual(key[404], 3)
            self.assertEqual(key > 9000, True)
            self.assertEqual(key.passphrase, "zax2rulez")
            self.assertEqual(str(key), "GeneralTsoKeycard")

        def test_two(self):
            key = Key(1337, 3, 9001, "abc", "GeneralTsoKeycard")

            self.assertEqual(len(key), 1337)
            self.assertEqual(key[404], 3)
            self.assertEqual(key > 9000, True)
            self.assertEqual(key.passphrase, "abc")
            self.assertEqual(str(key), "GeneralTsoKeycard")

        def test_three(self):
            key = Key(-10, 3, 9001, "abc", "def")

            self.assertEqual(len(key), 0)
            self.assertEqual(key[-5], 0)
            self.assertEqual(key > 9000, True)
            self.assertEqual(key.passphrase, "abc")
            self.assertEqual(str(key), "def")


    unittest.main()
