# Module for testing:
import subprocess


# Function for checking output of commands:
def check_command(command, expected_output, number):
	result = subprocess.run(command, capture_output=True, text=True, shell=True)

	print("************Тест № ", number, ':************', sep='')
	print("Ожидаемый вывод:\n", expected_output, sep='')
	print("Наш вывод:\n", result.stdout, sep='')

	if expected_output in result.stdout:  # Check are they equal
		print(f"*********Тест - пройден!*********\n")
	else:
		print("*********Тест - не пройден!*********\n")


# Tests:
# Task - ex00:
number = 1
ex00_command_one = "cat other/ex00_data.txt | python ex00.py"
ex00_expected_output_one = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
0000071f49cffeaea4184be3d507086v
"""
check_command(ex00_command_one, ex00_expected_output_one, number)

number = 2
ex00_command_two = "cat other/ex00_data.txt | python ex00.py -2"  # Any number less then 1
ex00_expected_output_two = """Incorrect input! Value must be bigger than 0
"""
check_command(ex00_command_two, ex00_expected_output_two, number)

number = 3
ex00_command_three = "cat other/ex00_data.txt | python ex00.py 10"  # Any number more 0
check_command(ex00_command_three, ex00_expected_output_one, number)

number = 4
ex00_command_four = "cat other/ex00_data.txt | python ex00.py 1"
ex00_expected_output_four = "00000254b208c0f43409d8dc00439896\n"
check_command(ex00_command_four, ex00_expected_output_four, number)

number = 5
ex00_command_five = "cat other/ex00_data.txt | python ex00.py 5"
ex00_expected_output_five = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
"""
check_command(ex00_command_five, ex00_expected_output_five, number)

# Task - ex01:
number = 1
ex01_command_one = "python ex01.py 'Britain is Great because everyone necessitates'"
ex01_expected_output_one = "bigben"
check_command(ex01_command_one, ex01_expected_output_one, number)

number = 2
ex01_command_two = "python ex01.py"
ex01_expected_output_two = ""
check_command(ex01_command_two, ex01_expected_output_two, number)

number = 3
ex01_command_three = "python ex01.py 321"
ex01_expected_output_three = "3"
check_command(ex01_command_three, ex01_expected_output_three, number)

number = 4
ex01_command_four = "python ex01.py 'The only way everyone reaches Brenda rapidly is delivering groceries explicitly'"
ex01_expected_output_four = "towerbridge"
check_command(ex01_command_four, ex01_expected_output_four, number)

number = 5
ex01_command_five = "python ex01.py 'Have you delivered eggplant pizza at restored keep?'"
ex01_expected_output_five = "hydepark"
check_command(ex01_command_five, ex01_expected_output_five, number)

# Task ex02:
number = 1
ex02_command_one = "cat other/m.txt | python mfinder.py"
ex02_expected_output_one = "True\n"
check_command(ex02_command_one, ex02_expected_output_one, number)

number = 2
ex02_command_two = "cat other/m2.txt | python mfinder.py"
ex02_expected_output_two = "False\n"
check_command(ex02_command_two, ex02_expected_output_two, number)

number = 3
ex02_command_three = "cat other/m3.txt | python mfinder.py"
ex02_expected_output_three = "False\n"
check_command(ex02_command_three, ex02_expected_output_three, number)

number = 4
ex02_command_four = "cat other/m4.txt | python mfinder.py"
ex02_expected_output_four = "False\n"
check_command(ex02_command_four, ex02_expected_output_four, number)

number = 5
ex02_command_five = "cat other/m5.txt | python mfinder.py"
ex02_expected_output_five = "False\n"
check_command(ex02_command_five, ex02_expected_output_five, number)
check_command(ex00_command_five, ex00_expected_output_five, number)

# Task - ex01:
number = 1
ex01_command_one = "python ex01.py 'Britain is Great because everyone necessitates'"
ex01_expected_output_one = "bigben"
check_command(ex01_command_one, ex01_expected_output_one, number)

number = 2
ex01_command_two = "python ex01.py"
ex01_expected_output_two = ""
check_command(ex01_command_two, ex01_expected_output_two, number)

number = 3
ex01_command_three = "python ex01.py 321"
ex01_expected_output_three = "3"
check_command(ex01_command_three, ex01_expected_output_three, number)

number = 4
ex01_command_four = "python ex01.py 'The only way everyone reaches Brenda rapidly is delivering groceries explicitly'"
ex01_expected_output_four = "towerbridge"
check_command(ex01_command_four, ex01_expected_output_four, number)

number = 5
ex01_command_five = "python ex01.py 'Have you delivered eggplant pizza at restored keep?'"
ex01_expected_output_five = "hydepark"
check_command(ex01_command_five, ex01_expected_output_five, number)

# Task ex02:
number = 1
ex02_command_one = "cat other/m.txt | python mfinder.py"
ex02_expected_output_one = "True\n"
check_command(ex02_command_one, ex02_expected_output_one, number)

number = 2
ex02_command_two = "cat other/m2.txt | python mfinder.py"
ex02_expected_output_two = "False\n"
check_command(ex02_command_two, ex02_expected_output_two, number)

number = 3
ex02_command_three = "cat other/m3.txt | python mfinder.py"
ex02_expected_output_three = "False\n"
check_command(ex02_command_three, ex02_expected_output_three, number)
