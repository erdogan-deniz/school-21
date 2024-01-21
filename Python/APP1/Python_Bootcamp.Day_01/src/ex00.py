# First of all, we don't save any other elements in dictionary
import unittest  # Module for tests


def add_ingot(purse: dict[str, int]) -> dict[str, int]:
    answer: dict[str, int] = {}

    if ("gold_ingot" not in purse) or (purse["gold_ingot"] + 1 < 0):
        answer["gold_ingot"] = 1
    else:
        answer["gold_ingot"] = purse["gold_ingot"] + 1

    return answer


def get_ingot(purse: dict[str, int]) -> dict[str, int]:
    answer: dict[str, int] = {}

    if ("gold_ingot" in purse) and (purse["gold_ingot"] > 1):
        answer["gold_ingot"] = purse["gold_ingot"] - 1

    return answer


def empty(purse: dict[str, int]) -> dict[str, int]:
    answer: dict[str, int] = {}

    return answer


if __name__ == "__main__":  # Case if we don't import module (tests)
    class TestsEx00(unittest.TestCase):

        def tests_add_ingot(self):
            self.assertEqual(add_ingot({}), {"gold_ingot": 1})
            self.assertEqual(add_ingot({"something": 1}), {"gold_ingot": 1})
            self.assertEqual(add_ingot({"gold_ingot": 0}), {"gold_ingot": 1})
            self.assertEqual(add_ingot({"gold_ingot": 1}), {"gold_ingot": 2})
            self.assertEqual(add_ingot({"gold_ingot": -3}), {"gold_ingot": 1})
            self.assertEqual(add_ingot(add_ingot({"gold_ingot": 1})), {"gold_ingot": 3})
            self.assertEqual(add_ingot(add_ingot({"gold_ingot": -3})), {"gold_ingot": 2})

        def tests_get_ingot(self):
            self.assertEqual(get_ingot({}), {})
            self.assertEqual(get_ingot({"something": 1}), {})
            self.assertEqual(get_ingot({"gold_ingot": 1}), {})
            self.assertEqual(get_ingot({"gold_ingot": -2}), {})
            self.assertEqual(get_ingot({"gold_ingot": 20}), {"gold_ingot": 19})

        def tests_empty(self):
            self.assertEqual(empty({}), {})
            self.assertEqual(empty({"gold_ingot": 1}), {})
            self.assertEqual(empty({"something": -2}), {})
            self.assertEqual(empty({"gold_ingot": -2}), {})
            self.assertEqual(empty({"gold_ingot": 20}), {})

        def tests_combinations(self):
            self.assertEqual(empty(empty(empty({}))), {})
            self.assertEqual(add_ingot(add_ingot(add_ingot({}))), {"gold_ingot": 3})
            self.assertEqual(get_ingot(get_ingot(get_ingot({"gold_ingot": 5}))), {"gold_ingot": 2})
            self.assertEqual(get_ingot(add_ingot(get_ingot({"gold_ingot": 5}))), {"gold_ingot": 4})
            self.assertEqual(add_ingot(get_ingot(add_ingot(empty({"gold_ingot": 1})))), {"gold_ingot": 1})

    unittest.main()
