"""This one is responsible for all actions with the class representative Task.

Classes:
    Task - A class for an analog of working with a task.

Functions:
    set_task - A function for filling in the data fields of a class representative Task.
"""

# Necessary modules:
import database

# Necessary functions and classes:
from aiogram.types import Message
from additional import clear_string
from entities.location import Location


# The function for endless setting task:
def set_task(current_location: Location):
    """
    The function of setting data for a specific task.

    :param current_location: The location from which we take data for the task.
    :type current_location: Location.

    :return: A representative of the class with the completed data.
    :rtype: Task.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(current_location, Location):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    if current_location.id == 2:
        new_task = database.get_row(1, "Tasks")

        return Task(*new_task)
    elif current_location.id == 10:
        new_task = database.get_row(2, "Tasks")

        return Task(*new_task)

    return Task()


class Task:
    """This is a conceptual class representation of a Task.

    :param task_id: The unique number of task.
    :type task_id: int.
    :param task_name: The name of task.
    :type task_id: str.
    :param task_description: The description of the task.
    :type task_description: str.
    :param task_difficult: The difficult of the task.
    :type task_difficult: str.
    """

    def __init__(
                    self, task_id: int = None, task_name: str = None, task_description: str = None,
                    task_difficult: str = None
                ):
        """Constructor method.

        :return: It does not return anything, but only set parameters of task.
        :rtype: None.
        """

        self.id: int = task_id
        self.name: str = task_name
        self.difficult: str = task_difficult
        self.description: str = task_description

    async def print_parameters(self, message: Message):
        """The method outputs the necessary information about task.

        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but only outputs to the chat.
        :rtype: None.
        """

        await message.answer(
                                f"<u>THIS IS TASK</u> № {self.id}:\n\n" +
                                f"<b>Task difficult</b>: <code>{self.difficult}</code>\n" +
                                f"<b>Task name</b>: <code>{clear_string(self.name)}</code>\n" +
                                f"<b>Task description</b>: <i>{clear_string(self.description)}</i>\n"
                            )
