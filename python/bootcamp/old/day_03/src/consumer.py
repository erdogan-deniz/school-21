import redis  # Module for pub/sub
import json  # For deserialization
import time  # Module for output freezing
import sys  # Module for reading arguments
import logging.handlers  # For putting in the file
import subprocess  # Module for subprocess commands

connection = redis.Redis(host="localhost", port=6379, db=1)  # The same one, which we create in producer
follower = connection.pubsub()  # Follow to channel

follower.subscribe("hacked_channel")  # Subscribe on channel

# Default from another script:
if __name__ != "__main__":
    while True:
        message = follower.get_message()  # Get message

        for index in range(len(sys.argv)):  # Convert args to str and delete symbol ','
            sys.argv[index] = str(sys.argv[index]).rstrip(',')

        if message:  # If we get a message
            try:
                json_data = json.loads(message["data"])  # Convert data to dict

                if (str(json_data["metadata"]["to"]) in sys.argv) and (json_data["amount"] >= 0):  # Check conditions

                    # Swap users:
                    json_data["metadata"]["from"], json_data["metadata"]["to"] = json_data["metadata"]["to"], \
                        json_data["metadata"]["from"]
                    json_data = json.dumps(json_data)  # Serialization
                    message["data"] = json_data

            except TypeError:  # If we got the first string of connection
                continue

            logging.info(message)  # Print message
            time.sleep(0.1)  # Small-time freeze
else:  # Testing
    print("What we get:")
    logging.basicConfig(level=logging.DEBUG)  # Set status

    file_handler = logging.handlers.RotatingFileHandler("logfile.txt")  # Create file

    logging.getLogger().addHandler(file_handler)  # Connect output to file

    # Lines for compare:
    test_line_one = ("{'type': 'message', 'pattern': None, 'channel': b'hacked_channel', 'data': '{\"metadata\": {"
                     "\"from\": 2222222222, \"to\": 1111111111}, \"amount\": 10000}'}")
    test_line_two = ("{'type': 'message', 'pattern': None, 'channel': b'hacked_channel', 'data': b'{\"metadata\": {"
                     "\"from\": 3333333333, \"to\": 4444444444}, \"amount\": -3000}'}")
    test_line_three = ("{'type': 'message', 'pattern': None, 'channel': b'hacked_channel', 'data': b'{\"metadata\": {"
                       "\"from\": 2222222222, \"to\": 5555555555}, \"amount\": 5000}'}")
    counter = 0  # Index of a message

    while True:
        message = follower.get_message()  # Get message

        for index in range(len(sys.argv)):  # Convert args to str and delete symbol ','
            sys.argv[index] = str(sys.argv[index]).rstrip(',')

        if message:  # If we get a message
            counter += 1  # Check the next message

            try:
                json_data = json.loads(message["data"])  # Convert data to dict

                if (str(json_data["metadata"]["to"]) in sys.argv) and (json_data["amount"] >= 0):  # Check conditions
                    # Swap users:
                    json_data["metadata"]["from"], json_data["metadata"]["to"] = json_data["metadata"]["to"], \
                        json_data["metadata"]["from"]
                    json_data = json.dumps(json_data)  # Serialization
                    message["data"] = json_data

            except TypeError:  # If we got the first string of connection
                continue

            logging.debug(message)  # Add lines

            if counter == 4:  # Break endless loop for next checking
                counter = 0
                break

    with open("logfile.txt", 'r') as file:  # Check result
        lines = file.readlines()  # Read file with a result

        for line in lines:
            if (counter == 0) and (line.rstrip() == test_line_one):
                logging.info("Test № 1 - was passed!")
            elif (counter == 0) and (line.rstrip() != test_line_one):
                logging.info("Test № 1 - wasn't passed!")

            if (counter == 1) and (line.rstrip() == test_line_two):
                logging.info("Test № 2 - was passed!")
            elif (counter == 1) and (line.rstrip() != test_line_two):
                logging.info("Test № 2 - wasn't passed!")

            if (counter == 2) and (line.rstrip() == test_line_three):
                logging.info("Test № 3 - was passed!")
            elif (counter == 2) and (line.rstrip() != test_line_three):
                logging.info("Test № 3 - wasn't passed!")

            counter += 1

    subprocess.run("rm -rf logfile.txt", capture_output=True, text=True, shell=True)  # Delete txt.file
