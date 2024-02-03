# Necessary modules:
import sys
import json
import aiohttp
import asyncio


# Necessary data:
found_uuid = ""  # UUID of task
correct_urls = []  # Urls for final result
final_url = "http://127.0.0.1:8888/api/v1/tasks/"  # Url for request


# Function for checking urls:
def check_url(url):
    if str(url).startswith("https://") or str(url).startswith("http://"):  # If we know that is an url
        return str(url)

    print(f"ERROR! INCORRECT URL - {url}.")

    return -1


# Function converts arguments to urls:
def define_urls():
    if len(sys.argv) > 1:  # If we have any arguments
        global correct_urls

        urls = []

        for url in sys.argv[1:]:
            if check_url(url) != -1:  # Check that we have correct url
                urls.append(url)

        if len(urls) > 0:  # If we have any urls
            if len(correct_urls) < 1:  # If we have any correct urls
                correct_urls = urls

            return urls

    print("ERROR! THE CLIENT DOESN'T HAS URLS.")

    return -1


# Function make json files:
def make_json(urls_l: list):
    if (not isinstance(urls_l, list)) or (len(urls_l) < 1):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    urls_d = {}  # JSON format of urls

    for index in range(len(urls_l)):
        urls_d[str(index)] = urls_l[index]

    return urls_d


# Main method for post request:
async def post_request(current_url: str):
    if not isinstance(current_url, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    json_data = make_json(define_urls())  # Create list of urls and convert to JSON

    async with aiohttp.ClientSession() as session:
        response = await session.post(current_url, json=json_data)  # Make post request

    return response.read()  # Check result of request (returns coroutine)


# Get new request:
async def get_request(current_url: str):
    if not isinstance(current_url, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    async with aiohttp.ClientSession() as session:
        response = await session.get(current_url)  # Make get request

    return response.text()  # Check result of request (returns coroutine)


# The final result description function:
def print_result(codes: list, sites: list):
    if (not isinstance(codes, list)) or (not isinstance(sites, list)):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1
    elif len(codes) != len(sites):  # Check that we have the same count of codes and urls
        print("ERROR! INCORRECT SIZES.")

        return -1

    print()

    for index in range(len(codes)):  # Print all pares
        print(f"URL: {sites[index]}, CODE: {codes[index]}", end='\n')

    print()


# Main function for work:
async def main():
    json_urls = make_json(define_urls())

    if json_urls == -1:
        print("ERROR! INCORRECT WORK.")
    else:
        global found_uuid, correct_urls

        first_request = await post_request(final_url)  # Make first request
        answer = json.loads(await first_request)  # Convert to JSON
        found_uuid = str(answer["Object"]["dimensions"])  # Take UUID
        result = ""

        while "ready" not in str(result):
            await asyncio.sleep(1)

            result = await (await get_request(final_url + str(found_uuid)))  # Endless

        founded_codes = json.loads(result)["Result"]

        print_result(founded_codes, correct_urls)

        correct_urls = []
        found_uuid = ""


if __name__ == "__main__":
    asyncio.run(main())
