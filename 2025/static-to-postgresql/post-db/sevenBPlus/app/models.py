import sqlalchemy as sa
import sqlalchemy.orm as so
from app import db
from datetime import datetime, timezone


class Post(db.Model):
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