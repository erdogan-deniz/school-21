# Don't forget to start redis server - "sudo service redis-server start"
# Should start with argument case like "python producer.py 1"
import sys  # Module for invariant cases
import json  # Module for serialization json data
import redis  # Module for pub/sub process
import random  # Module for generate numbers


# Main function for task
def generate(number_of_test: str = '0'):
    # Create connection to localhost
    connection = redis.Redis(host="localhost", port=6379, db=1)

    # Check case for actions:
    if number_of_test == '0':  # Random numbers - non swap
        counter: int = 5  # Counter of messages

        # Generate json messages:
        for message in range(counter):
            from_: int = random.randint(1000000000, 9999999999)
            to_: int = random.randint(1000000000, 9999999999)
            amount_: int = random.randint(-1000000, 1000000)

            # Json structure
            json_data = {
                "metadata": {"from": from_, "to": to_},
                "amount": amount_
            }

            serialized_data = json.dumps(json_data)  # Serialization json
            connection.publish("hacked_channel", serialized_data)  # Publish json message
    elif number_of_test == '1':  # All swap case

        # Json structures:
        json_data_one = {
            "metadata": {"from": 1111111111, "to": 2222222222},
            "amount": 10000
        }

        json_data_two = {
            "metadata": {"from": 3333333333, "to": 4444444444},
            "amount": 10000
        }

        json_data_three = {
            "metadata": {"from": 2222222222, "to": 5555555555},
            "amount": 10000
        }

        # Serialization jsons:
        serialized_data_one = json.dumps(json_data_one)
        serialized_data_two = json.dumps(json_data_two)
        serialized_data_three = json.dumps(json_data_three)

        # Publish json messages:
        connection.publish("hacked_channel", serialized_data_one)
        connection.publish("hacked_channel", serialized_data_two)
        connection.publish("hacked_channel", serialized_data_three)

    elif number_of_test == '2':  # Test from task
        # Json structures:
        json_data_one = {
            "metadata": {"from": 1111111111, "to": 2222222222},
            "amount": 10000
        }

        json_data_two = {
            "metadata": {"from": 3333333333, "to": 4444444444},
            "amount": -3000
        }

        json_data_three = {
            "metadata": {"from": 2222222222, "to": 5555555555},
            "amount": 5000
        }

        # Serialization jsons:
        serialized_data_one = json.dumps(json_data_one)
        serialized_data_two = json.dumps(json_data_two)
        serialized_data_three = json.dumps(json_data_three)

        # Publish json messages:
        connection.publish("hacked_channel", serialized_data_one)
        connection.publish("hacked_channel", serialized_data_two)
        connection.publish("hacked_channel", serialized_data_three)


# Check that we have arguments:
if len(sys.argv) > 1:
    generate(sys.argv[1])
else:
    generate("0")
