class Must_read:
    """"""

    file_content: list | None = None

    with open("../../datasets/data.csv", "r") as work_file:
        file_content: list = work_file.readlines()

    print(*file_content, sep="")


if __name__ == "__main__":
    reader: Must_read = Must_read()
