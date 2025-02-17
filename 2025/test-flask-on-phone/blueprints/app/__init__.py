from config import Config
from flask import Flask
from .scripts import make_api_request

def create_app(config_class=Config):
	app = Flask(__name__)
	app.config.from_object(config_class)

	make_api_request()

	from app.api import bp as api_bp
	app.register_blueprint(api_bp, url_prefix="/api")

	from app.main import bp as main_bp
	app.register_blueprint(main_bp, url_prefix="/")

	return app