# First of all, we don't save any other elements in dictionary
import unittest  # Module for tests
import ex00  # Module for functions


def decorator(func: object) -> object:
    def message(*args) -> object:
        print("squeaky")
        return func(*args)

    return message


ex00.add_ingot = decorator(ex00.add_ingot)
ex00.get_ingot = decorator(ex00.get_ingot)
ex00.empty = decorator(ex00.empty)

if __name__ == "__main__":  # Case if we don't import module (tests)
    class TestsEx02(unittest.TestCase):

        def tests_decorator(self):
            self.assertEqual(ex00.add_ingot({}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot({"something": 1}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot({}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot({"something": 1}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot({"gold_ingots": 0}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot({"gold_ingots": 1}), {"gold_ingots": 2})
            self.assertEqual(ex00.add_ingot({"gold_ingots": -3}), {"gold_ingots": 1})
            self.assertEqual(ex00.add_ingot(ex00.add_ingot({"gold_ingots": 1})), {"gold_ingots": 3})
            self.assertEqual(ex00.add_ingot(ex00.add_ingot({"gold_ingots": -3})), {"gold_ingots": 2})
            self.assertEqual(ex00.get_ingot({}), {})
            self.assertEqual(ex00.get_ingot({"something": 1}), {})
            self.assertEqual(ex00.get_ingot({"gold_ingots": 1}), {})
            self.assertEqual(ex00.get_ingot({"gold_ingots": -2}), {})
            self.assertEqual(ex00.get_ingot({"gold_ingots": 20}), {"gold_ingots": 19})
            self.assertEqual(ex00.empty({}), {})
            self.assertEqual(ex00.empty({"gold_ingots": 1}), {})
            self.assertEqual(ex00.empty({"something": -2}), {})
            self.assertEqual(ex00.empty({"gold_ingots": -2}), {})
            self.assertEqual(ex00.empty({"gold_ingots": 20}), {})
            self.assertEqual(ex00.empty(ex00.empty(ex00.empty({}))), {})
            self.assertEqual(ex00.add_ingot(ex00.add_ingot(ex00.add_ingot({}))), {"gold_ingots": 3})
            self.assertEqual(ex00.get_ingot(ex00.get_ingot(ex00.get_ingot({"gold_ingots": 5}))), {"gold_ingots": 2})
            self.assertEqual(ex00.get_ingot(ex00.add_ingot(ex00.get_ingot({"gold_ingots": 5}))), {"gold_ingots": 4})


    unittest.main()
