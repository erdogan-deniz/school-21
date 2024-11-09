"""The module has the minimum and necessary functionality to work with the database.

Functions:
    configuration_database - The function parses all the necessary database parameters.
    connection_database - The function connects to the database.
    close_connection_database - The function disconnects from the database.
    drop_tables - The function deletes all existing tables.
    create_tables - The function creates tables if they do not exist.
    load_information - The function completely fills in the table.
    get_row - The function writes one entity to a table.
"""

# Necessary modules:
import psycopg2

# Necessary functions and classes:
from configparser import ConfigParser


def configuration_database(filename: str = "database.ini", section: str = "postgresql"):
    """The function to configure connection to the database.

    :param filename: The file names for getting connection parameters.
    :type filename: str.
    :param section: The dbms names.
    :type section: str.

    :return: The dictionary of connection parameters.
    :rtype: dict.

    :raise: Exception: If we get incorrect argument.
    """

    if (not isinstance(filename, str)) or (not isinstance(section, str)):  # Incorrect type of argument
        raise Exception("ERROR! INCORRECT ARGUMENT.")

    database = {}
    parser = ConfigParser()

    parser.read(filename)

    if parser.has_section(section):  # Take arguments for connection
        parameters = parser.items(section)

        for parameter in parameters:
            database[parameter[0]] = parameter[1]

        return database

    raise Exception(f"ERROR! SECTION {section} NOT FOUND IN THE {filename} FILE.")


def connection_database():
    """The database connection function.

    :return: The connector to the database.
    :rtype: psycopg2.extensions.connection.

    :raise: Exception: If it was not possible to connect to the database.
    """

    try:
        params = configuration_database()  # Set params
        connection = psycopg2.connect(**params)  # Connect to the database

        return connection

    except Exception as error:
        raise Exception(str(error).upper())


def close_connection_database(connection):
    """The function to close database connection.

    :param connection: The connector to the database.
    :type connection: psycopg2.extensions.connection.

    :return: It does not return anything, but only changes the state of the connector.
    :rtype: None.

    :raise: Exception: If it was not possible to connect to the database.
    """

    if connection is not None:
        try:
            connection.close()

        except Exception as error:
            raise Exception(str(error).upper())
    else:
        raise Exception("ERROR! INCORRECT CONNECTION.")


def drop_tables(tables: list):
    """The function to drop all existing tables.

    :param tables: The list of tables name.
    :type tables: list.

    :return: It does not return anything, but only changes the state of the connector.
    :rtype: None.

    :raise: Exception: If we don't get tables names.
    """

    if not isinstance(tables, list):
        raise Exception("ERROR! INCORRECT ARGUMENT.")

    connection = connection_database()
    cursor = connection.cursor()  # For any changes in database

    for table in tables:
        cursor.execute('DROP TABLE IF EXISTS public."' + str(table) + '";')

    connection.commit()  # Save changes
    cursor.close()
    close_connection_database(connection)


