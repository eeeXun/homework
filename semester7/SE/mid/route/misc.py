from flask import Blueprint, redirect, request

from backend.cart import Cart

misc_route = Blueprint("misc_route", __name__)


@misc_route.route("/deletecart/", methods=["POST"])
def delete_cart():
    cart_id = request.form["id"]
    Cart.delete_cart(cart_id)
    try:
        request.form["admin"]
        return redirect("/admin")
    except:
        return redirect("/page")
