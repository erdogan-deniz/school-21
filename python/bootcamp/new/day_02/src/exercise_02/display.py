"""Summary table renderer."""


def print_summary(res: list[tuple[str, str]]) -> None:
    """
    Print a formatted ASCII table of download results to *stdout*.

    :Parameters:
        res (list[tuple[str, str]]): Sequence of ``(url, status)`` tuples in the
            order the URLs were entered by the user.
    """

    if not res:
        print("No downloads attempted.")

        return

    link_w: int = max(len("Link"), max(map(lambda r: len(r[0]), res)))
    status_w: int = max(len("Status"), max(map(lambda r: len(r[1]), res)))
    sep: str = f"+{'-' * (link_w + 2)}+{'-' * (status_w + 2)}+"

    def fmt_row(r: tuple[str, str]) -> str:
        """
        Format a single row of the table.

        :Parameters:
            r (tuple[str, str]): A tuple containing the URL and its download
                status.
        """

        return f"| {r[0]:<{link_w}} | {r[1]:<{status_w}} |"

    print(sep)
    print(f"| {'Link':<{link_w}} | {'Status':<{status_w}} |")
    print(sep)
    print("\n".join(map(fmt_row, res)))
    print(sep)