def create_tables():
    """The function of creating database tables.

    :return: It does not return anything, but only changes the state of the connector.
    :rtype: None.
    """

    connection = connection_database()
    cursor = connection.cursor()  # For any changes in database

    # Table "Dialogs":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."Dialogs"
                    (
                        id bigint NOT NULL,
                        phrase text COLLATE pg_catalog."default" NOT NULL,
                        answer text COLLATE pg_catalog."default" NOT NULL,
                        "number" bigint NOT NULL,
                        location_id bigint NOT NULL,
                        CONSTRAINT "Dialogs_pkey" PRIMARY KEY (id)
                    )
                    """
                   )

    # Table "Enemies":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."Enemies"
                    (
                        id bigint NOT NULL,
                        armor bigint NOT NULL DEFAULT 0,
                        health bigint NOT NULL DEFAULT 1,
                        agility bigint NOT NULL DEFAULT 1,
                        strength bigint NOT NULL DEFAULT 1,
                        name text COLLATE pg_catalog."default" NOT NULL,
                        CONSTRAINT "Enemies_pkey" PRIMARY KEY (id)
                    )
                    """
                  )

    # Table "Locations":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."Locations"
                    (
                        id bigint NOT NULL,
                        item text COLLATE pg_catalog."default",
                        name text COLLATE pg_catalog."default" NOT NULL,
                        npc_id bigint,
                        top_side bigint,
                        bot_side bigint,
                        enemy_id bigint,
                        type text COLLATE pg_catalog."default" NOT NULL,
                        left_side bigint,
                        right_side bigint,
                        description text COLLATE pg_catalog."default" NOT NULL,
                        required_item text COLLATE pg_catalog."default",
                        area text COLLATE pg_catalog."default" NOT NULL,
                        CONSTRAINT "Locations_pkey" PRIMARY KEY (id)
                    )"""
                  )

    # Table "NPCs":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."NPCs"
                    (
                        id bigint NOT NULL,
                        name text COLLATE pg_catalog."default" NOT NULL,
                        item text COLLATE pg_catalog."default",
                        description text COLLATE pg_catalog."default" NOT NULL,
                        CONSTRAINT "NPCs_pkey" PRIMARY KEY (id)
                    )"""
                  )

    # Table "Protagonists":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."Protagonists"
                    (
                        id bigint NOT NULL,
                        type text COLLATE pg_catalog."default" NOT NULL DEFAULT 'bladerunner'::text,
                        armor bigint NOT NULL DEFAULT 0,
                        level bigint NOT NULL DEFAULT 1,
                        strength bigint NOT NULL DEFAULT 1,
                        completed_tasks text[] COLLATE pg_catalog."default",
                        name text COLLATE pg_catalog."default" NOT NULL DEFAULT 'James'::text,
                        health bigint NOT NULL DEFAULT 1,
                        passed_npcs text[] COLLATE pg_catalog."default",
                        defeated_enemies text[] COLLATE pg_catalog."default",
                        inventory text[] COLLATE pg_catalog."default",
                        CONSTRAINT "Protagonist_pkey" PRIMARY KEY (id)
                    )"""
                  )

    # Table "Tasks":
    cursor.execute(
                    """CREATE TABLE IF NOT EXISTS public."Tasks"
                    (
                        id bigint NOT NULL,
                        name text COLLATE pg_catalog."default" NOT NULL,
                        description text COLLATE pg_catalog."default" NOT NULL,
                        difficult text COLLATE pg_catalog."default" NOT NULL,
                        CONSTRAINT "Tasks_pkey" PRIMARY KEY (id)
                    )"""
                  )

    connection.commit()  # Save changes
    cursor.close()
    close_connection_database(connection)


def load_information(loading_data: list):
    """The function for uploading data to the database.

    :param loading_data: The list of sql queries.
    :type loading_data: list.

    :return: It does not return anything, but changed connector status.
    :rtype: None.

    :raise: Exception: If we get argument of incorrect type.
    """

    if not isinstance(loading_data, list):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    connection = connection_database()
    cursor = connection.cursor()  # For any changes in database
    data_number = 1

    # Add all locations from prepare dataset:
    for current_data in loading_data:
        cursor.execute(current_data)
        print(f"THE DATA № {data_number} HAS BEEN ADDED.")

        data_number += 1

    print()
    connection.commit()  # Save changes
    cursor.close()
    close_connection_database(connection)


def get_row(data_number: int, table_name: str):
    """The function for getting a specific row of an arbitrary table.

    :param data_number: The number of string in the database.
    :type data_number: int.
    :param table_name: The name of the table for requests.
    :type table_name: str.

    :return: Return turple of values for one entity in database.
    :rtype: tuple.

    :raise: Exception: If we get argument of incorrect type.
    """
    if (not isinstance(data_number, int)) or (not isinstance(table_name, str)):
        raise Exception("ERROR! INCORRECT ARGUMENT.")

    connection = connection_database()
    cursor = connection.cursor()

    cursor.execute(f'SELECT * FROM public."{table_name}" WHERE id = {data_number}')  # Take necessary string

    row = cursor.fetchone()  # Put it in tuple

    cursor.close()
    close_connection_database(connection)

    if row is None:
        raise Exception("ERROR! DONT GET DATA.")

    return row
