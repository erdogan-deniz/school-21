"""The module of additional functions necessary for the bot to work.

Functions:
    clear_string - The function of clearing the string of unnecessary characters.
    get_time - Function for getting a current time.
    get_date - Function for getting a current date.
    get_name - Function for getting a random name.
    get_surname - Function for getting a random surname.
    get_dialogs - A function for getting a dialog in the form of a tuple of lists.
    print_dialogs - The function prints the entire dialogue between the protagonist and the NPC.
"""

# Necessary modules:
import data
import time
import random
import database

# Necessary functions and classes:
from asyncio import sleep
from aiogram.types import Message


def clear_string(text: str):
    """The function for clearing the text of the characters of the film adaptation.

    :param text: The text that will be cleaned.
    :type text: str.

    :return: The cleaned line.
    :rtype: str.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(text, str):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    while '\n' in text:
        text = text.replace('\n', ' ')

    while '\t' in text:
        text = text.replace('\t', ' ')

    while '  ' in text:
        text = text.replace('  ', ' ')

    return text


def get_time():
    """The function of getting the current time.

    :return: The time.
    :rtype: str.
    """

    current_time = time.localtime()

    return f"{current_time.tm_hour}:{current_time.tm_min}"


def get_date():
    """The function of getting the current date.

    :return: The date.
    :rtype: str.
    """

    current_date = time.localtime()

    return f"{current_date.tm_year}-{current_date.tm_mon}-{current_date.tm_mday}"


def get_name():
    """The function to get random protagonist name.

    :return: The random name.
    :rtype: str.
    """

    return random.choice(data.protagonist_names)


def get_surname():
    """The function to get random protagonist surname.

    :return: The random surname.
    :rtype: str.
    """

    return random.choice(data.protagonist_surnames)


def get_dialogs(location_id: int):
    """The function of creating a tuple of a hero's dialogue with an unknown NPC.

    :param location_id: The location from which we take data.
    :type location_id: int.

    :return: A turple of replicas of each character.
    :rtype: tuple.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(location_id, int):
        raise Exception("ERROR! INCORRECT ARGUMENT.")

    connection = database.connection_database()
    cursor = connection.cursor()

    cursor.execute(f'SELECT * FROM public."Dialogs" WHERE location_id = {location_id}')  # Take necessary string

    dialogs = cursor.fetchall()  # Put it in tuple

    cursor.close()
    database.close_connection_database(connection)

    if not dialogs:
        return None

    result = []

    for dialog in dialogs:  # Parse all dialogs and answers
        result.append([dialog[1], dialog[2]])

    return result


async def print_dialogs(dialogs: tuple, message: Message):
    """The function for displaying all dialog messages.

    :param dialogs: The phrases.
    :type dialogs: tuple.
    :param message: The context of the bot work is necessary for output to a specific chat.
    :type message: Message.

    :return: A turple of replicas of each character.
    :rtype: tuple.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(dialogs, list):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    await message.answer("<u>DIALOG</u>:")

    for dialog in dialogs:
        await message.answer(f"<i>{clear_string(dialog[0])}</i>")
        await sleep(1)
        await message.answer(f"<i>{clear_string(dialog[1])}</i>")
        await sleep(1)
