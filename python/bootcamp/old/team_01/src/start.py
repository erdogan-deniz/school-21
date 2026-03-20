"""This module contains all the functionality related to the bot.

Functions:
    get_actions - The function generates a list of buttons available to the user depending on the conditions.
    main - The function logs and launches the bot.

Handlers:
    escape - The handler implementing the logic of the end of the game.
    pass_task - The handler implementing the logic of passing the NPC task.
    fight - The handler implements the logic of the fight between the protagonist and the enemy.
    take - The handler implements the logic of taking tasks from an NPC.
    pick - The handler implements the logic of selecting the subject of the location.
    talk - The handler carries out a conversation between the NPC and the protagonist.
    left_test_location - The handler switches to the left location during the test.
    left_location - The handler switches to the left location in the game.
    bot_location - The handler switches to the bot location in the game.
    bot_test_location - The handler switches to the bot location during the test.
    right_location - The handler switches to the right location in the game.
    top_location - The handler switches to the top location in the game.
    right_test_location - The handler switches to the right location during the test.
    top_test_location - The handler switches to the top location during the test.
    end - The handler exits the test.
    start - The handler performs the start of work with the bot.
    test - The handler enables the test mode.
    give_up - The handler carries out the loss in the game.
    set_up - The handler allows you to make game settings.
    exit_menu - The handler exits the menu.
    back - The handler takes a step back.
    chain_select - The handler selects the subject sea chains.
    uniform_select - The handler selects the subject real madrid uniform.
    mantle_select - The handler selects the subject policeman's mantle.
    gloves_select - The handler selects the subject gloves.
    set_item - The handler adds a starter item to the user.
    set_type - The handler sets the character type.
    bladerunner_select - The handler sets the character type bladerunner.
    phantom_select - The handler sets the character type phantom-ghost.
    jes_select - The handler sets the character type real-jes.
    electro_select - The handler sets the character type electro-psycho.
    game_launched - The handler starts the game.
    echo - The handler responds to an unknown command.
"""

# Necessary modules:
import asyncio
import logging
import database
import entities.npc
import entities.task
import entities.enemy
import entities.location
import entities.protagonist

# Necessary classes and functions:
from asyncio import sleep
from aiogram.filters import Command
from entities.npc import NPC, set_npc
from entities.location import Location
from aiogram import Bot, Dispatcher, F
from bot_data import ADMIN_ID, TOKEN_API
from entities.task import Task, set_task
from entities.enemy import Enemy, set_enemy
from entities.protagonist import Protagonist
from additional import print_dialogs, get_dialogs
from aiogram.types import Message, KeyboardButton, ReplyKeyboardMarkup, FSInputFile

# Starter type and item:
hero_type = "Bladerunner"
hero_item = "Gradient Gloves"

# The main using data:
main_npc = NPC()
main_task = Task()
main_enemy = Enemy()
main_protagonist = entities.protagonist.Protagonist()  # Create protagonist
main_location = Location(*database.get_row(1, "Locations"))

# Create bot and his dispatcher:
dispatcher = Dispatcher()
bot = Bot(token=TOKEN_API, parse_mode="HTML")


