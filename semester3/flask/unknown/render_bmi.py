from flask import Flask,render_template,request
from flask_wtf import FlaskForm
from wtforms import StringField,SubmitField
from wtforms.validators import DataRequired

app=Flask(__name__)
app.config['SECRET_KEY']='hard to guess'

class NameForm(FlaskForm):
    height=StringField('Your height?',validators=[DataRequired()])
    weight=StringField('Your weight?',validators=[DataRequired()])
    submit=SubmitField('Submit')

@app.route('/')
def index():
    form=NameForm()
    return render_template('render_form.html',form=form)

@app.route('/bmi',methods=['POST'])
def bmi():
    height=float(request.form['height'])
    weight=float(request.form['weight'])
    bmi=weight/(height*height)
    return '<h1>Your BMI is {}'.format(bmi)
