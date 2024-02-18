"""The module is used to fill in the table Locations.

Functions:
    load_map - The function fill in the table.
"""

import data
import database


def load_map():
    """The function for filling map table.

    :return: It does not return anything, but only fill the table.
    :rtype: None.

    :raise: Exception: If we get error of filling data.
    """

    try:
        print("\nSTART FILLING DATA...\n")
        database.drop_tables(["Locations"])
        database.create_tables()  # Create databases if there are not exist
        database.load_information(data.locations_data)
        print("THE DATA HAS BEEN FILLED.")
    except Exception:
        raise Exception("ERROR! INCORRECT LOAD DATA.")


# The switch of script logic:
if __name__ == "__main__":
    load_map()
