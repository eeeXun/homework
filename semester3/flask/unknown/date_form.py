from flask import Flask,render_template,request
from flask_wtf import FlaskForm
from wtforms import StringField,SubmitField,SelectField
from wtforms.validators import DataRequired

app=Flask(__name__)
app.config['SECRET_KEY']='hard to guess'

class NameForm(FlaskForm):
    yearchoice=[i for i in range(1950,2021)]
    monthchoice=[(1,'Jan'),(2,'Feb'),(3,'Mar'),(4,'Apr'),(5,'May'),(6,'Jun'),
                 (7,'Jul'),(8,'Aug'),(9,'Sep'),(10,'Oct'),(11,'Nov'),(12,'Dec')]
    daychoice=[i for i in range(1,32)]
    year=SelectField('Year',choices=yearchoice)
    month=SelectField('Month',choices=monthchoice)
    day=SelectField('Day',choices=daychoice)
    submit=SubmitField('Submit')

@app.route('/')
def index():
    form=NameForm()
    return render_template('render_date.html',form=form)

@app.route('/date',methods=['POST'])
def date():
    from datetime import datetime
    year=request.form['year']
    month=request.form['month']
    day=request.form['day']
    weekday=datetime.strptime('{}-{}-{}'.format(year,month,day),'%Y-%m-%d').strftime('%w')
    if weekday=='0':
        weekday='Sun'
    elif weekday=='1':
        weekday='Mon'
    elif weekday=='2':
        weekday='Tue'
    elif weekday=='3':
        weekday='Wen'
    elif weekday=='4':
        weekday='Thu'
    elif weekday=='5':
        weekday='Fri'
    else:
        weekday='Sat'
    return '<h1>It\'s {}/{}/{} {}'.format(year,month,day,weekday)
