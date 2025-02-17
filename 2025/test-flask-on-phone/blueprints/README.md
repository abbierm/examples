# Example flask app with blueprints

Entire example flask app from post on [sevenBplus.dev](https://www.sevenbplus.dev/blog/test-flask-websites-on-your-phone) that shows how to set up a development server that you can view and test on other devices. The goal of this repo is to give a  "non-foobar" flask example that contains blueprints. 

There are only 2 routes (and 2 blueprints). The main bp contains a homepage with basic simple UI elements ("/"). The other bp is for the api with 1 endpoint ("/api/next-race") that returns a JSON string with information about the next formula 1 race. 

## Quickstart (running the development server on your own device)

1. Install requirements from requirements.txt

    pip install requirements.txt

2. Run test server (to test UI routes on phone)

    python flaskapp.py
