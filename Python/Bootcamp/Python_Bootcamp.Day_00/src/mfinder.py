# Module for regular expressions:
import re

counter = 0  # Counter of strings:
answer = True

while True:
	try:
		sample = input().strip()  # Read string

		if not sample:  # If user press "Enter"
			break

		counter += 1

		if counter == 1 and \
			(re.fullmatch(r"\*([^\*]+)\*", sample) is None):
			answer *= False
		elif counter == 2 and \
			(re.fullmatch(r"\*\*[^*]*\*\*", sample) is None):
			answer *= False
		elif counter == 3 and \
			(re.fullmatch(r"\*[^*]*\*[^*]*\*", sample) is None):
			answer *= False

	except EOFError:
		break

if counter != 3:  # If we have incorrect count of strings
	answer = False

print(bool(answer))
