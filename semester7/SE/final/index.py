from flask import Flask, redirect, render_template, request, session
from flask_socketio import SocketIO

app = Flask(__name__)
app.config["SECRET_KEY"] = "ABC"
socketio = SocketIO(app)
global answer
global current_user


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/redirect_login")
def redirect_login():
    username = request.values["username"]
    session["username"] = username
    return redirect("/login")


@app.route("/login")
def login():
    username = session.get("username")
    return render_template("login.html", username=username)


@app.route("/question")
def question():
    return render_template("question.html")


@socketio.on("set")
def set(data):
    global answer
    if data == "game_over":
        answer = None
        socketio.emit("set_q", "<h2>Game Over!</h2>")
        socketio.emit("set_qa", "<h2>Game Over!</h2>")
        socketio.emit("close_answer", "No one")
        return
    answer = data[1]
    socketio.emit(
        "set_q",
        f"<h2>Question:{data[0]}</h2>",
    )
    socketio.emit(
        "set_qa",
        f"<h2>Question:{data[0]}</h2><h2>Answer:{data[1]}</h2>",
    )
    socketio.emit("open_answer", "")


@socketio.on("press_answer")
def press_answer(data):
    global current_user
    username = session.get("username")
    current_user = username
    session_id = request.sid
    socketio.emit("close_answer", username)
    socketio.emit("open_message", "", room=session_id)


@socketio.on("send_message")
def send_message(data):
    global answer
    username = session.get("username")
    socketio.emit("set_box", f"{username}: {data}<br>")
    session_id = request.sid

    if data == answer:
        socketio.emit("set_box", f"{username} get the answer!<br>")
        socketio.emit("set_q", "<h2>No question!</h2>")
        socketio.emit("close_answer", "No one")
    else:
        socketio.emit("open_answer", "")

    socketio.emit("close_message", "", room=session_id)


if __name__ == "__main__":
    app.debug = True
    socketio.run(app, host="0.0.0.0")
