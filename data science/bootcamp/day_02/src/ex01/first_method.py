class Research:
    """"""

    def file_reader(self, file_path: str, file: str) -> list:
        """"""

        file_content: list | None = None

        with open(file_path + file, "r") as work_file:
            file_content: list = work_file.readlines()

        return file_content


if __name__ == "__main__":
    researcher: Research = Research()

    file_content: list = researcher.file_reader("../../datasets/", "data.csv")

    print(*file_content, sep="")
