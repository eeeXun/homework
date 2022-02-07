from flask import Flask,render_template,request
from flask_mail import Mail,Message

app=Flask(__name__)
mail=Mail(app)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/sendMail')
def sendMail():
    addr=request.args['mail']
    msg=Message('Hello',sender='s108321019@ncnu.com',recipients=[addr])
    msg.html=render_template('mail.html',addr=addr)
    with app.app_context():
        mail.send(msg)

    return 'Mail sent'

@app.route('/reply')
def reply():
    reply=request.args['usr']
    with open('out','a') as f:
        f.write(reply+'\n')
    return 'Thank you'

if __name__=='__main__':
    app.run(debug=True,host='lilina.csie.ncnu.edu.tw',port='10819')
