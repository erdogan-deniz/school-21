import time  # Module for little freezing
import random as rd  # Module for randomize value


def emit_gel(step: int = 2):  # Main function for generated pressure
    # If we get an incorrect step:
    if step < 2:
        step = 2

    random_step: int = rd.randint(1, step)  # Sampled step
    left_l: int = 0
    right_l: int = 100

    while True:  # Endless stream of number
        pressure: int = rd.randrange(left_l, right_l, random_step)

        time.sleep(0.75)
        print("The pressure is: ", pressure, end='')
        print("\tThe random step is: ", random_step)

        if (pressure > 100) or (pressure < 0):
            print("ERROR")
            yield -999
        elif (pressure < 10) or (pressure > 90):
            print("The marginal value")
            yield -666
        elif (pressure < 20) or (pressure > 80):
            changer = yield

            if changer:
                left_l, right_l = right_l, left_l
                random_step *= -1
                changer = False

                yield pressure


# Function which switch:
def valve(test_case: int = 1):
    gen = emit_gel(test_case)  # Get a step for loop

    while True:
        tmp = next(gen)  # Get generator

        try:
            if (tmp == -666) or (tmp == -999):  # Exceptions
                break
            elif (tmp < 20) or (tmp > 80):  # Switch
                gen.send(True)
        except TypeError:  # Switch situation
            gen.send(True)


# Check tests:
if __name__ == "__main__":
    for test in range(11):
        valve(test)  # Test function
        print()  # Newline
