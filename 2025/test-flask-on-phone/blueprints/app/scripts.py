import httpx
import json
from datetime import datetime


"""
This function only needs to be run once per day since the f1 schedule 
usually doesn't change after it's been created. This will run the ESPN 
api, retrieve the schedule for the current year, and save the info 
needed for the api/next-race route to JSON file inside the directory. 
"""
def make_api_request():
    # Get current year
    year = datetime.today().year
    api = f"https://www.espn.com/f1/schedule/_/year/{year}?_xhr=pageContent"
    r_json_calendar = httpx.get(api).json()["calendar"]
    # Save to file
    with open("races.json", "w") as f:
        json.dump(r_json_calendar, f, sort_keys=True, indent=4)


    