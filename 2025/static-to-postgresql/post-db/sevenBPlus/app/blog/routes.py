from flask import render_template, redirect, flash, url_for, current_app
from app.blog import bp
from app import db, flatpages
import sqlalchemy as sa
from ..models import Post
import ast


@bp.route("/", methods=["GET"])
def all():
    if current_app.config.get("DEVELOPMENT") == True:
        ip_posts = sorted([p for p in flatpages if p.folder == "posts/inprogress"], key=lambda x: x.meta["date"], reverse=True)
    else:
        ip_posts = None
    posts = list(db.session.scalars(sa.select(Post).order_by(Post.date.desc())))
    return render_template("blog/all.html", posts=posts, ip_posts=ip_posts)


@bp.route("/<url>", methods=["GET"])
def post(url):
    p = db.session.scalar(sa.select(Post).where(Post.url == url))
    if p:
        # This is part of the magical (hacky) abstraction of how I render my css
        style_dict = ast.literal_eval(p.styles) if p.styles != "None" else {}
        return render_template("blog/post.html", post=p, styles=style_dict, ip=False)

    # Searches for post if it's in development and 'in-progress'
    elif not p and current_app.config.get("DEVELOPMENT"):
        post_path = "posts/inprogress/{}".format(url)
        ip_post = flatpages.get(post_path)
        if ip_post: 
            style_dict = ip_post.meta["styles"]
            return render_template("blog/post.html", post=ip_post, 
                                        styles=style_dict, ip=True)
    flash(f"Unable to find Post: {url}")
    return redirect(url_for("blog.all"))