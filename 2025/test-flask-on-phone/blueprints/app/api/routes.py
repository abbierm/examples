from app.api import bp
from datetime import datetime
import json


@bp.route("/next-race", methods=["GET"])
def next_race():
	""" 
	Returns JSON when the next f1 race is after current date
		i.e if there is a race TODAY it will find the next race 
		after today's race

	If its the last race or after the last race of the season will
	return json with None
	"""
	date = datetime.now()
	with open("races.json", "r") as race_file:
		race_events = json.load(race_file)
	
	filtered_races = list(filter(lambda x: datetime.strptime(x["endDate"], \
							"%Y-%m-%dT%H:%MZ") >= date, race_events))
	return filtered_races[0]
	
	