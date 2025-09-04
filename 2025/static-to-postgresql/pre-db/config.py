from pathlib import Path

BASEDIR = Path(__file__).parent.absolute()

class Config:
    ROOT = BASEDIR
    FLATPAGES_AUTO_RELOAD = True
    FLATPAGES_EXTENSION = ".html"
    FLATPAGES_ROOT = "../content"


    @staticmethod
    def init_app(app):
        pass