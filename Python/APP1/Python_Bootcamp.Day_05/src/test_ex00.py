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
ex00_command_one = "curl http://127.0.0.1:8888/?species=Time%20Lord"
ex00_expected_output_one = "{\"credentials\": \"Rassilon\"}"
check_command(ex00_command_one, ex00_expected_output_one, number)

number = 2
ex00_command_two = "curl http://127.0.0.1:8888/?species=Cyberman"
ex00_expected_output_two = "{\"credentials\": \"John Lumic\"}"
check_command(ex00_command_two, ex00_expected_output_two, number)

number = 3
ex00_command_three = "curl http://127.0.0.1:8888/?species=Dalek"
ex00_expected_output_three = "{\"credentials\": \"Davros\"}"
check_command(ex00_command_three, ex00_expected_output_three, number)

number = 4
ex00_command_four = "curl http://127.0.0.1:8888/?species=Judoon"
ex00_expected_output_four = "{\"credentials\": \"Shadow Proclamation Convention 15 Enforcer\"}"
check_command(ex00_command_four, ex00_expected_output_four, number)

number = 5
ex00_command_five = "curl http://127.0.0.1:8888/?species=Human"
ex00_expected_output_five = "{\"credentials\": \"Leonardo da Vinci\"}"
check_command(ex00_command_five, ex00_expected_output_five, number)

number = 6
ex00_command_six = "curl http://127.0.0.1:8888/?species=Ood"
ex00_expected_output_six = "{\"credentials\": \"Klineman Halpen\"}"
check_command(ex00_command_six, ex00_expected_output_six, number)

number = 7
ex00_command_seven = "curl http://127.0.0.1:8888/?species=Silence"
ex00_expected_output_seven = "{\"credentials\": \"Tasha Lem\"}"
check_command(ex00_command_seven, ex00_expected_output_seven, number)

number = 8
ex00_command_eight = "curl http://127.0.0.1:8888/?species=Slitheen"
ex00_expected_output_eight = "{\"credentials\": \"Coca-Cola salesman\"}"
check_command(ex00_command_eight, ex00_expected_output_eight, number)

number = 9
ex00_command_nine = "curl http://127.0.0.1:8888/?species=Sontaran"
ex00_expected_output_nine = "{\"credentials\": \"General Staal\"}"
check_command(ex00_command_nine, ex00_expected_output_nine, number)

number = 10
ex00_command_ten = "curl http://127.0.0.1:8888/?species=Weeping%20Angel"
ex00_expected_output_ten = "{\"credentials\": \"The Division Representative\"}"
check_command(ex00_command_ten, ex00_expected_output_ten, number)

number = 11
ex00_command_eleven = "curl http://127.0.0.1:8888/?species=Zygon"
ex00_expected_output_eleven = "{\"credentials\": \"Broton\"}"
check_command(ex00_command_eleven, ex00_expected_output_eleven, number)

number = 12
ex00_command_twelve = "curl http://127.0.0.1:8888/?species=Deniz"
ex00_expected_output_twelve = "{\"credentials\": \"Unknown\"}"
check_command(ex00_command_twelve, ex00_expected_output_twelve, number)
