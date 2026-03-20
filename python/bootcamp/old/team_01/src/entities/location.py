"""This one is responsible for all actions with the class representative Location.

Classes:
    Location - A class for an analog of working with a location.
"""

# Necessary modules:
import additional

# Necessary functions and classes:
from additional import clear_string
from aiogram.types import Message, FSInputFile


class Location:
    """This is a conceptual class representation of a Location.

    :param location_id: Unique number of the location.
    :type location_id: int.
    :param location_item: The item that is located on the location.
    :type location_item: int.
    :param location_name: The name of the location.
    :type location_name: str.
    :param location_npc_id: The unique number of npc whose is on location.
    :type location_npc_id: int.
    :param location_top_side: The unique location number on top.
    :type location_top_side: int.
    :param location_bot_side: The unique location number on bot.
    :type location_bot_side: int.
    :param location_enemy_id: The unique number of npc whose is on location.
    :type location_enemy_id: int.
    :param location_type: The type of location.
    :type location_type: str.
    :param location_left_side: The unique location number on left.
    :type location_left_side: int.
    :param location_right_side: The unique location number on right.
    :type location_right_side: int.
    :param location_description: Description of the location.
    :type location_description: str.
    :param current_required_item: The item is necessary to complete the location.
    :type current_required_item: str.
    :param location_area: The area of the location.
    :type location_area: str.
    """

    def __init__(
                    self, location_id: int, location_item: str, location_name: str, location_npc_id: int,
                    location_top_side: int, location_bot_side: int, location_enemy_id: int, location_type: str,
                    location_left_side: int, location_right_side: int, location_description: str,
                    current_required_item: str, location_area: str
                ):
        """Constructor method.

        :return: It does not return anything, but only set parameters of location.
        :rtype: None.
        """

        # Stats:
        self.id: int = location_id
        self.item: str = location_item
        self.name: str = location_name
        self.type: str = location_type
        self.area: str = location_area
        self.description: str = location_description
        self.required_item: str = current_required_item

        # Other creatures:
        self.npc_id: int = location_npc_id
        self.enemy_id: int = location_enemy_id

        # Nearby locations:
        self.top_side: int = location_top_side
        self.bot_side: int = location_bot_side
        self.left_side: int = location_left_side
        self.right_side: int = location_right_side

    async def print_parameters(self, message: Message):
        """The method outputs the necessary information about location.

        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but only outputs to the chat.
        :rtype: None.
        """

        # Open existing photo for chat answer:
        photo = FSInputFile(f"photos/{self.id}.jpg", "rb")

        await message.answer_photo(photo, caption=f"<u>THIS IS LOCATION</u> № {self.id}:\n\n" +
                                                  f"<b>Time</b>: <code>{clear_string(additional.get_time())}</code>\n" +
                                                  f"<b>Data</b>: <code>{clear_string(additional.get_date())}</code>\n" +
                                                  f"<b>Area</b>: <code>{clear_string(self.area)}</code>\n" +
                                                  f"<b>Name</b>: <code>{clear_string(self.name)}</code>\n" +
                                                  f"<b>Description</b>: <i>{clear_string(self.description)} </i>"
                                   )
