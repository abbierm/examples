import sqlalchemy as sa
import sqlalchemy.orm as so
from sqlalchemy.ext.declarative import declarative_base
from datetime import datetime, timezone
from sqlalchemy.orm import sessionmaker
from sqlalchemy.exc import IntegrityError, OperationalError
from contextlib import contextmanager
from config import SQLALCHEMY_DATABASE_URL


engine = sa.create_engine(SQLALCHEMY_DATABASE_URL, echo=True)
Base = declarative_base()

class Post(Base):
    __tablename__ = "posts"
    id: so.Mapped[int] = so.mapped_column(primary_key=True)
    title: so.Mapped[str] = so.mapped_column(sa.String(64), \
                                             index=True, unique=True)
    url: so.Mapped[str] = so.mapped_column(sa.String(64), \
                                           index=True, unique=True)
    date: so.Mapped[datetime] = so.mapped_column(index=True, \
                                    default=lambda: datetime.now(timezone.utc))
    date_readable: so.Mapped[str] = so.mapped_column(sa.String(16))
    last_updated: so.Mapped[datetime] = so.mapped_column(index=True, \
                                    default=lambda: datetime.now(timezone.utc))
    content: so.Mapped[str] = so.mapped_column(sa.Text)
    tags: so.Mapped[str] = so.mapped_column(sa.Text)
    styles: so.Mapped[str] = so.mapped_column(sa.Text)

    def edit_post(self, meta: dict, post_content: str, db) -> bool:
    	self.title = meta["title"]
    	self.url = meta["url"]
    	self.last_updated = datetime.now(timezone.utc)
    	self.content = post_content
    	self.tags = meta["tags"]
    	self.styles=str(meta["styles"])
    	try:
    		db.add(self)
    		db.commit()
    		return True
    	except (IntegrityError, OperationalError) as e:
    		print(f"ERROR: {e}")
    		return False

@contextmanager
def get_db():
    Base.metadata.create_all(bind=engine)
    SessionLocal = sessionmaker(bind=engine)
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()