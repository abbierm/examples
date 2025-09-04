from config import Config
from flask import Flask
from flask_frozen import Freezer
from flask_flatpages import FlatPages


flatpages = FlatPages()
freezer = Freezer()


def create_app(config_class=Config):
    app = Flask(__name__)
    app.config.from_object(config_class)

    from .utils import filters

    filters.init_app(app)

    freezer.init_app(app)
    flatpages.init_app(app)

    from app.main import bp as main_bp
    app.register_blueprint(main_bp, url_prefix="/")

    from app.blog import bp as blog_bp
    app.register_blueprint(blog_bp, url_prefix="/blog")

    return app