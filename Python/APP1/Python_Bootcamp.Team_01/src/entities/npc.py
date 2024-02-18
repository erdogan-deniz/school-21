"""This one is responsible for all actions with the class representative NPC.

Classes:
    NPC - A class for an analog of working with a NPC.

Functions:
    set_npc - A method for filling in the data fields of a class representative NPC.
"""

# Necessary modules:
import database

# Necessary functions and classes:
from aiogram.types import Message
from additional import clear_string
from entities.location import Location


# The function for endless setting NPC:
def set_npc(current_location: Location):
    """The function of setting data for a specific npc.

    :param current_location: The location from which we take data for the npc.
    :type current_location: Location.

    :return: A representative of the class with the completed data.
    :rtype: NPC.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(current_location, Location):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    if current_location.type == "NPC":
        new_npc = database.get_row(current_location.npc_id, "NPCs")

        return NPC(*new_npc)

    return NPC()


class NPC:
    """This is a conceptual class representation of an NPC.

    :param npc_id: Unique number of the NPC.
    :type npc_id: int.
    :param npc_name: The name of the NPC.
    :type npc_name: str.
    :param npc_item: The item of the NPC.
    :type npc_item: str.
    :param npc_description: Description of a neutral character.
    :type npc_description: str.
    """

    def __init__(self, npc_id: int = None, npc_name: str = None, npc_item: str = None, npc_description: str = None):
        """Constructor method.

        :return: It does not return anything, but only set parameters of NPC.
        :rtype: None.
        """

        self.id: int = npc_id
        self.name: str = npc_name
        self.item: str = npc_item
        self.description: str = npc_description

    async def print_parameters(self, message: Message):
        """The method outputs the necessary information about NPC.

        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but only outputs to the chat.
        :rtype: None.
        """

        await message.answer(
                                f"<u>NPC DATA:</u>\n\n" +
                                f"<b>NPC name</b>: <code>{clear_string(self.name)}</code>\n" +
                                f"<b>NPC description</b>: <code>{clear_string(self.description)}</code>\n"
                            )
