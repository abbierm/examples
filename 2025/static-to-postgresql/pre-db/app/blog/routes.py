from flask import render_template
from app.blog import bp
from app import flatpages
from app import Config
from datetime import datetime



@bp.route("/", methods=["GET"])
def all():
    # Only show finished posts
    # posts = sorted([p for p in flatpages if p.folder == "posts" and \
    #                     p.meta["date"] < datetime.now()], \
    #                     key=lambda x: x.meta["date"], reverse=True)
    
    # Shows all of the posts
    posts = sorted([p for p in flatpages], \
                     key=lambda x: x.meta["date"], reverse=True)
    
    return render_template("blog/all.html", posts=posts)


@bp.route("/<url>", methods=["GET"])
def post(url):
    # post_path = "{}".format(url)
    post = flatpages.get_or_404(url)
    print(post.meta)
    return render_template("blog/post.html", post=post)