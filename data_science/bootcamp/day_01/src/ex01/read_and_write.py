def read_csv_file(
    file_path: str,
    file: str,
    file_access_mode: str,
    res_file: str,
    res_file_access_mode: str,
) -> None:
    """"""

    file_content: list = None

    with open(file_path + file, file_access_mode) as work_file:
        file_content = work_file.readlines()

    file_content[0] = file_content[0].replace(",", "\t")

    for file_row_idx in range(1, len(file_content)):
        if ('",') in file_content[file_row_idx]:
            file_content[file_row_idx] = file_content[file_row_idx].replace(
                '",', '"\t'
            )
        if (',"') in file_content[file_row_idx]:
            file_content[file_row_idx] = file_content[file_row_idx].replace(
                ',"', '\t"'
            )
        if ("true,") in file_content[file_row_idx]:
            file_content[file_row_idx] = file_content[file_row_idx].replace(
                "true,", "true\t"
            )
        if ("false,") in file_content[file_row_idx]:
            file_content[file_row_idx] = file_content[file_row_idx].replace(
                "false,", "false\t"
            )

    with open(res_file, res_file_access_mode) as work_file:
        work_file.writelines(file_content)


if __name__ == "__main__":
    read_csv_file("../../datasets/", "ds.csv", "r+", "ds.tsv", "w+")
