import os
import shutil
import sqlite3

DBNAME = "test.db"


def check_db():
    if os.path.isfile(DBNAME):
        choose = input("Backup Database? ")
        if choose == "Y" or choose == "y":
            shutil.copy(DBNAME, DBNAME + ".bk")
            os.remove(DBNAME)
        else:
            exit(0)


def create_table():
    with open("test.sql") as f:
        sql = f.read()

        with sqlite3.connect(DBNAME) as conn:
            conn.executescript(sql)


if __name__ == "__main__":
    check_db()
    create_table()
