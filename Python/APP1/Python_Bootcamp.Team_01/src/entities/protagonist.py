"""This one is responsible for all actions with the class representative Protagonist.

Classes:
    Protagonist - A class for an analog of working with a protagonist.
"""


# Necessary modules:
import time
import random
import additional

# Necessary functions and classes:
from entities.enemy import Enemy
from aiogram.types import Message
from additional import clear_string
from entities.location import Location


class Protagonist:
    """This is a conceptual class representation of a Protagonist.

    :param protagonist_id: Unique number of the protagonist.
    :type protagonist_id: int.
    :param protagonist_type: The type of the protagonist.
    :type protagonist_type: int.

    :ivar armor: The protagonist's armor.
    :vartype armor: int.
    :ivar health:The protagonist's health.
    :vartype health: int.
    :ivar agility: The protagonist's agility.
    :vartype agility: int.
    :ivar strength: The protagonist's strength.
    :vartype strength: int.
    :ivar level: The protagonist's level.
    :vartype level: int.
    :ivar name: The protagonist's name (randomly selected by other methods).
    :vartype name: str.
    :ivar inventory: The protagonist's inventory (contains names of items).
    :vartype inventory: list.
    :ivar talked_npcs: The list of NPCs that the main character will talk to.
    :vartype talked_npcs: list.
    :ivar passed_tasks: The list of tasks that the protagonist has passed.
    :vartype passed_tasks: list.
    :ivar current_tasks: The list of tasks that the protagonist currently has.
    :vartype current_tasks: list.
    :ivar defeated_enemies: The list of enemies that the protagonist has defeated.
    :vartype defeated_enemies: list.
    """

    def __init__(self, protagonist_id: int = None, protagonist_type: str = None):
        """Constructor method.

        :return: It does not return anything, but only set parameters of protagonist.
        :rtype: None.
        """

        # Skills:
        self.armor: int = 1
        self.health: int = 10
        self.agility: int = 1
        self.strength: int = 1

        # Stats
        self.level: int = 1
        self.id: int = protagonist_id
        self.type: str = protagonist_type
        self.name: str = additional.get_name() + ' ' + additional.get_surname()

        # Other:
        self.inventory: list = []
        self.talked_npcs: list = []
        self.passed_tasks: list = []
        self.current_tasks: list = []
        self.defeated_enemies: list = []

    def set_type(self, protagonist_type: str):
        """Thу method for setting the type of protagonist.

        :param protagonist_type: The type of protagonist to install.
        :type protagonist_type: str.

        :return: It does not return anything, but only sets the type.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(protagonist_type, str):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        self.type = protagonist_type

    async def print_parameters(self, message: Message):
        """The method outputs the necessary information about protagonist.

        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but only outputs to the chat.
        :rtype: None.
        """

        await message.answer(
                                "<u>YOUR HERO IS</u>:\n\n"
                                f"<b>Name</b>: <code>{clear_string(self.name)}</code>\n" +
                                f"<b>Type</b>: <code>{clear_string(self.type)}</code>\n" +
                                f"<b>Level</b>: <code>{self.level}</code>\n"
                            )

    def set_start_item(self, protagonist_item: str):
        """The method to add item to the protagonist inventory.

        :param protagonist_item: The item for protagonist inventory.
        :type protagonist_item: str.

        :return: It does not return anything, but only adds an item to the inventory.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(protagonist_item, str):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        self.inventory.append(protagonist_item)

    def set_parameters(self):
        """The method calculates the characteristics of a character relative to its type and items.

        :return: It does not return anything, but only sets parameters of protagonist.
        :rtype: None.

        :raise: Exception: If we do not have item or type.
        """

        if self.type is not None:
            if self.type == "Bladerunner":
                self.armor = 2
                self.strength = 4
                self.agility = 3
            elif self.type == "Phantom-Ghost":
                self.armor = 1
                self.agility = 4
                self.strength = 4
            elif self.type == "Electro-Psycho":
                self.armor = 3
                self.agility = 1
                self.strength = 5
            elif self.type == "Real-Jes":
                self.armor = 3
                self.agility = 3
                self.strength = 3
        else:
            raise Exception("ERROR! HERO DONT HAVE TYPE.")

        if len(self.inventory) > 0:
            if self.inventory[0] == "Gradient Gloves":
                self.armor += 2
            elif self.inventory[0] == "Cyber Policemans Mantle":
                self.armor += 1
                self.agility += 1
            elif self.inventory[0] == "Real Madrid Uniform":
                self.armor += 1
                self.agility += 1
                self.strength += 1
            elif self.inventory[0] == "The Sea Chain":
                self.agility += 1
                self.strength += 1
        else:
            raise Exception("ERROR! HERO DONT HAVE ANY STARTED ITEMS.")

    async def fight(self, current_enemy: Enemy, message: Message):
        """The method for a phased battle with the enemy.

        :param current_enemy: The entity of the enemy for the battle.
        :type current_enemy: Enemy.
        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but fully displays the battle.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(current_enemy, Enemy):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        current_round = 1
        enemy_health = current_enemy.health

        await message.answer("<b>FIGHT BEGINS</b>!\n\n")

        while enemy_health > 0:
            your_stats = self.strength + self.agility + self.armor + random.randint(1, 6)
            enemy_stats = current_enemy.agility + current_enemy.strength + current_enemy.armor + random.randint(1, 6)

            await message.answer(
                                    f"<u>Round №</u> {current_round}:\n\n" +
                                    f"<b>Your skills</b>: <code>{your_stats}</code>\n" +
                                    f"<b>Enemy skills</b>: <code>{enemy_stats}</code>\n"
                                )

            current_round += 1

            if enemy_stats > your_stats:
                await message.answer("<b>YOU LOSE ROUND!</b>\n")
                await self.take_hit(1, message)
            else:
                enemy_health -= 1

                await message.answer("<b>ENEMY LOSE ROUND!</b>\n")

            time.sleep(2)

        await message.answer("<b>CONGRATULATIONS, YOU WIN!</b>\n\n")
        self.defeated_enemies.append(current_enemy.id)

    async def take_hit(self, value=1, message: Message = None):
        """The method of recalculating health after taking damage.

        :param value: The value of the damage received.
        :type value: int.
        :param message: The context of the bot work is necessary for output to a specific chat.
        :type message: Message.

        :return: It does not return anything, but calculate health after taking damage.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(value, int):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        self.health -= value

        if self.health <= 0:
            await message.answer("<b>YOU DIED!</b>")

    # The method for constant level updates:
    def set_level(self):
        """The method of recalculating the level of the main character.

        :return: It does not return anything, but calculate and set level.
        :rtype: None.
        """

        if self.level != 1 + int(len(self.passed_tasks) / 2 + len(self.defeated_enemies) / 2):
            self.agility += 1
            self.strength += 1
            self.armor += 1

        self.level = 1 + int(len(self.passed_tasks) / 2 + len(self.defeated_enemies) / 2)

    def go(self, current_location: Location):
        """The method of getting available transitions.

        :param current_location: The current location where is a protagonist.
        :type current_location: Location.

        :return: It does not return anything, but output available locations.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(current_location, Location):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        print(f"Hero: {self.name}")

        if current_location.left_side is not None:
            print("\tYou can go to the left side!")

        if current_location.right_side is not None:
            print("\tYou can go to the right side!")

        if current_location.bot_side is not None:
            print("\tYou can go to the bot side!")

        if current_location.top_side is not None:
            print("\tYou can go to the top side!")

    def whereami(self, current_location: Location):
        """The method to print current location description.

        :param current_location: The current location where is a protagonist.
        :type current_location: Location.

        :return: It does not return anything, but output location description.
        :rtype: None.

        :raise: Exception: If we get incorrect argument.
        """

        if not isinstance(current_location, Location):
            raise Exception("ERROR! INCORRECT ARGUMENT TYPE.")

        print(f"Hello, {self.name}")
        print(f"You are on location with the next description:\n {current_location.description}")
