import unittest  # Module for testing
from collections import Counter  # Necessary module


# Signals:
def cooperate_step():
    return "cooperate"


def cheat_step():
    return "cheat"


# The main idea is that the first we update prev_step:
def steps(step: int, player1: object, player2: object):
    player1.update_prev_step()
    player2.update_prev_step()

    if player1.get_behavior_type() == "detective":
        player1.check_cheat(player2)

    if player2.get_behavior_type() == "detective":
        player2.check_cheat(player1)

    if (player1.get_behavior_type() == "copycat") or (player1.get_behavior_type() == "grudger"):
        player1.update_next_step(player2)
    elif player1.get_behavior_type() == "detective":
        player1.update_next_step(step, player2)
    elif player1.get_behavior_type() == "silver":
        player1.update_next_step(step)

    if (player2.get_behavior_type() == "copycat") or (player2.get_behavior_type() == "grudger"):
        player2.update_next_step(player1)
    elif player2.get_behavior_type() == "detective":
        player2.update_next_step(step, player1)
    elif player2.get_behavior_type() == "silver":
        player2.update_next_step(step)


# Function for describe:
def result(step: int, player1: object, player2: object):
    print("----------", "ROUND №", step, "----------")
    print("     Player № 1 has:", player1.get_candies())
    print("     Player № 2 has:", player2.get_candies())


class Player(object):  # Father class
    def __init__(self, behavior_type: str = "", candies: int = 0):
        self.next_step = ""
        self.prev_step = ""
        self.behavior_type = behavior_type

        if candies < 0:
            self.candies = 0
        else:
            self.candies = candies

    def get_next_step(self):
        return self.next_step

    def get_prev_step(self):
        return self.prev_step

    def get_candies(self):
        return self.candies

    def change_candies(self, candies: int):
        self.candies = self.get_candies() + candies

    def get_behavior_type(self):  # For detective functions
        return self.behavior_type

    def update_prev_step(self):  # Always use for all users
        self.prev_step = self.get_next_step()


