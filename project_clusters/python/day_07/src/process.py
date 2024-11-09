"""Process functions

This module is used to perform the calculations necessary to calculate replicants.

This file can also be imported as a module and contains the following
functions:

    * check_respiration - returns determination to replicant respiration
    * check_heart_rate - returns determination to replicant heart rate
    * check_blushing_level - returns determination to replicant blushin level
    * check_pupillary_dilation - returns determination to replicant pupillary
    * make_decision - returns binary value of replicant determination
    * main - the main function of the script
"""

# Necessary modules:
import support


# Functions for input variables:
def check_respiration():
    """The function that gets and check respiration. Repeated input until don't get the correct value.

    :rtype: int
    :return: 1 if count of bpm bigger than 14, else 0.
    """

    support.typing("Respiration in BPM is: ")

    bpm = support.is_integer()

    while (bpm < 12) or (bpm > 16):
        if bpm != -1:
            support.typing("\nINCORRECT VALUE! PLEASE, INPUT AGAIN.\n")

        support.typing("Respiration in BPM is: ")

        bpm = support.is_integer()

    if bpm >= 15:
        return 1

    return 0


def check_heart_rate():
    """The function that gets and check heart rate. Repeated input until don't get the correct value.

    :rtype: int
    :return: 1 if count of heart rates bigger than 84, else 0.
    """

    support.typing("Hearth rate is: ")

    heart_rate = support.is_integer()

    while (heart_rate < 60) or (heart_rate > 100):
        if heart_rate != -1:
            support.typing("\nINCORRECT VALUE! PLEASE, INPUT AGAIN.\n")

        support.typing("Hearth rate is: ")

        heart_rate = support.is_integer()

    if heart_rate >= 85:
        return 1

    return 0


def check_blushing_level():
    """The function that gets and check blushing level. Repeated input until don't get the correct value.

    :rtype: int
    :return: 1 of value of blushing_level bigger than 4, else 0.
    """

    support.typing("Blushing level is: ")

    blushing_level = support.is_integer()

    while (blushing_level < 1) or (blushing_level > 6):
        if blushing_level != -1:
            support.typing("\nINCORRECT VALUE! PLEASE, INPUT AGAIN.\n")

        support.typing("Blushing level is: ")

        blushing_level = support.is_integer()

    if blushing_level >= 5:
        return 1

    return 0


def check_pupillary_dilation():
    """The function that gets and check pupillary dilation. Repeated input until don't get the correct value.

    :rtype: int
    :return: 1 if value of pupillary dilation bigger than 5, else 0.
    """

    support.typing("Pupillary dilation: ")

    pupillary_dilation = support.is_integer()

    while (pupillary_dilation < 2) or (pupillary_dilation > 8):
        if pupillary_dilation != -1:
            support.typing("\nINCORRECT VALUE! PLEASE, INPUT AGAIN.\n")

        support.typing("Pupillary dilation: ")

        pupillary_dilation = support.is_integer()

    if pupillary_dilation >= 6:
        return 1

    return 0


# Calculating result:
def make_decision(points: int):
    """The function that make decision about suspect, is he replicant or not.

    :param points: The count of replicant points of user.
    :type points: int

    :rtype: int
    :return: 1 if suspect is a replicant, 0 if suspect is a human, -1 if we get error.
    """

    support.typing("Process...\n")

    if not isinstance(points, int):  # Incorrect type of argument case
        support.typing("\nERROR! INCORRECT ARGUMENT TYPE.\n")

        return -1

    if (points < 0) or (points > 40):
        support.typing("\nERROR! INCORRECT COUNT OF POINTS.\n")

        return -1

    elif points > 15:
        support.typing("THE SUSPECT IS A REPLICANT!\n")

        return 1

    else:
        support.typing("THE SUSPECT IS A MAN!\n")

        return 0
