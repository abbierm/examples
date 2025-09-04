from flask import render_template, send_from_directory
from app.main import bp

@bp.route("/", methods=["GET"])
def index():
    return render_template("index.html")


@bp.route("/about", methods=["GET"])
def about():
    return render_template("about.html")

