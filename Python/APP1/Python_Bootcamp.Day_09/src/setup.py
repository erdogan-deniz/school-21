# Module for installing:
import sys
import subprocess


# Function to run command:
def make_process(command: str):
    if not isinstance(command, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    process = subprocess.Popen(command.split())
    process.communicate()


# Install module:
def install():
    make_process("sudo apt-get install python3-dev")
    make_process("sudo apt install plocate")

    location = subprocess.run("plocate Python.h", capture_output=True, text=True, shell=True).stdout
    final_location = location.split()[-1].rsplit('/', maxsplit=1)[0]  # Find final directory where "Python.h" is

    make_process(f"gcc -shared -o calculator.so calculator.c -I{final_location}")


# Main task for installing:
if __name__ == "__main__":
    if (len(sys.argv) == 2) and str(sys.argv[1]) == "install":  # Case to install module
        install()
    elif (len(sys.argv) == 2) and str(sys.argv[1]) == "clean":  # Case to delete module
        make_process("rm -rf build")
        make_process("rm -rf multiply.c")
        make_process("rm -rf monotonic.so")
        make_process("rm -rf calculator.so")
        make_process("rm -rf multiply.cpython-310-x86_64-linux-gnu.so")
    elif (len(sys.argv) == 2) and str(sys.argv[1]) == "cython":  # Case to delete module
        make_process("python ex_module.py build_ext --inplace")
    else:  # Any other cases
        print("ERROR! CAN'T INSTALL MODULE.")
