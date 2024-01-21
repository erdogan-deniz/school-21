# Module for argumnet parsing:
import argparse

is_first_letter = True
parser = argparse.ArgumentParser()  # Add parser
parser.add_argument("string", help="An argument for decypher type of string")
args = parser.parse_args()  # Parse aguments

# Output all first letters in lowcase of our argument:
for ch in args.string.strip():
	if ch == ' ':
		is_first_letter = True
	elif is_first_letter:
		print(ch.lower(), end='')
		is_first_letter = False

print()  # New line for the ending of programm
