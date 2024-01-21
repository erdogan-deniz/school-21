#! /usr/bin/env python

import json  # For serilization in json
from urllib.parse import parse_qs  # Function for parsing get requests
from html import escape  # Function for checking url on scripts
from wsgiref.simple_server import make_server  # Function for creating server

# Our species:
species = {
    "Cyberman": "John Lumic",
    "Dalek": "Davros",
    "Judoon": "Shadow Proclamation Convention 15 Enforcer",
    "Human": "Leonardo da Vinci",
    "Ood": "Klineman Halpen",
    "Silence": "Tasha Lem",
    "Slitheen": "Coca-Cola salesman",
    "Sontaran": "General Staal",
    "Time Lord": "Rassilon",
    "Weeping Angel": "The Division Representative",
    "Zygon": "Broton"
}


# The application interface is a callable object:
def application(environ, start_response):
    # Settings of server like GCI:
    response_headers = [("Content-Type", "application/json")]

    # Returns a dictionary in which the values are lists:
    parsed_string = parse_qs(environ["QUERY_STRING"])
    credentials = parsed_string.get("species", [''])[0]  # Parse strings
    credentials = escape(credentials)  # Delete scripts

    # Check species:
    if credentials in species:
        default_status = "202 "
        response_body = {"credentials": species[credentials]}
    else:
        default_status = "404 "
        response_body = {"credentials": "Unknown"}

    # Send them to the server using the supplied function:
    start_response(default_status, response_headers)

    return [json.dumps(response_body).encode("utf-8")]  # Return the json


# Instantiate the server:
http_server = make_server('localhost', 8888, application)

# Start endless server:
http_server.serve_forever()
