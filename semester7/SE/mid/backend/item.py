import sqlite3

DBNAME = "test.db"


class Item:
    @staticmethod
    def add_item(name, amount):
        with sqlite3.connect(DBNAME) as conn:
            stmt = "INSERT INTO items (name, amount) VALUES (?, ?);"
            conn.execute(stmt, [name, amount])
            conn.commit()

    @staticmethod
    def delete_item(id):
        with sqlite3.connect(DBNAME) as conn:
            stmt = "UPDATE items SET amount=0 WHERE id=?;"
            conn.execute(stmt, [id])
            conn.commit()

    @staticmethod
    def get_item_amount(id):
        with sqlite3.connect(DBNAME) as conn:
            stmt = "SELECT amount FROM items WHERE id = ?;"
            data = conn.execute(stmt, [id]).fetchone()[0]
            return data

    @staticmethod
    def get_all_item():
        """
        return (name, amount, id)
        """
        with sqlite3.connect(DBNAME) as conn:
            stmt = "SELECT name, amount, id FROM items WHERE amount > 0;"
            data = conn.execute(stmt).fetchall()
            return data

    @staticmethod
    def update_item(item_id, item_name, item_amount):
        with sqlite3.connect(DBNAME) as conn:
            stmt = "UPDATE items SET name = ?, amount= ? WHERE id = ?;"
            conn.execute(stmt, [item_name, item_amount, item_id])
            conn.commit()
