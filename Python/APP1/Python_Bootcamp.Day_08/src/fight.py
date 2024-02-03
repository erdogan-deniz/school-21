# Necessary modules:
import asyncio

from random import choice
from enum import Enum, auto


# Class of actions:
class Action(Enum):
    HIGHKICK = auto()
    LOWKICK = auto()
    HIGHBLOCK = auto()
    LOWBLOCK = auto()


# Class of agent:
class Agent:

    def __aiter__(self, health=5):
        self.health = health
        self.actions = list(Action)

        return self

    async def __anext__(self):
        return choice(self.actions)


# Neos turn logic:
def neos_turn(action: Action):
    if not isinstance(action, Action):  # Check argument
        print("\nERROR! INCORRECT ARGUMENT TYPE.\n")

        return -1

    if action == Action.HIGHKICK:
        return Action.HIGHBLOCK
    elif action == Action.LOWKICK:
        return Action.LOWBLOCK
    elif action == Action.HIGHBLOCK:
        return Action.LOWKICK
    elif action == Action.LOWBLOCK:
        return Action.HIGHKICK


# Calculate agent health:
def health_calculation(agent_turn: Action, neo_turn: Action, agent_health: int):
    if ((not isinstance(agent_turn, Action)) or (not isinstance(neo_turn, Action)) or
            (not isinstance(agent_health, int))):  # Check argument
        print("\nERROR! INCORRECT ARGUMENT TYPE.\n")

        return -1

    # Check the correction of value of agent health:
    if agent_health < 1:
        print("\nERROR! INCORRECT ARGUMENT VALUE.\n")

        return -1

    # Cases when agent get kick:
    if (agent_turn == Action.LOWBLOCK) and (neo_turn == Action.HIGHKICK):
        return agent_health - 1
    elif (agent_turn == Action.HIGHBLOCK) and (neo_turn == Action.LOWKICK):
        return agent_health - 1
    else:
        return agent_health


# Main function:
async def fight():
    # Create objects:
    agent = Agent()

    # Fill data:
    agent.__aiter__()

    # Get persons turns:
    agent_turn = await agent.__anext__()
    neo_turn = neos_turn(agent_turn)

    print()

    # Run process:
    while agent.health > 0:
        print(f"Agent: {agent_turn}, Neo: {neo_turn}, Agent Health: "
              f"{health_calculation(agent_turn, neo_turn, agent.health)}")

        agent.health = health_calculation(agent_turn, neo_turn, agent.health)
        agent_turn = await agent.__anext__()
        neo_turn = neos_turn(agent_turn)

    print("\nNeo wins!\n")


if __name__ == "__main__":
    asyncio.run(fight())  # ex00
