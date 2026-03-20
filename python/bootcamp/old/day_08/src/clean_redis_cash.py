# For start linux command:
import time as t
import subprocess


# For taking time from user:
def input_time():
    while True:  # Untill user input integer value
        try:
            timeout = int(input("Input timeout value: \n"))

            break
        except ValueError:
            print("ERROR! INCORRECT INPUT.", end='\n')

    t.sleep(abs(timeout))

    command = ["redis-cli", "flushall"]
    process = subprocess.Popen(command)
    output = process.communicate()


if __name__ == "__main__":
    input_time()
