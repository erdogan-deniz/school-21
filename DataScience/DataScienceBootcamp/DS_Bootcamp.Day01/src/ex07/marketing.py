import sys


def get_unnoticed_person_emails_list(
    clients_list: list, participants_list: list, recipients_list: list
) -> list:
    """"""

    tmp_set: set = set(clients_list) | set(participants_list)
    unnoticed_person_emails_list: list = list(tmp_set - set(recipients_list))

    return unnoticed_person_emails_list


def get_not_client_emails_list(
    clients_list: list, participants_list: list, recipients_list: list
) -> list:
    """"""

    tmp_set: set = set(participants_list) | set(recipients_list)
    not_client_emails_list: list = list(tmp_set - set(clients_list))

    return not_client_emails_list


def get_not_visited_person_emails_list(
    clients_list: list, participants_list: list, recipients_list: list
) -> list:
    """"""

    tmp_set: set = set(clients_list) | set(recipients_list)
    not_visited_person_emails_list: list = list(
        tmp_set - set(participants_list)
    )

    return not_visited_person_emails_list


def get_necessary_emails_list() -> list | None:
    """"""

    clients: list = [
        "john@snow.is",
        "ted@mosby.com",
        "elon@paypal.com",
        "andrew@gmail.com",
        "jessica@gmail.com",
        "mark@facebook.com",
        "jessica@gmail.com",
        "bill\\_gates@live.com",
    ]

    participants: list = [
        "mr@robot.gov",
        "vasily@mail.ru",
        "pinkman@yo.org",
        "pinkman@yo.org",
        "elon@paypal.com",
        "eleven@yahoo.com",
        "jessica@gmail.com",
        "walter@heisenberg.com",
    ]

    recipients: list = [
        "john@snow.is",
        "andrew@gmail.com",
        "jessica@gmail.com",
    ]

    script_args: list = sys.argv

    if len(script_args) == 2:
        if script_args[1] == "call_center":
            return get_unnoticed_person_emails_list(
                clients, participants, recipients
            )
        elif script_args[1] == "potential_clients":
            return get_not_client_emails_list(
                clients, participants, recipients
            )
        elif script_args[1] == "loyalty_program":
            return get_not_visited_person_emails_list(
                clients, participants, recipients
            )
        else:
            raise f"ERROR! Incorrect the argument name {script_args[1]}."


if __name__ == "__main__":
    print(get_necessary_emails_list())
