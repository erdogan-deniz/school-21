"""This one is responsible for all actions with the class representative Enemy.

Classes:
    Enemy - A class for an analog of working with an enemy.

Functions:
    set_enemy - A function for filling in the data fields of a class representative Enemy.
"""

# Necessary modules:
import database

# Necessary functions and classes:
from aiogram.types import Message
from additional import clear_string
from entities.location import Location


# The function for endless setting NPC:
def set_enemy(current_location: Location):
    """The function of setting data for a specific enemy.

    :param current_location: The location from which we take data for the enemy.
    :type current_location: Location.

    :return: A representative of the class with the completed data.
    :rtype: Enemy.

    :raise: Exception: If we get incorrect argument.
    """

    if not isinstance(current_location, Location):
        raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

    if current_location.type == "Enemy":
        new_enemy = database.get_row(current_location.enemy_id, "Enemies")

        return Enemy(*new_enemy)

    return Enemy()


class Enemy:
    """This is a conceptual class representation of an Enemy.

    :param enemy_id: Unique number of the enemy.
    :type enemy_id: int.
    :param enemy_armor: The armor of the enemy.
    :type enemy_armor: int.
    :param enemy_health: The health of the enemy.
    :type enemy_health: int.
    :param enemy_agility: The agility of the enemy.
    :type enemy_agility: int.
    :param enemy_strength: The strength of the enemy.
    :type enemy_strength: int.
    :param enemy_name: The name of the enemy.
    :type enemy_name: str.
    """

    def __init__(
                    self, enemy_id: int = None, enemy_armor: int = None, enemy_health: int = None,
                    enemy_agility: int = None, enemy_strength: int = None, enemy_name: str = None
                ):
        """Constructor method.

        :return: It does not return anything, but only set parameters of enemy.
        :rtype: None.
        """

        # Main information:
        self.id: int = enemy_id
        self.name: str = enemy_name

        # Parameters:
        self.armor: int = enemy_armor
        self.health: int = enemy_health
        self.agility: int = enemy_agility
        self.strength: int = enemy_strength

    async def print_parameters(self, message: Message):
        """The method outputs the necessary information about enemy.

        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but only outputs to the chat.
        :rtype: None.
        """

        await message.answer(
                                f"<u>ENEMY DATA</u>:\n\n" +
                                f"<b>Enemy name</b>: <code>{clear_string(self.name)}</code>\n" +
                                f"<b>Enemy armor</b>: <code>{self.armor}</code>\n" +
                                f"<b>Enemy health</b>: <code>{self.health}</code>\n" +
                                f"<b>Enemy agility</b>: <code>{self.agility}</code>\n" +
                                f"<b>Enemy strength</b>: <code>{self.strength} </code>"
                            )