# Users classes:
class Cheater(Player):
    def __init__(self, behavior_type: str = "cheater"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cheat_step()

    def update_next_step(self):
        self.next_step = cheat_step()


class Cooperator(Player):
    def __init__(self, behavior_type: str = "cooperator"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cooperate_step()

    def update_next_step(self):
        self.next_step = cooperate_step()


class Copycat(Player):
    def __init__(self, behavior_type: str = "copycat"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cooperate_step()

    def update_next_step(self, player: object):
        self.next_step = player.get_prev_step()


class Grudger(Player):
    def __init__(self, behavior_type: str = "grudger"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cooperate_step()

    def update_next_step(self, player: object):
        if (player.get_prev_step() == cheat_step()) or (self.get_next_step() == cheat_step()):
            self.next_step = cheat_step()
        else:
            self.next_step = cooperate_step()


class Detective(Player):
    def __init__(self, behavior_type: str = "detective"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cooperate_step()
        self.cheat_flag = False

    def check_cheat(self, player: object):
        if player.get_prev_step() == cheat_step():
            self.cheat_flag = True

    def update_next_step(self, step: int, player: object):
        if step == 0:
            self.next_step = cheat_step()
        elif step in [1, 2]:
            self.next_step = cooperate_step()
        elif self.cheat_flag:
            self.next_step = player.get_prev_step()
        else:
            self.next_step = cheat_step()


class Silver(Player):  # My class
    def __init__(self, behavior_type: str = "silver"):
        super().__init__(behavior_type)
        self.behavior_type = behavior_type
        self.next_step = cheat_step()

    def update_next_step(self, step: int):
        if step == 1:
            self.next_step = cooperate_step()
        else:
            self.next_step = cheat_step()


class Game(object):

    def __init__(self, matches: int = 10):
        if matches < 1:
            self.matches = 1
        else:
            self.matches = matches

        self.registry = Counter()

    def top3(self):
        #     # print("\n\nTop players are:")
        #     # print(*self.registry.most_common()[0:2])
        return self.registry.most_common()[0: 2]

    # For updating collections:
    def update_top(self, player1: object, player2: object):
        if player1.get_candies() > player2.get_candies():
            self.registry.update([player1.get_behavior_type()])
        elif player2.get_candies() > player1.get_candies():
            self.registry.update([player2.get_behavior_type()])

    def play(self, player1: object, player2: object):
        print("\n\nBefore the game players have:", player1.get_candies(), " - ", player2.get_candies(), end="\n\n")

        for i in range(0, self.matches):
            # Both cheaters:
            if (player1.get_next_step() == player2.get_next_step()) and (player1.get_next_step() == cheat_step()):
                steps(i, player1, player2)

            # Both cooperate:
            elif (player1.get_next_step() == player2.get_next_step()) and (player1.get_next_step() == cooperate_step()):
                player1.change_candies(2)
                player2.change_candies(2)

                steps(i, player1, player2)

            # First cheater, the second cooperate
            elif player1.get_next_step() == cheat_step():
                player1.change_candies(3)
                player2.change_candies(-1)

                steps(i, player1, player2)
            # Second cheater, the first cooperate
            else:
                player1.change_candies(-1)
                player2.change_candies(3)

                steps(i, player1, player2)

            result(i, player1, player2)
        self.update_top(player1, player2)

        print()


# If users have draw no one win:
if __name__ == "__main__":  # Case if we don't import module (tests)
    class TestsEx01(unittest.TestCase):

        def tests_cheater(self):
            game = Game()

            # Cheater games:
            # № 1: Cheater vs Cooperate:
            cheater = Cheater()
            cooperate = Cooperator()
            game.play(cheater, cooperate)
            self.assertEqual(cheater.get_candies(), 30)
            self.assertEqual(cooperate.get_candies(), -10)

            # № 2: Cheater vs Copycat:
            cheater = Cheater()
            copycat = Copycat()
            game.play(cheater, copycat)
            self.assertEqual(cheater.get_candies(), 3)
            self.assertEqual(copycat.get_candies(), -1)

            # № 3: Cheater vs Grudger:
            cheater = Cheater()
            grudger = Grudger()
            game.play(cheater, grudger)
            self.assertEqual(cheater.get_candies(), 3)
            self.assertEqual(grudger.get_candies(), -1)

            # № 4: Cheater vs Detective:
            cheater = Cheater()
            detective = Detective()
            game.play(cheater, detective)
            self.assertEqual(cheater.get_candies(), 9)
            self.assertEqual(detective.get_candies(), -3)

            # Cooperate games:
            # № 1: Cooperate vs Copycat:
            cooperate = Cooperator()
            copycat = Copycat()
            game.play(cooperate, copycat)
            self.assertEqual(cooperate.get_candies(), 20)
            self.assertEqual(copycat.get_candies(), 20)

            # № 2: Cooperate vs Grudger:
            cooperate = Cooperator()
            grudger = Grudger()
            game.play(cooperate, grudger)
            self.assertEqual(cooperate.get_candies(), 20)
            self.assertEqual(grudger.get_candies(), 20)

            # № 3: Cooperate vs Detective:
            cooperate = Cooperator()
            detective = Detective()
            game.play(cooperate, detective)
            self.assertEqual(cooperate.get_candies(), -1)
            self.assertEqual(detective.get_candies(), 27)

            # # Copycat games:
            # № 1: Copycat vs Detective:
            copycat = Copycat()
            detective = Detective()
            game.play(copycat, detective)
            self.assertEqual(copycat.get_candies(), 18)
            self.assertEqual(detective.get_candies(), 18)

            # № 2: Copycat vs Grudger:
            copycat = Copycat()
            grudger = Grudger()
            game.play(copycat, grudger)
            self.assertEqual(copycat.get_candies(), 20)
            self.assertEqual(grudger.get_candies(), 20)

            # Grudger games:
            # № 1: Grudger vs Detective:
            grudger = Grudger()
            detective = Detective()
            game.play(grudger, detective)
            self.assertEqual(grudger.get_candies(), 7)
            self.assertEqual(detective.get_candies(), 3)

        def tests_top(self):
            game = Game()
            grudger = Grudger()

            # One top:
            cheater = Cheater()
            cooperator = Cooperator()
            game.play(cheater, cooperator)
            self.assertEqual(game.top3(), [("cheater", 1)])

            # Two tops:
            detective = Detective()
            game.play(cooperator, detective)
            game.play(grudger, detective)
            game.play(cheater, detective)
            game.play(cheater, cooperator)
            self.assertEqual(game.top3(), [("cheater", 3), ("detective", 2)])

        # Final test for all difference pairs:
        def tests_final(self):
            game = Game()
            cooperate = Cooperator()
            copycat = Copycat()
            grudger = Grudger()
            cheater = Cheater()
            detective = Detective()

            game.play(cheater, cooperate)
            game.play(cheater, copycat)
            game.play(cheater, grudger)
            game.play(cheater, detective)
            game.play(cooperate, copycat)
            game.play(cooperate, grudger)
            game.play(cooperate, detective)
            game.play(copycat, detective)
            game.play(copycat, grudger)
            game.play(grudger, detective)
            self.assertEqual(game.top3(), [('cheater', 4), ('copycat', 3)])

        # Tests for bonus part (top 2 after cheater):
        def tests_bonus(self):
            game = Game()
            cheater = Cheater()
            cooperate = Cooperator()
            copycat = Copycat()
            grudger = Grudger()
            detective = Detective()
            silver = Silver()
            game.play(silver, cheater)
            game.play(silver, cooperate)
            game.play(silver, copycat)
            game.play(silver, grudger)
            game.play(silver, detective)
            self.assertEqual(game.top3(), [("silver", 4), ("cheater", 1)])

    unittest.main()
