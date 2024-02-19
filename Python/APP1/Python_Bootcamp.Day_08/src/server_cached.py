# Necessary modules:
import uuid
import uvicorn
import fastapi
import aiohttp
import aioredis

# Necessary imports:
from fastapi import Request
from pydantic import BaseModel

final_codes = []  # List of sites codes
final_sites = []  # List of sites for requests
url_part = "/api/v1/tasks/"  # URL for requests
redis_url = "redis://localhost"  # URL of a redis database
task_UUID = -1  # Task id for requests after first action
redis_connection = ""  # The variable of connection redis
application = fastapi.FastAPI(title="Day_08")  # Tittle for site
timeout = aiohttp.ClientTimeout(total=3)  # Timeout for any requests
process_is_start = False  # Flag to check that async requests are started


# Define class for object returning:
class ObjectX(BaseModel):
    status: str
    dimensions: uuid.UUID


# Try to catch domain:
async def find_domain(url: str):
    if not isinstance(url, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1
    elif len(url) < 5:
        print("ERROR! INCORRECT SITE URL.")

        return -1

    return url.split('/')[2]


# Function to connect redis cash db:
async def connect_to_redis():
    global redis_url, redis_connection

    try:
        redis_connection = aioredis.from_url(redis_url)
    except Exception:
        print("ERROR! INCORRECT CONNECTION.")

        return -1


# Method for simple single request:
async def single_request(url: str):
    if not isinstance(url, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1
    elif len(url) < 5:
        print("ERROR! INCORRECT SITE URL.")

        return -1

    try:
        async with aiohttp.ClientSession() as session:
            response = await session.get(url, timeout=timeout)  # Make get request

        answer = response.status  # Check result of request (returns coroutine)
    except Exception:
        answer = 404

    return str(answer)


# Function for many requests:
async def many_requests(site_l: list):
    if not isinstance(site_l, list):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1
    elif len(site_l) < 1:
        print("ERROR! WE DON'T HAVE SITES.")

        return -1

    global task_UUID

    task_UUID = -2
    sites_codes = []

    for site in site_l:
        if (await get_value(str(site)) != -1) and (await get_value(str(site)) != "empty"):
            sites_codes.append((await get_value(str(site))).decode("utf-8"))  # Add http code from cash
        else:
            sites_codes.append(await single_request(site))
            await add_value(site, sites_codes[-1])

    return sites_codes


# Clear codes list:
def clear_codes(sites_c: list):
    if not isinstance(sites_c, list):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    s_codes = []

    for code in sites_c:
        if code != -1:
            s_codes.append(code)

    if len(s_codes) < 1:
        print("ERROR! WE DON'T HAVE ANY VALID CODE.")

        return -1

    return s_codes


# Add key and value to cash:
async def add_value(key: str, value: str):
    if (not isinstance(key, str)) or (not isinstance(value, str)):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    global redis_connection

    await redis_connection.set(key, value)


# Add key and value to cash:
async def add_int_value(key: str):
    if not isinstance(key, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    global redis_connection

    if await get_value(key + '/') != -1:
        await redis_connection.set(key + '/', str(int(await get_value(key + '/')) + 1))
    else:
        await redis_connection.set(key + '/', '1')


# Get value from cash:
async def get_value(key: str):
    if not isinstance(key, str):  # Incorrect type of argument case
        print("ERROR! INCORRECT ARGUMENT.")

        return -1

    global redis_connection

    answer = await redis_connection.get(key)

    if answer is None:
        return -1
    else:
        return answer


# Method for first request
@application.post(url_part)
async def post_request(request: Request):
    global task_UUID, redis_connection

    await connect_to_redis()

    data = await request.json()

    for site in data:  # Get all urls
        await add_int_value(await find_domain(data[site]))

    if task_UUID == -1:  # If we made the first request
        for site in data:  # Get all urls
            final_sites.append(data[site])

        task_UUID = uuid.uuid4()  # Generate current new UUID

        return {"Code Status": "201 Created", "Object": ObjectX(status="running", dimensions=task_UUID)}

    else:
        return "Request already done!"


@application.get("/api/v1/tasks/{current_uuid}")
async def check_process(current_uuid: str):
    global task_UUID, process_is_start, final_codes, final_sites

    if task_UUID == -1:
        return "ERROR! YOU DON'T SEND URLS."
    elif task_UUID == -2:
        global process_is_start

        task_UUID = -1
        process_is_start = False
        temporary_codes = final_codes
        final_sites = []
        final_codes = []

        return {"Status:": "ready", "Result": temporary_codes}
    else:
        if not process_is_start:
            process_is_start = True
            final_codes = clear_codes(await many_requests(final_sites))
            task_UUID = -2

            return final_codes  # HERE IS an ERROR


if __name__ == "__main__":
    uvicorn.run("server:application", host="127.0.0.1", port=8888)
