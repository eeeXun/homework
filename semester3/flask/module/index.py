from flask import request, Flask, render_template

app = Flask(__name__)


from snsd0805  import f1
from eeexun    import f2
from dogking  import f3
from three import f4

@app.route('/')
def index():
    return f1()

@app.route('/start')
def welcome():
    return f2()

@app.route('/login')
def login():
    return f3()

@app.route('/answer')
def form():
    return f4()

if __name__ == '__main__':
    app.debug = True
    app.run(host='127.0.0.1')

