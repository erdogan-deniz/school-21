# First of all, we don't save any other elements in dictionary
import unittest  # Module for tests
import ex00  # Module for functions


def split_booty(*args) -> tuple[dict[str, int], dict[str, int], dict[str, int]]:
    purse, purse_two, purse_three = {}, {}, {}
    gold_ingots = 0

    for arg in args:
        if isinstance(arg, dict) and ("gold_ingots" in arg) and (arg["gold_ingots"] > 0):
            gold_ingots += arg["gold_ingots"]

    purse["gold_ingots"] = gold_ingots // 3
    purse_two["gold_ingots"] = gold_ingots // 3
    purse_three["gold_ingots"] = gold_ingots // 3

    if (gold_ingots % 3) == 1:
        return ex00.add_ingot(purse), purse_two, purse_three
    elif (gold_ingots % 3) == 2:
        return ex00.add_ingot(purse), ex00.add_ingot(purse_two), purse_three
    else:
        return purse, purse_two, purse_three


if __name__ == "__main__":  # Case if we don't import module (tests)
    class TestsEx01(unittest.TestCase):

        def tests_split_booty(self):
            self.assertEqual(split_booty({}), ({"gold_ingots": 0}, {"gold_ingots": 0}, {"gold_ingots": 0}))
            self.assertEqual(split_booty({"something": 2}, {"some_something": 3}), ({"gold_ingots": 0},
                                                                                    dict(gold_ingots=0),
                                                                                    dict(gold_ingots=0)))
            self.assertEqual(split_booty({"gold_ingots": 3}, {"gold_ingots": 2}, {"apples": 10}),
                             ({"gold_ingots": 2}, {"gold_ingots": 2}, {"gold_ingots": 1}))
            self.assertEqual(split_booty({"gold_ingots": -2}, {"gold_ingots": 0}, {"apples": 10}),
                             ({"gold_ingots": 0}, {"gold_ingots": 0}, {"gold_ingots": 0}))
            self.assertEqual(split_booty({"gold_ingots": 3}, {"gold_ingots": 3}, {"apples": 10}),
                             ({"gold_ingots": 2}, {"gold_ingots": 2}, {"gold_ingots": 2}))
            self.assertEqual(split_booty({"gold_ingots": 3}, {"gold_ingots": 4}, {"apples": 10}),
                             ({"gold_ingots": 3}, {"gold_ingots": 2}, {"gold_ingots": 2}))


    unittest.main()
