# Necessary functions and classes:
from __future__ import print_function

# Necessary modules:
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
                    output(stub.GetShips(coordinates))

                else:
                    print("ERROR! INCORRECT COORDINATES.")

            except ValueError:
                print("ERROR! INCORRECT TYPE OF ARGUMENTS!")


# Output spaceship:
def output(spaceships):
    if spaceships is not None:
        for ship in spaceships:
            print('{\n' + str(ship))  # JSON like serialized data


if __name__ == "__main__":
    run()