# The function to generate all available actions and buttons:
def get_actions(
        current_location: Location = None, current_protagonist: Protagonist = None, current_npc: NPC = None,
        current_task: Task = None, current_enemy: Enemy = None, is_test: bool = True
):
    """The function is used to continuously update the user actions panel.

    :param current_location: The location where the action takes place.
    :type current_location: Location.
    :param current_protagonist: The current protagonist.
    :type current_protagonist: Protagonist.
    :param current_npc: The NPC on the location.
    :type current_npc: NPC.
    :param current_task: The task on the location.
    :type current_task: Task.
    :param current_enemy: The enemy on the location.
    :type current_enemy: Enemy.
    :param is_test: The flag to check is it a test or not.
    :type is_test: bool.

    :return: A list of buttons for actions and the attached text to explain the available actions.
    :rtype: turple (list, str).
    """

    if current_location is not None:  # Check that we have correct location
        if is_test:
            list_of_actions = "👾  <b>END</b> - to finish testing  👾"
            buttons = [[KeyboardButton(text="👾END👾")]]

            if current_location.left_side is not None:
                list_of_actions = "⬅️  <b>LEFT_TEST</b> - to go left location  ⬅️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬅️LEFT_TEST⬅️")])

            if current_location.bot_side is not None:
                list_of_actions = "⬇️  <b>BOT_TEST</b> - to go bot location  ⬇️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬇️BOT_TEST⬇️")])

            if current_location.right_side is not None:
                list_of_actions = "➡️  <b>RIGHT_TEST</b> - to go right location  ➡️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="➡️RIGHT_TEST➡️")])

            if current_location.top_side is not None:
                list_of_actions = "⬆️  <b>TOP_TEST</b> - to go top location  ⬆️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬆️TOP_TEST⬆️")])

            return list_of_actions, buttons
        else:  # If we play
            if current_location.id == 8:
                list_of_actions = "🏳️  <b>GIVE UP</b> - to be loser  🏳️"
                buttons = [[KeyboardButton(text="🏳️GIVE UP🏳️")]]

                return list_of_actions, buttons

            list_of_actions = "🏳️  <b>GIVE UP</b> - to be loser  🏳️"
            buttons = [[KeyboardButton(text="🏳️GIVE UP🏳️")]]

            if current_location.left_side is not None:
                list_of_actions = "⬅️  <b>LEFT</b> - to go left location  ⬅️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬅️LEFT⬅️")])

            if current_location.bot_side is not None:
                list_of_actions = "⬇️  <b>BOT</b> - to go bot location  ⬇️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬇️BOT⬇️")])

            if current_location.right_side is not None:
                list_of_actions = "➡️  <b>RIGHT</b> - to go right location  ➡️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="➡️RIGHT➡️")])

            if current_location.top_side is not None:
                list_of_actions = "⬆️  <b>TOP</b> - to go top location  ⬆️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⬆️TOP⬆️")])

            # Add actions to talk with npc and fight with enemy:
            if (current_location.type == "NPC") and (current_npc.id not in current_protagonist.talked_npcs):
                list_of_actions = "🗣  <b>TALK</b> - to talk with NPC  🗣\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="🗣TALK🗣")])
            elif (current_location.type == "Enemy") and (current_enemy.id not in current_protagonist.defeated_enemies):
                list_of_actions = "⚔️  <b>FIGHT</b> - to fight with enemy  ⚔️\n" + list_of_actions
                buttons.insert(0, [KeyboardButton(text="⚔️FIGHT⚔️")])

            # Add action to take location item:
            if current_location.item is not None:
                if current_location.item not in current_protagonist.inventory:
                    list_of_actions = "🖐  <b>PICK</b> - to take item  🖐\n" + list_of_actions
                    buttons.insert(0, [KeyboardButton(text="🖐PICK🖐")])

            # Add action to take task:
            if current_task.name is not None:
                if (current_task.id not in current_protagonist.current_tasks) and \
                        (current_task.id not in current_protagonist.passed_tasks):
                    list_of_actions = "💽  <b>TAKE</b> - to take npc task  💽\n" + list_of_actions
                    buttons.insert(0, [KeyboardButton(text="💽TAKE💽")])

        # Check that we have task to pass:
        if (((1 in current_protagonist.defeated_enemies) and (1 in current_protagonist.current_tasks) and
             (current_location.id == 2)) or (("Titanium Shackles" in current_protagonist.inventory) and
                                             (2 in current_protagonist.current_tasks) and (current_location.id == 10))):
            list_of_actions = "💵  <b>PASS</b> - to pass npc task  💵\n" + list_of_actions
            buttons.insert(0, [KeyboardButton(text="💵PASS💵")])

        # Check that we have task to pass:
        if (current_location.id == 18) and ("E-key" in current_protagonist.inventory):
            list_of_actions = '🗽  <b>ESCAPE</b> - to escape from "Cyber World"  🗽\n' + list_of_actions
            buttons.insert(0, [KeyboardButton(text="🗽ESCAPE🗽")])

        return list_of_actions, buttons


