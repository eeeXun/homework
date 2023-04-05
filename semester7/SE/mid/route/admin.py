from flask import Blueprint, redirect, render_template, request

from backend.cart import Cart
from backend.item import Item

admin_route = Blueprint("admin_route", __name__)


@admin_route.route("/admin/", methods=["GET"])
def admin():
    items = Item.get_all_item()
    carts = Cart.get_all_cart()
    return render_template("admin.html", items=items, carts=carts)


@admin_route.route("/additem/", methods=["POST"])
def add_item():
    name = request.form["name"]
    amount = request.form["amount"]
    Item.add_item(name, amount)
    return redirect("/admin")


@admin_route.route("/deleteitem/", methods=["POST"])
def delete_item():
    item_id = request.form["id"]
    Item.delete_item(item_id)
    return redirect("/admin")


@admin_route.route("/updateitem/", methods=["POST"])
def update_item():
    item_id = request.form["id"]
    item_name = request.form["name"]
    item_amount = request.form["amount"]
    Item.update_item(item_id, item_name, item_amount)
    return redirect("/admin")
