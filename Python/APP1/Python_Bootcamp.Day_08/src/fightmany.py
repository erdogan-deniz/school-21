# Necessary modules:
import fight
import random


# Function checks that agents already are defeated:
def check_agents_health(getting_agents):
    if getting_agents is not None:
        for agent in getting_agents:
            if agent.health > 0:
                return False

    return True


async def fightmany(agent_number: int):
    if not isinstance(agent_number, int):  # Check argument
        print("\nERROR! INCORRECT ARGUMENT TYPE.\n")
        exit()

    # Create objects:
    agent = fight.Agent()

    # Fill data:
    agent.__aiter__()

    # Get persons turns:
    agent_turn = await agent.__anext__()
    neo_turn = fight.neos_turn(agent_turn)

    # Run process:
    while agent.health > 0:
        await fight.asyncio.sleep(random.randint(1, 5))

        print(f"Agent {agent_number + 1}: {agent_turn}, Neo: {neo_turn}, Agent {agent_number + 1} Health: "
              f"{fight.health_calculation(agent_turn, neo_turn, agent.health)}")

        agent.health = fight.health_calculation(agent_turn, neo_turn, agent.health)
        agent_turn = await agent.__anext__()
        neo_turn = fight.neos_turn(agent_turn)


if __name__ == "__main__":
    print()

    agents = [fight.Agent() for _ in range(3)]
    ioloop = fight.asyncio.get_event_loop()
    tasks = []

    for i in range(3):
        tasks.append(ioloop.create_task(fightmany(i)))

    wait_tasks = fight.asyncio.wait(tasks)
    ioloop.run_until_complete(wait_tasks)
    ioloop.close()

    print("\nNeo wins!\n\n")
