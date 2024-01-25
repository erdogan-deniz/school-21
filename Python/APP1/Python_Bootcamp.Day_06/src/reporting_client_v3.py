from __future__ import print_function
from sqlalchemy.orm import Session

# Necessary modules:
import sys
import grpc
import models
import ex00_pb2
import arguments
import sqlalchemy
import ex00_pb2_grpc
import reporting_client_v3

# Data for translation:
alignment_list = ["Ally", "Enemy"]
class_list = ["Corvette", "Frigate", "Cruiser", "Destroyer", "Carrier", "Dreadnought"]


# Add traitor:
def add_traitor(engine, first_name, last_name, rank):
    with Session(engine) as session:
        new_traitor = models.Traitors(
            first_name=first_name,
            last_name=last_name,
            rank=rank
        )

        session.add(new_traitor)
        session.commit()
        session.close()


# Check that traitor is exists:
def is_exist_traitor(engine, first_name, last_name, rank):
    session = Session(engine)

    for traitor in session.query(models.Traitors):
        if (traitor.first_name == first_name) and (traitor.last_name == last_name) and (traitor.rank == rank):
            session.close()
            return True

    session.close()

    return False


# Function for finding traitors:
def find_traitors(engine):
    session = Session(engine)

    for officer in session.query(models.Officer):
        for second_officer in session.query(models.Officer):
            if ((officer.last_name == second_officer.last_name) and
                    (officer.first_name == second_officer.first_name) and (officer.rank == second_officer.rank) and
                    (officer.status != second_officer.status) and not
                    is_exist_traitor(engine, second_officer.first_name, second_officer.last_name,
                                     second_officer.rank)):
                add_traitor(engine, officer.first_name, officer.last_name, officer.rank)
                session.close()


# Function for connection:
def create_connection(USER_NAME: str, USER_PASSWORD: str, DATABASE_NAME: str):
    engine = sqlalchemy.create_engine(f"postgresql+psycopg2://" + USER_NAME + ":" + USER_PASSWORD + "@localhost/" +
                                      DATABASE_NAME)
    engine.connect()

    return engine


# Functions working with tables:
def create_tables(engine):
    models.Base.metadata.create_all(engine)


def delete_tables(engine):
    models.Base.metadata.drop_all(engine)


# Function for finding and returning list of officers of spaceship:
def find_officers(engine, spaceship_index):
    session = Session(engine)

    answer = '['

    for officer in session.query(models.Officer):
        if officer.spaceship_id == spaceship_index:
            answer = answer + '{ first_name: ' + str(officer.first_name) + ', '
            answer = answer + 'last_name: ' + str(officer.last_name) + ', '
            answer = answer + 'rank: ' + str(officer.rank) + ' }, '

    session.close()

    if answer == "{":
        return ""
    else:
        return answer[:-2] + ']'


# Functions for add new spaceship:
def add_spaceship(engine, spaceship):
    with Session(engine) as session:
        new_spaceship = models.Spaceship(
            alignment=reporting_client_v3.bytes_to_alignment(spaceship.alignment),
            name=spaceship.name,
            type=reporting_client_v3.bytes_to_class(spaceship.type),
            length=round(spaceship.length, 1),
            crew_size=spaceship.size,
            armed=spaceship.armed,
        )

        session.add(new_spaceship)
        session.commit()
        session.close()


# Functions for add new officer:
def add_officer(engine, officer, spaceship_id, status):
    with Session(engine) as session:
        new_officer = models.Officer(
            first_name=officer.first_name,
            last_name=officer.last_name,
            rank=officer.rank,
            spaceship_id=spaceship_id,
            status=status
        )

        session.add(new_officer)
        session.commit()
        session.close()


# Function to find status of last spaceship:
def find_last_status(engine):
    status = []
    session = Session(engine)

    for spaceship in session.query(models.Spaceship):
        status.append(spaceship.alignment)

    session.close()

    if len(status) > 0:
        return status[-1]

    return "Ally"


# Function to find max id of spaceship:
def find_last_index(engine):
    index = []
    session = Session(engine)

    for spaceship in session.query(models.Spaceship):
        index.append(spaceship.id)

    session.close()

    if len(index) > 0:
        return index[-1]

    return -1


# Function for argument list_traitors:
def print_traitors(engine):
    session = Session(engine)

    for traitor in session.query(models.Traitors):
        print("{ first_name: " + traitor.first_name +
              ", last_name: " + traitor.last_name +
              ", rank: " + traitor.rank +
              " }"
              )

    session.close()


# Print all spaceships:
def print_spaceships(engine):
    session = Session(engine)

    for spaceship in session.query(models.Spaceship):
        if checker(spaceship):
            print("{ alignment: " + spaceship.alignment +
                  ", name: " + spaceship.name +
                  ", class: " + spaceship.type +
                  ", length: " + str(spaceship.length) +
                  ", crew_size: " + str(spaceship.crew_size) +
                  ", armed: " + spaceship.armed +
                  ", officers: " + find_officers(engine, spaceship.id) +
                  " }"
                  )

    session.close()


# Functions for deserialization:
def bytes_to_alignment(alignment):
    return alignment_list[alignment]


def bytes_to_class(class_):
    return class_list[class_]


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
    if (len(sys.argv) == 2) and (sys.argv[-1] == "list_traitors"):  # list traitors case
        engine = create_connection(arguments.USER_NAME, arguments.USER_PASSWORD, arguments.DATABASE_NAME)

        create_tables(engine)
        print_traitors(engine)
    elif (len(sys.argv) == 4) and (sys.argv[1] == "scan"):  # scan case
        try:
            if (int(sys.argv[2]) >= -90) and (int(sys.argv[2]) <= 90) and (int(sys.argv[3]) >= 0) and (
                    int(sys.argv[3]) <= 360):
                engine = create_connection(arguments.USER_NAME, arguments.USER_PASSWORD, arguments.DATABASE_NAME)

                create_tables(engine)
                find_traitors(engine)
            else:
                print("ERROR! INCORRECT ARGUMENTS VALUE.")

        except ValueError:
            print("ERROR! INCORRECT TYPES OF ARGUMENTS.")

    elif len(sys.argv) != 3:
        print("ERROR! INCORRECT COUNT OF ARGUMENTS.")
    else:
        with grpc.insecure_channel("localhost:55555") as channel:
            stub = ex00_pb2_grpc.Ex00Stub(channel)

            try:
                coordinates = ex00_pb2.Coordinate(height=int(sys.argv[1]), azimuth=int(sys.argv[2]))

                if (int(sys.argv[1]) >= -90) and (int(sys.argv[1]) <= 90) and (int(sys.argv[2]) >= 0) and (
                        int(sys.argv[2]) <= 360):

                    try:
                        engine = create_connection(arguments.USER_NAME, arguments.USER_PASSWORD,
                                                   arguments.DATABASE_NAME)
                        # delete_tables(engine)  # If you want to clear database
                        create_tables(engine)

                    except Exception:
                        exit()

                    for ship in stub.GetShips(coordinates):  # Check all ships
                        add_spaceship(engine, ship)

                        # Add officers:
                        for officer in ship.officers:
                            index = find_last_index(engine)
                            status = find_last_status(engine)
                            add_officer(engine, officer, index, status)

                    print_spaceships(engine)

                else:
                    print("ERROR! INCORRECT COORDINATES.")

            except ValueError:
                print("ERROR! INCORRECT TYPE OF ARGUMENTS!")


if __name__ == "__main__":
    run()
