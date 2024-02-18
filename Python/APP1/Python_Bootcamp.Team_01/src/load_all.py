"""The module is used to fill in the tables: NPCs, Enemies, Dialogs, Tasks, Protagonists, Locations.

Functions:
    load_all - The function fills in the listed tables.
"""

# Necessary modules:
import data
import database


def load_all():
    """The function for filling in all database tables.

    :return: It does not return anything, but only fill the tables.
    :rtype: None.

    :raise: Exception: If we get error of filling data.
    """

    try:
        print("\nSTART FILLING DATA...\n")
        database.drop_tables(["Dialogs", "Enemies", "Locations", "NPCs", "Protagonists", "Tasks"])  # Drop all tables
        database.create_tables()  # Create databases if there are not exist
        database.load_information(data.npcs_data)
        database.load_information(data.tasks_data)
        database.load_information(data.dialogs_data)
        database.load_information(data.enemies_data)
        database.load_information(data.locations_data)
        print("DATA HAS BEEN FILLED.")
    except Exception:
        raise Exception("ERROR! INCORRECT LOAD DATA.")


# If we want to run this script:
if __name__ == "__main__":
    load_all()