@dispatcher.message(F.text == "🗽ESCAPE🗽")
async def escape(message: Message):
    """The handler to complete the game.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    # Read the audio file:
    audio = FSInputFile("audios/end.mpeg")

    await bot.send_audio(message.chat.id, audio)
    await message.answer('CONGRATULATIONS, YOU HAVE <s>LOS...</s> ESCAPED FROM <b>"The Cyber World"</b>!')
    await sleep(1)
    await message.answer("The whole story turned out to be real, it turns out that you saved someones life.")
    await message.answer("If you have any comments or suggestions, please write to the author at <b>@Denzi333</b>.")
    await sleep(3)
    await message.answer("<b> THANK YOU!</b>")

    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "💵PASS💵")
async def pass_task(message: Message):
    """The handler to submit assignment.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)
    main_protagonist.set_level()

    if main_location.id == 2:
        main_protagonist.current_tasks.remove(1)
        main_protagonist.passed_tasks.append(1)

        await message.answer('You get <b>"Enigma Gun"</b>!')

        main_protagonist.inventory.append("Enigma Gun")
    elif main_location.id == 10:
        main_protagonist.current_tasks.remove(2)
        main_protagonist.passed_tasks.append(2)
        main_protagonist.inventory.remove("Titanium Shackles")
        await message.answer('You gave up the <b>"Titanium Shackles"</b>!')
        await message.answer('You get <b>"E-key"</b>!')
        main_protagonist.inventory.append("E-key")

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⚔️FIGHT⚔️")
async def fight(message: Message):
    """The handler to fight with enemy.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()
    await main_enemy.print_parameters(message)
    await main_protagonist.fight(main_enemy, message)

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "💽TAKE💽")
async def take(message: Message):
    """The handler to take location task.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()
    await main_task.print_parameters(message)
    main_protagonist.current_tasks.append(main_task.id)

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "🖐PICK🖐")
async def pick(message: Message):
    """The handler to pick location item.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()
    await message.answer(f"You have picked up <b>{main_location.item}</b>!")
    main_protagonist.inventory.append(main_location.item)

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "🗣TALK🗣")
async def talk(message: Message):
    """The handler to talk with NPC.

    :param message: The context of the telegram chat.
    :type message: Message.

    :return: Does not return anything, but only works in the Telegram.
    :rtype: None.
    """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()
    main_protagonist.talked_npcs.append(main_npc.id)
    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)
    await print_dialogs(get_dialogs(main_location.id), message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬅️LEFT_TEST⬅️")
async def left_test_location(message: Message):
    """The handler to go to the left location in the test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    # Set next location:
    main_location = entities.location.Location(*database.get_row(main_location.left_side, "Locations"))
    actions, buttons = get_actions(main_location, is_test=True)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬅️LEFT⬅️")
async def left_location(message: Message):
    """The handler to go to the left location.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_location = entities.location.Location(*database.get_row(main_location.left_side, "Locations"))
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    await main_location.print_parameters(message)

    if main_location.id == 8:
        await message.answer("<b>You've fallen into a trap!</b>")

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬇️BOT⬇️")
async def bot_location(message: Message):
    """The handler to go to the bot location.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    if (main_location.id == 14) and (main_protagonist.level < 3):
        await message.answer("<b>THE LEVEL IS TOO SMALL!</b>\n\n")
    else:
        # Set next entities:
        main_location = entities.location.Location(*database.get_row(main_location.bot_side, "Locations"))
        main_npc = set_npc(main_location)
        main_task = set_task(main_location)
        main_enemy = set_enemy(main_location)

        main_protagonist.set_level()

        actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

        await main_location.print_parameters(message)

        if buttons is not None:
            keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

            await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬇️BOT_TEST⬇️")
async def bot_test_location(message: Message):
    """The handler to go to the bot location in the test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    # Set next location:
    main_location = entities.location.Location(*database.get_row(main_location.bot_side, "Locations"))
    actions, buttons = get_actions(main_location, is_test=True)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "➡️RIGHT➡️")
async def right_location(message: Message):
    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_location = entities.location.Location(*database.get_row(main_location.right_side, "Locations"))
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)
    main_protagonist.set_level()
    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬆️TOP⬆️")
async def top_location(message: Message):
    """The handler to go to the top location.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location, main_protagonist, main_npc, main_task, main_enemy

    # Set next entities:
    main_location = entities.location.Location(*database.get_row(main_location.top_side, "Locations"))
    main_npc = set_npc(main_location)
    main_task = set_task(main_location)
    main_enemy = set_enemy(main_location)

    main_protagonist.set_level()

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, is_test=False)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "➡️RIGHT_TEST➡️")
async def right_test_location(message: Message):
    """The handler to go to the right location in the test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    # Set next location:
    main_location = entities.location.Location(*database.get_row(main_location.right_side, "Locations"))
    actions, buttons = get_actions(main_location, is_test=True)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "⬆️TOP_TEST⬆️")
async def top_test_location(message: Message):
    """The handler to go to the top location in the test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    # Set next location:
    main_location = entities.location.Location(*database.get_row(main_location.top_side, "Locations"))
    actions, buttons = get_actions(main_location, is_test=True)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "👾END👾")
