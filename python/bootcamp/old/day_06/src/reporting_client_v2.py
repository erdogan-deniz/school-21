# Necessary modules:

from __future__ import print_function
from typing import List
from pydantic import BaseModel, ConfigDict

import sys
import grpc
import ex00_pb2
import ex00_pb2_grpc

# Data for translation:
alignment_list = ["Ally", "Enemy"]
class_list = ["Corvette", "Frigate", "Cruiser", "Destroyer", "Carrier", "Dreadnought"]


# Functions for deserialization:
def bytes_to_alignment(alignment):
    return alignment_list[alignment]


def bytes_to_class(class_):
    return class_list[class_]


# Pydantic classes:
class Officer(BaseModel):
    first_name: str
    last_name: str
    rank: str


class Spaceship(BaseModel):
    alignment: str
    name: str
    type: str
    length: float
    crew_size: int
    armed: bool

    officers: List[Officer]


# Functions for checking ship:
def checker(spaceship):
    if ((spaceship.type == "Corvette") and (80 <= spaceship.length <= 250) and (4 <= spaceship.crew_size <= 10) and
            spaceship.armed and (spaceship.alignment == "Enemy")):
        return True
    elif ((spaceship.type == "Frigate") and (300 <= spaceship.length <= 600) and (10 <= spaceship.crew_size <= 15) and
          spaceship.armed and (spaceship.alignment == "Ally")):
        return True
    elif ((spaceship.type == "Cruiser") and (500 <= spaceship.length <= 1000) and (15 <= spaceship.crew_size <= 30) and
          spaceship.armed and (spaceship.alignment == "Enemy")):
        return True
    elif ((spaceship.type == "Destroyer") and (800 <= spaceship.length <= 1000) and (50 <= spaceship.crew_size <= 80)
          and spaceship.armed and (spaceship.alignment == "Ally")):
        return True
    elif ((spaceship.type == "Carrier") and (1000 <= spaceship.length <= 4000) and (120 <= spaceship.crew_size <= 250)
          and (not spaceship.armed) and (spaceship.alignment == "Enemy")):
        return True
    elif ((spaceship.type == "Dreadnought") and (5000 <= spaceship.length <= 20000)
          and (300 <= spaceship.crew_size <= 500) and spaceship.armed and (spaceship.alignment == "Enemy")):
        return True

    return False


# Main process function:
def run():
    if len(sys.argv) != 3:
        print("ERROR! INCORRECT COUNT OF ARGUMENTS.")
    else:
        with grpc.insecure_channel("localhost:55555") as channel:
            stub = ex00_pb2_grpc.Ex00Stub(channel)

            try:
                coordinates = ex00_pb2.Coordinate(height=int(sys.argv[1]), azimuth=int(sys.argv[2]))

                if (int(sys.argv[1]) >= -90) and (int(sys.argv[1]) <= 90) and (int(sys.argv[2]) >= 0) and (
                        int(sys.argv[2]) <= 360):
                    for ship in stub.GetShips(coordinates):
                        officers = []

                        # Add officers:
                        for i in ship.officers:
                            officers.append(Officer(first_name=i.first_name, last_name=i.last_name, rank=i.rank))

                        spaceship = Spaceship(
                            alignment=bytes_to_alignment(ship.alignment),
                            name=ship.name,
                            type=bytes_to_class(ship.type),
                            length=round(ship.length, 1),
                            crew_size=ship.size,
                            armed=ship.armed,
                            officers=officers
                        )

                        # Check spaceship for conditions:
                        if checker(spaceship):
                            # Serialization:
                            spaceship = spaceship.model_dump_json()
                            print(spaceship)

                else:
                    print("ERROR! INCORRECT COORDINATES.")

            except ValueError:
                print("ERROR! INCORRECT TYPE OF ARGUMENTS!")


if __name__ == "__main__":
    run()
