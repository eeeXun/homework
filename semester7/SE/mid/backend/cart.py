import sqlite3

DBNAME = "test.db"


class Cart:
    @staticmethod
    def get_all_cart():
        with sqlite3.connect(DBNAME) as conn:
            """
            return user_name, item_name, cart_id, cart_amount
            """
            stmt = """SELECT users.username, items.name, cart.id, cart.item_amount
            FROM cart
            LEFT JOIN users ON cart.user_id = users.id
            LEFT JOIN items ON cart.item_id=items.id;"""
            data = conn.execute(stmt).fetchall()
            return data

    @staticmethod
    def delete_cart(cart_id):
        with sqlite3.connect(DBNAME) as conn:
            stmt = """UPDATE items
            SET amount = amount + (SELECT item_amount FROM cart WHERE id = ?)
            WHERE id = (SELECT item_id FROM cart WHERE id = ?);"""
            conn.execute(stmt, [cart_id, cart_id])
            conn.commit()
            stmt = "DELETE FROM cart WHERE id = ?;"
            conn.execute(stmt, [cart_id])
            conn.commit()
