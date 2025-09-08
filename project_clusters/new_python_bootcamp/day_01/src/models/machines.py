"""
`Machines` model module.

Examples of usage:
    >>> machines: Machines = Machines()

    >>> machines.fill_machines_data()
    >>> 5 48
    >>> 2023 100 14
    >>> 2020 18 347
    >>> 2023 1000000 34
    >>> 2023 1000 34
    >>> 2022 10 34
    >>> print(machines.find_two_suitable_machines_cost(), )
"""


class Machines:
    """
    Machines class of data and operations.

    :Attributes:
        cert_time (int | None): A certain running time of two machines.
                                Default: None.
        num_of_machines (int | None): A number of machines.
                                      Default: None.
        costs (list): A machines costs.
                      Default: [].
        runn_times (list): A machines running times.
                           Default: [].
        manufact_years (list): A machines manufacture years.
                               Default: [].
    """

    def __init__(
        self,
        cert_time: int | None = None,
        num_of_machines: int | None = None,
        costs: list[int] | None = None,
        runn_times: list[int] | None = None,
        manufact_years: list[int] | None = None
    ) -> None:
        """
        Initializes the `Machines` class representative.

        :Parameters:
            cert_time (int | None): A certain running time of two machines.
                                    Default: None.
            num_of_machines (int | None): A number of machines.
                                          Default: None.
            costs (list[int] | None): A machines costs.
                                      Default: None.
            runn_times (list[int] | None): A machines running times.
                                           Default: None.
            manufact_years (list[int] | None): A machines manufacture years.
                                               Default: None.
        """

        self.cert_time: int | None = cert_time
        self.num_of_machines: int | None = num_of_machines
        self.costs: list = costs or []
        self.runn_times: list = runn_times or []
        self.manufact_years: list = manufact_years or []

    def fill_machines_data(self) -> None:
        """
        Fill machines data from the user.

        :Exceptions:
            IndexError: When iterable object do not contain expected element.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.num_of_machines, self.cert_time = map(int, input().split(), )

            for _ in range(self.num_of_machines, ):
                machine_data: list = list(map(int, input().split(), ), )

                self.costs.append(machine_data[1], )
                self.runn_times.append(machine_data[2], )
                self.manufact_years.append(machine_data[0], )

        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
            )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def find_two_suitable_machines_cost(self) -> float | None:
        """
        Returns cost of two suitable machines.

        :Returns:
            float: A cost of two machines.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When iterable object do not contain expected element.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            total_cost: int = 0

            for idx in range(self.num_of_machines, ):
                for jdx in range(self.num_of_machines, ):
                    if (
                        (
                            (self.runn_times[idx] + self.runn_times[jdx]) ==\
                            self.cert_time
                        ) and
                        (idx != jdx) and
                        (self.manufact_years[idx] == self.manufact_years[jdx])
                    ):
                        if (
                            (total_cost == 0) or
                            ((self.costs[idx] + self.costs[jdx]) < total_cost)
                        ):
                            total_cost = self.costs[idx] + self.costs[jdx]

            return total_cost
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
            )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )
