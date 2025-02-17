from pathlib import Path

BASEDIR = Path(__file__).parent.absolute()

class Config:
	TESTING = False

	@staticmethod
	def init_app(app):
		pass