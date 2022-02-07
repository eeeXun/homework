from flask import Flask,request

app=Flask(__name__)

@app.route('/')
def index():
    html='''<form method=post action=bmi>
Height:<input type=text name=height><br>
Weight:<input type=text name=weight><br>
<input type=submit>'''
    return html

@app.route('/bmi',methods=['GET','POST'])
def bmi():
    h=float(request.form['height'])
    # h=request.form['height']
    w=float(request.form['weight'])
    # w=request.form['weight']
    bmi=w/(h*h)
    return '<h1>Your BMI is {}'.format(bmi)
