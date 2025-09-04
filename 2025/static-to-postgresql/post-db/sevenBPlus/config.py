from pathlib import Path
import os
from dotenv import load_dotenv

BASEDIR = Path(__file__).parent.absolute()
load_dotenv(BASEDIR.joinpath('.env'))


def raw_html_renderer(text: str) -> str:
    return text


class Config:
    TESTING = False
    FLATPAGES_AUTO_RELOAD = True
    FLATPAGES_EXTENSION = ".html"
    FLATPAGES_ROOT = "../../sevenBPosts/content"

    """
        flask-flatpages prefers markdown so I had to  
        create a function to "render" the html back
        into HTML? Basically its just a function that 
        pretends it's doing something so flatpages 
        doesn't do it and mess up my formatting
    """
    FLATPAGES_HTML_RENDERER = raw_html_renderer
    FLATPAGES_RENDERER = raw_html_renderer

    SQLALCHEMY_TRACK_MODIFICATIONS =  False

    """
        this creates a temporary database so you could
        run this application without a valid postggresql
        URI just to see how it works
    """
    SQLALCHEMY_DATABASE_URI = 'sqlite://'
    

    """
    this won't work since I have a 'fake' URL in my .env file
    BUT if you want to use a PostgreSQL db this is the format
    it would be in 
    """ 
    # SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL', '').replace('postgres://', 'postgresql+psycopg://')
    
    # used for the message flashing feature inside flask
    SECRET_KEY = os.environ.get("SECRET_KEY")
    
    
class DevelopmentConfig(Config):
    DEVELOPMENT = True
    DEBUG = True
    

class ProductionConfig(Config):
    DEBUG = False
    LOG_TO_STDOUT = os.environ.get('LOG_TO_STDOUT')
    SECRET_KEY = os.environ.get("SECRET_KEY")
    DEVELOPMENT = False

    
@staticmethod
def init_app(app):
    pass 