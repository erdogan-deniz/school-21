# Module for work with argument:
import sys

answer = ""  # Result string
have_argument = False  # Bool flag for work with number of strings

try:
    argument_value = int(sys.argv[-1])  # Try to get number of strings

    # If user input incorrect argument:
    if argument_value < 1:
        print("Incorrect input! Value must be bigger than 0")
        sys.exit()  # Exit from script

    have_argument = True
# If we don't have number of strings:
except ValueError:
    argument_value = 1  # Default value of number strings

# Read all lines when we don't have number of lines:
while True:
    try:
        sample = input().strip()  # Delete \\n end of the line

        # If we just press "Enter":
        if not sample:
            break

        # Check is correct line:
        if not sample.startswith("000000") and sample.startswith("00000") and \
                len(sample) == 32 and argument_value > 0:
            answer += sample + '\n'  # Update answer

    # End loop when we get empty line:
    except EOFError:
        break

    # Check do we have argument:
    if have_argument:
        argument_value -= 1

    # Situation when we have less than strings argument:
    if argument_value < 1:
        break

print(answer.rstrip())  # Output the result without last \\n
