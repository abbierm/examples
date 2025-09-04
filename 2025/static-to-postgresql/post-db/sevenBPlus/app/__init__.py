from config import DevelopmentConfig, ProductionConfig
import os
from flask import Flask
from flask_flatpages import FlatPages
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate



flatpages = FlatPages()
db = SQLAlchemy()
migrate = Migrate()



def create_app():
    app = Flask(__name__)

    is_prod = os.environ.get("HEROKU", None)
    
    if not is_prod:
        app.config.from_object(DevelopmentConfig)
    else:
        app.config.from_object(ProductionConfig)

    from .utils import filters

    filters.init_app(app)
    
    # used to load pages in development server
    flatpages.init_app(app)

    db.init_app(app)
    migrate.init_app(app, db)

    from app.main import bp as main_bp
    app.register_blueprint(main_bp, url_prefix="/")

    from app.blog import bp as blog_bp
    app.register_blueprint(blog_bp, url_prefix="/blog")

    return app