"""The module is used to fill in the tables: NPCs, Enemies, Dialogs, Tasks, Protagonists.

Functions:
    load_data - The function fills in the listed tables.
"""

import data
import database


def load_data():
    """The function for filling in all database tables without map.

    :return: It does not return anything, but only fill the tables.
    :rtype: None.

    :raise: Exception: If we get error of filling data.
    """
    try:
        print("\nSTART FILLING DATA...\n")
        database.drop_tables(["Dialogs", "Enemies", "NPCs", "Tasks", "Protagonists"])
        database.create_tables()  # Create databases if there are not exist
        database.load_information(data.npcs_data)
        database.load_information(data.tasks_data)
        database.load_information(data.dialogs_data)
        database.load_information(data.enemies_data)
        database.load_information(data.protagonist_data)
        print("THE DATA HAS BEEN FILLED.")
    except Exception:
        raise Exception("ERROR! INCORRECT LOAD DATA.")


# The point to start load data:
if __name__ == "__main__":
    load_data()
