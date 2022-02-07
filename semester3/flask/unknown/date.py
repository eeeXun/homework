from flask import render_template,request,Flask
app=Flask(__name__)

@app.route('/')
def index():
    ylist=[i for i in range(1950,2021)]
    dlist=[i for i in range(1,32)]
    return render_template('date.html',ylist=ylist,dlist=dlist)

@app.route('/date',methods=['GET','POST'])
def date():
    import datetime
    y=request.args['year']
    m=request.args['month']
    d=request.args['day']
    w=datetime.datetime.strptime('{}-{}-{}'.format(y,m,d),'%Y-%m-%d').strftime('%w')
    if w=='0':
        week='Sun'
    elif w=='1':
        week='Mon'
    elif w=='2':
        week='Tue'
    elif w=='3':
        week='Wen'
    elif w=='4':
        week='Thu'
    elif w=='5':
        week='Fri'
    else:
        week='Sat'

    return '<h1>It\'s {}-{}-{} {}</h1>'.format(y,m,d,week)
