import sqlite3

from flask import session

DBNAME = "test.db"


class User:
    @staticmethod
    def login(username, pwd):
        """
        success return 1
        wrong password return 0
        not register return -1
        """
        with sqlite3.connect(DBNAME) as conn:
            stmt = "SELECT id, pwd FROM users WHERE username == '{}'".format(
                username
            )
            cursor = conn.cursor()
            cursor.execute(stmt)
            data = cursor.fetchone()

            if not data:
                return -1
            else:
                if data[1] == pwd:
                    session["id"] = data[0]
                    return 1
                else:
                    return 0

    @staticmethod
    def register(username, pwd):
        """
        success return 1
        failed return 0
        """
        with sqlite3.connect(DBNAME) as conn:
            stmt = "INSERT INTO users (username, pwd) VALUES (?, ?);"
            conn.execute(stmt, [username, pwd])
            conn.commit()
        return 1

    @staticmethod
    def get_username():
        with sqlite3.connect(DBNAME) as conn:
            uid = session.get("id")
            stmt = "SELECT username FROM users WHERE id == (?)"
            username = conn.execute(stmt, [uid]).fetchone()[0]
            return username

    @staticmethod
    def add_cart(item_id, item_amount):
        with sqlite3.connect(DBNAME) as conn:
            uid = session.get("id")
            stmt = "INSERT INTO cart (user_id, item_id, item_amount) VALUES (?, ?, ?);"
            conn.execute(stmt, [uid, item_id, item_amount])
            conn.commit()
            stmt = "UPDATE items SET amount = amount - ? WHERE id=?;"
            conn.execute(stmt, [int(item_amount), item_id])
            conn.commit()

    @staticmethod
    def get_user_cart():
        """
        return (cart_id, item_amount, item_name)
        """
        with sqlite3.connect(DBNAME) as conn:
            uid = session.get("id")
            stmt = """SELECT cart.id, cart.item_amount, items.name
            FROM (cart LEFT JOIN items ON cart.item_id=items.id)
            WHERE user_id=(?);"""
            data = conn.execute(stmt, [uid]).fetchall()
            return data

    @staticmethod
    def buy_cart(cart_id):
        with sqlite3.connect(DBNAME) as conn:
            stmt = "DELETE FROM cart WHERE id = ?"
            conn.execute(stmt, [cart_id])
            conn.commit()
