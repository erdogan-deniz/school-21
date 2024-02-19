import subprocess


# Function for checking output of commands:
def check_command(command, expected_output, test_number):
    result = subprocess.run(command, capture_output=True, text=True, shell=True)

    print("************Тест № ", test_number, ':************', sep='')
    print("Ожидаемый вывод:\n", expected_output, sep='')
    print("Наш вывод:\n", result.stdout, sep='')

    if expected_output in result.stdout:  # Check are they equal
        print("*********Тест - пройден!*********\n")
    else:
        print("*********Тест - не пройден!*********\n")


if __name__ == "__main__":
    # Test cases:
    number = 1
    ex00_command_one = "python reporting_client.py"
    ex00_expected_output_one = "ERROR! INCORRECT COUNT OF ARGUMENTS."

    check_command(ex00_command_one, ex00_expected_output_one, number)

    number = 2
    ex00_command_two = "python reporting_client.py 1"

    check_command(ex00_command_two, ex00_expected_output_one, number)

    number = 3
    ex00_command_three = "python reporting_client.py 1 zxc"
    ex00_expected_output_three = "ERROR! INCORRECT TYPE OF ARGUMENTS!"

    check_command(ex00_command_three, ex00_expected_output_three, number)

    number = 4
    ex00_command_four = "python reporting_client.py zxc 1"

    check_command(ex00_command_four, ex00_expected_output_three, number)

    number = 5
    ex00_command_five = "python reporting_client.py -666 10"
    ex00_expected_output_five = "ERROR! INCORRECT COORDINATES."

    check_command(ex00_command_five, ex00_expected_output_five, number)

    number = 6
    ex00_command_six = "python reporting_client.py 10 666"

    check_command(ex00_command_six, ex00_expected_output_five, number)

    number = 7
    ex00_command_seven = "python reporting_client.py -666 666"

    check_command(ex00_command_seven, ex00_expected_output_five, number)

    for i in range(25):
        ex01_command_one = "python reporting_client_v2.py 45 45"

        subprocess.run(ex01_command_one, text=True, shell=True)

    for i in range(25):
        ex02_command_one = "python reporting_client_v3.py 45 45"

        subprocess.run(ex02_command_one, text=True, shell=True)

    ex02_command_two = "python reporting_client_v3.py scan 5 5"

    subprocess.run(ex02_command_two, text=True, shell=True)
