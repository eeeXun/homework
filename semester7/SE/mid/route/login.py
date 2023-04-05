from flask import Blueprint, redirect, render_template, request, session

from backend.cart import Cart
from backend.item import Item
from backend.user import User

login_route = Blueprint("login_route", __name__)


@login_route.route("/error/", methods=["GET"])
def error():
    msg = request.values["msg"]
    return render_template("error.html", msg=msg)


@login_route.route("/", methods=["GET"])
def index():
    return render_template("index.html")


@login_route.route("/login/", methods=["POST"])
def login():
    username = request.form["username"]
    pwd = request.form["pwd"]
    response = User.login(username, pwd)

    if response == 1:
        return redirect("/page")
    elif response == 0:
        return redirect("/error?msg=Wrong+password")
    else:
        return redirect("/error?msg=This+account+is+not+register")


@login_route.route("/page/", methods=["GET", "POST"])
def page():
    username = User.get_username()
    items = Item.get_all_item()
    carts = User.get_user_cart()
    items = sorted(items, key=lambda s: s[1], reverse=True)
    for i in range(len(items)):
        print(items[i])
        if items[i][1] >= 100:
            items[i] = [items[i][0], items[i][1], items[i][2], "red"]
        elif items[i][1] >= 50:
            items[i] = [items[i][0], items[i][1], items[i][2], "blue"]
        else:
            items[i] = [items[i][0], items[i][1], items[i][2], "green"]
    return render_template(
        "user.html", name=username, items=items, carts=carts
    )


@login_route.route("/register/", methods=["POST"])
def register():
    username = request.form["username"]
    pwd = request.form["pwd"]
    response = User.register(username, pwd)

    if response == 1:
        return f"""<p>{username} register success</p>
    <a href='/'><button>Back</button></a>"""
    else:
        return redirect("/error?msg=Something+wrong!")


@login_route.route("/addcart/", methods=["POST"])
def add_cart():
    item_id = request.form["id"]
    item_amount = request.form["amount"]
    item_remain = int(Item.get_item_amount(item_id))
    if (
        len(item_amount) > 0
        and int(item_amount) > 0
        and item_remain >= int(item_amount)
    ):
        User.add_cart(item_id, item_amount)
    return redirect("/page")


@login_route.route("/buycart/", methods=["POST"])
def buy_cart():
    cart_id = request.form["id"]
    User.buy_cart(cart_id)
    return redirect("/page")


@login_route.route("/logout/", methods=["GET", "POST"])
def logout():
    session["id"] = False
    return redirect("/")
