# Loads drivers from f1db.db from f1db an unofficial f1db
# https://github.com/f1db/f1db
# Driver data accessed on 3.14.25  

import sqlite3


def get_database_connection():
    db_path = "f1db.db"
    conn = sqlite3.connect(db_path)
    cur = conn.cursor()
    try:
        yield cur

    finally:
        cur.close()
        conn.close()

    
def query_f1_db(database_cursor):
    query = "SELECT name, nationality_country_id, date_of_birth, permanent_number, total_race_starts, total_race_wins, total_points FROM Driver"
    try:
        cur = database_cursor.__next__()
        cur.execute(query)
        with open("drivers.txt", "w") as f:
            for row in cur.fetchall():
                for i in row:
                    f.write(f"{i},")
                f.write("\n")
    except Exception as e:
        print(e)


def count_drivers():
    count = 0
    with open("drivers.txt", "r") as f:
        x = len(f.readlines())
        return x


def main():
    query_f1_db(get_database_connection())
    print(count_drivers())


if __name__ == "__main__":
    main()