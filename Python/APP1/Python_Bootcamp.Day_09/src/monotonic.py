# Import necessary modules:
import ctypes
import subprocess


# Install create so for script:
def create_library_so():
    process = subprocess.Popen("gcc -fPIC -shared -o monotonic.so monotonic.c".split())
    process.communicate()


# Function to get currecnt pwd:
def get_pwd():
    result = subprocess.run("pwd", capture_output=True, text=True, shell=True)

    return str(result.stdout)


# Task function:
def get_time(pwd: str):
    if not isinstance(pwd, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    library = ctypes.CDLL(pwd.strip() + "/monotonic.so", mode=ctypes.RTLD_GLOBAL)
    library.monotonic()


# If we run the script:
if __name__ == "__main__":
    create_library_so()
    get_time(get_pwd())
