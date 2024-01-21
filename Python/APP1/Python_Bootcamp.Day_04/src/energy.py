import unittest


def filter_and_convert(cables, sockets):  # Create zip of clear items
    filtered_cables = list(filter(check_item, cables))
    filtered_sockets = list(filter(check_item, sockets))

    return list(zip(filtered_cables, filtered_sockets))


def check_item(example: object) -> bool:  # Function clear an iteration object
    if isinstance(example, str):
        if example.startswith(("plug", "socket", "cable")):
            return True

    return False


def get_single_res(index: int, plugs, sockets, cables) -> str:  # Get one iter item
    try:
        return (f"plug {filter_and_convert(cables=cables, sockets=sockets)[index][0]}" +
                f" into {filter_and_convert(cables=cables, sockets=sockets)[index][1]}" +
                f" using {list(filter(check_item, plugs))[index]}")
    except IndexError:
        return (f"weld {list(filter(check_item, cables))[index]}" +
                f" to {list(filter(check_item, sockets))[index]} without plug")


def fix_writing(plugs, sockets, cables) -> object:  # Main function
    # Solution:
    return [get_single_res(index=index, plugs=plugs, sockets=sockets, cables=cables) for index in
            range(len(filter_and_convert(cables=cables, sockets=sockets)))]


class TestEx00(unittest.TestCase):
    # Data for tests:
    plugs = ["plug1", "plug2", "plug3"]
    sockets = ["socket1", "socket2", "socket3", "socket4"]
    cables = ["cable1", "cable2", "cable3", "cable4"]

    plugs_two = ["plugZ", None, "plugY", "plugX"]
    sockets_two = [1, "socket1", "socket2", "socket3", "socket4"]
    cables_two = ["cable2", "cable1", False]

    plugs_trash = [123, None, True]
    sockets_trash = [123, None, True]
    cables_trash = [123, None, True]

    sockets_length_one = ["socket1"]
    cables_length_one = ["cable1", "cable2"]

    sockets_length_two = ["socket1", "socket2"]
    cables_length_two = ["cable1"]

    result_one = ["plug cable1 into socket1 using plug1",
                  "plug cable2 into socket2 using plug2",
                  "plug cable3 into socket3 using plug3",
                  "weld cable4 to socket4 without plug"
                  ]

    result_two = ["plug cable2 into socket1 using plugZ",
                  "plug cable1 into socket2 using plugY"
                  ]

    empty_result = []

    length_result = ["weld cable1 to socket1 without plug"]

    def tests_task(self):  # Tests from task
        self.assertEqual(fix_writing(plugs=self.plugs, sockets=self.sockets, cables=self.cables), self.result_one)
        self.assertEqual(fix_writing(plugs=self.plugs_two, sockets=self.sockets_two,
                                     cables=self.cables_two), self.result_two)

    def tests_exception(self):  # Uncommon tests
        self.assertEqual(fix_writing([], [], []), self.empty_result)
        self.assertEqual(fix_writing(plugs=self.plugs_trash, sockets=self.sockets_trash, cables=self.cables_trash),
                         self.empty_result)

    def tests_length(self):  # Different lengths tests
        self.assertEqual(fix_writing(plugs=[], sockets=self.sockets_length_one, cables=self.cables_length_one),
                         self.length_result)
        self.assertEqual(fix_writing(plugs=[], sockets=self.sockets_length_two, cables=self.cables_length_two),
                         self.length_result)


if __name__ == "__main__":  # Tests
    unittest.main()
