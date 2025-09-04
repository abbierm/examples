# the entire suite of functions that I use push/edit posts from content folder

from pathlib import Path
from config import BASEDIR, COMPLETE_DIR, INPROGRESS_DIR
import yaml
from .models import get_db, Post
from sqlalchemy.exc import IntegrityError, OperationalError
import sqlalchemy as sa
import sys
from datetime import datetime, timezone
import ast


def _parse_html_file(filepath: Path) -> tuple[dict, str] | None:
	"""Creates dict from YAML metadata and returns dict and html as string"""
	with open(filepath, "r", encoding="utf-8") as fp:
		page = fp.read()
		parts = page.split("---", 2)
		_, yaml_block, html = parts
		metadata = yaml.safe_load(yaml_block)
		return (metadata, html)



# =============================================================================
# Upload posts from the db
# =============================================================================
def push_post_to_db(
	location: Path,
	filename: str
):
	"""Pushes filename from inprogress to db and then moves in to completed"""	
	if filename == "":
		print("Must include filename to upload")
		return
	
	fp = Path(BASEDIR, "content", "inprogress", filename + ".html")
	if not fp.exists():
		print(f"Unable to locate file: {fp}")
		return
	meta, post_content = _parse_html_file(fp)
	with get_db() as db:
		new_post = Post(
			title=meta["title"],
			url=meta["url"],
			date_readable=meta["date_readable"],
			content=post_content,
			tags=meta["tags"],
			styles=str(meta["styles"])
		)
		try:
			db.add(new_post)
			db.commit()
			print("Successfully uploaded post to db")
			fp.rename(Path(BASEDIR, "content", "complete", fp.name))
		except (IntegrityError, OperationalError) as e:
			db.rollback()
			print(f"ERROR: {e}")
	return


# =============================================================================
# Edit Posts from content/complete directory
# =============================================================================
def edit_existing_post(
	location: Path,
	filename: str
):
	"""
		- Looks for filename inside of content/completed file
		- Queries the external database to find matching item
		- Updates with w.e is inside of the file using Post method
			- Changes the -"last updated--- section to right now"  
	"""
	fp = Path(location, filename + ".html")
	if not fp.exists():
		print(f"Could not locate {fp}")
		return
	meta, post_content = _parse_html_file(fp)
	with get_db() as db:
		p = db.scalar(sa.select(Post).where(Post.title == meta["title"]))
		if p is None:
			print(f"Could not locate {meta["title"]} inside external database")
			return
		p.edit_post(meta, post_content, db)
	return



# =============================================================================
# Download the posts from the db
# =============================================================================
def _read_to_file(file: Path, post: Post) -> None:
   # Use context manager with file
    with open(file, "w", encoding="utf-8") as f:
        # YAML metadata at the top of the page
        f.write("---\n")
        f.write(f"title: {post.title}\n")
        f.write(f"url: {post.url}\n")
        date = post.date
        f.write(f"date: {date}\n")
        f.write(f"month: {date.strftime('%B')}\n")
        f.write(f"day: {date.strftime('%d')}\n")
        f.write(f"year: {date.strftime('%Y')}\n")
        f.write(f"date_readable: {post.date_readable}\n")
        f.write(f"tags: {post.tags}\n")
        if post.styles == "None":
            f.write(f"styles: null")
        else:
            styles_dictionary = ast.literal_eval(post.styles)
            styles = yaml.dump(styles_dictionary, default_flow_style=False)
            f.write(f"styles: {styles}\n")
        f.write("---\n")
        f.write(post.content)
    return 


def download_posts(
    location: Path = COMPLETE_DIR,
    filename: str | None = None,
    rewrite_if_duplicate: bool = True
) -> None:
    if not location.exists():
        if input(f"The path {location} doesn't exist, would you like to create it? y/n: ").lower() != "y":
            print("Exiting the program")
            sys.exit()
        location.mkdir(parents=True)

    with get_db() as db:
        if filename != "":
            posts = [db.scalar(sa.select(Post).where(Post.url == filename)),]
            if len(posts) == 0:
                print(f"{filename} doesn't exist inside of db")
                sys.exit()
        else:
            posts = list(db.scalars(sa.select(Post)))
        for post in posts:
            post_html_file = post.url + ".html"
            new_post_fp = Path(location, post_html_file) 
            if not rewrite_if_duplicate and new_post_fp.exists():
                print(f"A file at {new_post_fp} already exists")
                continue
            _read_to_file(new_post_fp, post)

