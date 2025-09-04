from pathlib import Path
import os
from dotenv import load_dotenv



BASEDIR = Path(__file__).parent.absolute()
load_dotenv(BASEDIR.joinpath('.env'))

"""
    this won't work since I have a 'fake' URL in my .env file
    BUT if you want to use a PostgreSQL db this is the format
    it would be in 
    """ 

# SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL', '').replace('postgres://', 'postgresql+psycopg://')]


SQLALCHEMY_DATABASE_URI = 'sqlite://'
COMPLETE_DIR = Path(BASEDIR, "content", "posts", "complete")
INPROGRESS_DIR = Path(BASEDIR, "content", "posts", "in-progress")
