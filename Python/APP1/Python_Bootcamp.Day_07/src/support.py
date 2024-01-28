"""Support functions

This module is auxiliary and necessary for calculations during the test.

This file can also be imported as a module and contains the following
functions:

    * read_json - returns python data structure or error number
    * typing - output message
    * is_integer - returns integer value or error status
    * greetings - output greetings
    * main - the main function of the script
"""

# Necessary modules:
import sys
import time
import json


# Function to read json data:
def read_json(file_name: str):
    """
    The function that serializer json to python data structure.

    :param file_name: The name of json file.
    :type file_name: str

    :rtype: int, dict
    :return: -1 if we get error, dict if we convert json data.
    """

    if not isinstance(file_name, str):  # Incorrect type of argument case
        typing("\nERROR! INCORRECT ARGUMENT TYPE.\n")

        return -1

    elif file_name.strip() == "":  # Empty file name case
        typing("\nERROR! EMPTY FILE NAME.\n")

        return -1

    try:  # Uncreated file case
        open(f"{file_name}.json", "r")

    except FileNotFoundError:
        typing("\nERROR! FILE IS NOT EXISTS!\n")

        return -1

    try:  # Empty file case
        with open(f"{file_name}.json", "r") as read_file:
            data = json.loads(read_file.read())

            return data

    except json.decoder.JSONDecodeError:
        typing("\nERROR! DATA IS CRUSHED!\n")

        return -1


# Simulation terminal typing:
def typing(message: str):
    """
    The function that simulate terminal output.

    :param message: The message that we need to output.
    :type message: str

    :rtype: int, None
    :return: -1 if we get error, else output message.
    """

    if not isinstance(message, str):  # Incorrect type of argument case
        typing("\nERROR! INCORRECT ARGUMENT TYPE.\n")

        return -1

    for char in message:
        sys.stdout.write(char)
        sys.stdout.flush()  # Print immediately character
        time.sleep(0.045)

    time.sleep(1)  # Time sleep for new sentence


# Check the is correct integer value or not:
def is_integer():
    """
    The function that check input is integer value.

    :rtype: int
    :return: -1 if we get error, else value.
    """

    try:
        value = int(input())

        return value

    except ValueError:
        typing("\nINCORRECT INPUT TYPE! INPUT AGAIN.\n")

        return -1


# Start by this message:
def greetings():
    """
    The function that make greetings to user.

    :rtype: None
    :return: output message
    """

    typing("\n              Hello!\n\n")
    typing(" Now you have to take the Voight-Kampf test.")
    typing(" I think you know firsthand about him.\n")
    typing(" I will clarify that this test does not test your intelligence.")
    typing(" The main thing here is the speed of the response.")
    typing(" Answer quickly without hesitation.\n")
    typing(" So, sit back, and if you have no questions, let's get started!\n")