async def end(message: Message):
    """The handler to end test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    buttons = [[KeyboardButton(text="⚠️TEST⚠️"), KeyboardButton(text="✅SET UP✅")]]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(f'Hello new hero, <b>{message.from_user.first_name}</b>!' +
                         f'\nWelcome to the game 🏃‍♂️<tg-spoiler>️"Escape From Cyber World"</tg-spoiler> 🌐\n')
    await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" +
                         '1️⃣  TEST - to get to know the "Cyber World"\n' +
                         "2️⃣  SET UP - to customize your character, start the adventure\n",
                         reply_markup=keyboard)


@dispatcher.message(Command("start"))
async def start(message: Message):
    """The handler to start work with bot.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [[KeyboardButton(text="⚠️TEST⚠️"), KeyboardButton(text="✅SET UP✅")]]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(f'Hello new hero, <b>{message.from_user.first_name}</b>!' +
                         f'\nWelcome to the game 🏃‍♂️<tg-spoiler>️"Escape From Cyber World"</tg-spoiler> 🌐\n')
    await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" +
                         '1️⃣  TEST - to get to know the "Cyber World"\n' +
                         "2️⃣  SET UP - to customize your character, start the adventure\n",
                         reply_markup=keyboard)


@dispatcher.message(F.text == "⚠️TEST⚠️")
async def test(message: Message):
    """The handler test.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location

    # Set first location
    main_location = entities.location.Location(*database.get_row(1, "Locations"))
    actions, buttons = get_actions(main_location, is_test=True)

    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message(F.text == "🏳️GIVE UP🏳️")
async def give_up(message: Message):
    """The handler to lose game.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "✅SET UP✅")
async def set_up(message: Message):
    """The handler to set reference of game.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🌚EXIT🌚")
async def exit_menu(message: Message):
    """The handler to exit to the menu.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [[KeyboardButton(text="⚠️TEST⚠️"), KeyboardButton(text="✅SET UP✅")]]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(f'Hello new hero, <b>{message.from_user.first_name}</b>!' +
                         f'\nWelcome to the game 🏃‍♂️<tg-spoiler>️"Escape From Cyber World"</tg-spoiler> 🌐\n')
    await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" +
                         '1️⃣  TEST - to get to know the "Cyber World"\n' +
                         "2️⃣  SET UP - to customize your character, start the adventure\n",
                         reply_markup=keyboard)


@dispatcher.message(F.text == "🚶‍♂️BACK🚶‍♂️")
async def back(message: Message):
    """The handler to go back to the settings.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🌊THE SEA CHAIN🌊")
async def chain_select(message: Message):
    """The handler to choice item sea chain.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_item

    hero_item = "The Sea Chain"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER'S STARTING ITEM HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "⚽️REAL MADRID UNIFORM⚽️")
async def uniform_select(message: Message):
    """The handler to choice item real madrid uniform.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_item

    hero_item = "Real Madrid Uniform"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER'S STARTING ITEM HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "👮‍♂️CYBER POLICEMANS MANTLE👮‍♂️")
async def mantle_select(message: Message):
    """The handler to choice item cyber policeman's mantle.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_item

    hero_item = "Cyber Policemans Mantle"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER'S STARTING ITEM HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🧤GRADIENT GLOVES🧤")
