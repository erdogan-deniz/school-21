import os
import sys
import subprocess


def installing_libraries() -> None:
    """"""

    correct_venv_name: str = "charisel"

    venv_variable: str = "VIRTUAL_ENV"
    venv_path: str | None = os.getenv(venv_variable)

    packages_file_path: str = "../"
    packages_file: str = "requirements.txt"

    required_packages: list = [
        "six\n",
        "zipp\n",
        "pytest\n",
        "wcwidth\n",
        "soupsieve\n",
        "termgraph\n",
        "beautifulsoup4\n",
    ]

    try:
        venv_name: str = os.path.basename(venv_path)

        if venv_name == correct_venv_name:
            with open(packages_file_path + packages_file, "w+") as work_file:
                work_file.writelines(required_packages)

            subprocess.check_call(
                [
                    sys.executable,
                    "-m",
                    "pip",
                    "install",
                    "-r",
                    packages_file_path + packages_file,
                ]
            )

            cmd_result: object = subprocess.run(
                ["cat", packages_file_path + packages_file],
                capture_output=True,
                text=True,
                check=True,
            )

            print(
                "\n\nThe installed packages are:\n", cmd_result.stdout, sep=""
            )
        else:
            raise Exception("You are in the incorrect venv.")
    except Exception as err:
        print(f"Your are not in the venv. {err}")


if __name__ == "__main__":
    installing_libraries()
