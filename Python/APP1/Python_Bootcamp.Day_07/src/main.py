"""Voight-Kampff test

This module is designed to use blade runners to identify a suspected replicant or human.

This file can also be imported as a module and contains the following
functions:

    * test - returns the result of test
    * main - the main function of the script
"""

# Necessary modules:
import random
import process
import support


# Main function:
def test():
    """
    Main test function that prognosis replicant.

    :rtype: None
    :return: Nothing and output result if we don't have errors.
    """

    questions = support.read_json("questions")
    answers = support.read_json("answers")

    if (questions != -1) and (answers != -1):
        support.greetings()
        print()

        result = 0

        for i in questions:
            support.typing(questions[i])

            print()

            support.typing(random.choice(answers[i]))

            print()
            print()

            result += process.check_respiration()
            result += process.check_heart_rate()
            result += process.check_blushing_level()
            result += process.check_pupillary_dilation()
            print()

        process.make_decision(result)


if __name__ == "__main__":
    test()