async def gloves_select(message: Message):
    """The handler to choice item gradient gloves.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_item

    hero_item = "Gradient Gloves"

    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER'S STARTING ITEM HAS BEEN SELECTED!</b>")

    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🗡SET ITEM🗡")
async def set_item(message: Message):
    """The handler to set protagonist item.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [
        [KeyboardButton(text="🧤GRADIENT GLOVES🧤"), KeyboardButton(text="👮‍♂️CYBER POLICEMANS MANTLE👮‍♂️")],
        [KeyboardButton(text="⚽️REAL MADRID UNIFORM⚽️"), KeyboardButton(text="🌊THE SEA CHAIN🌊")],
        [KeyboardButton(text="🚶‍♂️BACK🚶‍♂️")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE A HERO START ITEM</u>:\n\n"
        '1️⃣  GRADIENT GLOVES - to choice the character item "Gradient Gloves"\n' +
        '2️⃣  CYBER POLICEMANS MANTLE - to choice the character item "Cyber Policemans Mantle"\n' +
        '3️⃣  REAL MADRID UNIFORM  - to choice the character item "Real Madrid Uniform "\n' +
        '4️⃣  THE SEA CHAIN - to choice the character item "The Sea Chain"' +
        '5️⃣  BACK - to return back to set up',
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🎭SET TYPE🎭")
async def set_type(message: Message):
    """The handler to set protagonist type.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    buttons = [
        [KeyboardButton(text="🌀BLADERUNNER🌀"), KeyboardButton(text="🎴PHANTOM-GHOST🎴")],
        [KeyboardButton(text="😎REAL-JES😎"), KeyboardButton(text="⚡️ELECTRO-PSYCHO⚡️")],
        [KeyboardButton(text="🚶‍♂️BACK🚶‍♂️"), ]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer(
        "<u>PLEASE, CHOICE A HERO TYPE</u>:\n\n"
        '1️⃣  BLADERUNNER - to set the character type "Bladerunner"\n' +
        '2️⃣  PHANTOM-GHOST - to set the character type "Phantom-Ghost"\n' +
        '3️⃣  REAL-JES  - to set the character type "Real-Jes"\n' +
        '4️⃣  ELECTRO-PSYCHO - to set the character type "Electro-Psycho"' +
        '5️⃣  BACK - to return back to set up',
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🌀BLADERUNNER🌀")
async def bladerunner_select(message: Message):
    """The handler to choice type bladerunner.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_type

    hero_type = "Bladerunner"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER TYPE HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "🎴PHANTOM-GHOST🎴")
async def phantom_select(message: Message):
    """The handler to choice type phantom-ghost.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_type

    hero_type = "Phantom-Ghost"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER TYPE HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "😎REAL-JES😎")
async def jes_select(message: Message):
    """The handler to choice type real-jes.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_type

    hero_type = "Real-Jes"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER TYPE HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "⚡️ELECTRO-PSYCHO⚡️")
async def electro_select(message: Message):
    """The handler to choice type electro-psycho.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global hero_type

    hero_type = "Electro-Psycho"
    buttons = [
        [KeyboardButton(text="🗡SET ITEM🗡"), KeyboardButton(text="🎭SET TYPE🎭")],
        [KeyboardButton(text="👹LEEEROY JENKIS...👹"), KeyboardButton(text="🌚EXIT🌚")]
    ]
    keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

    await message.answer("<b>THE CHARACTER TYPE HAS BEEN SELECTED!</b>")
    await message.answer(
        "<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n"
        "1️⃣  SET ITEM - to choice a protagonist item\n" +
        "2️⃣  SET TYPE - to choice a protagonist type\n" +
        '3️⃣  LEEEROY JENKIS... - to immerse yourself in "Cyber World"\n' +
        "4️⃣  EXIT - to exit from settings",
        reply_markup=keyboard
    )


@dispatcher.message(F.text == "👹LEEEROY JENKIS...👹")
async def game_launched(message: Message):
    """The handler to start the game.

     :param message: The context of the telegram chat.
     :type message: Message.

     :return: Does not return anything, but only works in the Telegram.
     :rtype: None.
     """

    global main_location, main_protagonist, hero_type, hero_item, main_task

    # Set first location:
    main_location = entities.location.Location(*database.get_row(1, "Locations"))
    main_protagonist = Protagonist()
    main_task = Task()

    main_protagonist.type = hero_type
    main_protagonist.inventory = [hero_item]
    main_protagonist.set_parameters()  # Set protagonist stats
    main_protagonist.set_level()

    actions, buttons = get_actions(main_location, main_protagonist, main_npc, main_task, main_enemy, False)

    await main_protagonist.print_parameters(message)
    await main_location.print_parameters(message)

    if buttons is not None:
        keyboard = ReplyKeyboardMarkup(keyboard=buttons, resize_keyboard=True)

        await message.answer("<u>PLEASE, CHOICE THE BUTTON AND PRESS IT</u>:\n\n" + actions, reply_markup=keyboard)


@dispatcher.message()
async def echo(message: Message):
    """The method for handling unintended commands.

    :param message: The context of the bot work is necessary for output to a specific chat.
    :type message: Message.

    :return: It does not return anything, but only outputs the message.
    :rtype: None.
    """

    await message.answer("I DON'T UNDERSTAND YOU, SORRY!")


async def main():
    """The function that performs the work of the bot.

    :return: It does not return anything, but only starts bot work.
    :rtype: None.
    """

    try:
        logging.basicConfig(filename="actions.log", level=logging.DEBUG)
        await bot.delete_webhook(drop_pending_updates=True)  # Make only first greetings
        await dispatcher.start_polling(bot)  # Start bot work
    finally:
        await bot.session.close()  # Close bot work


# Check that start point goes from this script:
if __name__ == "__main__":
    asyncio.run(main())
