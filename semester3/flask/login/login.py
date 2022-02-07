from flask import Flask, render_template,request,redirect,url_for

app=Flask(__name__)

@app.route('/')
def index():
    html='''
<form action="/confirm" method="post">
Name<input type='text' name=name><br>
Passwd<input type='password' name=passwd><br>
<input type="submit">
</form>'''
    return html

@app.route('/confirm',methods=["POST"])
def confirm():
    name=request.form['name']
    passwd=request.form['passwd']
    with open('info.csv','r') as f:
        correct_pwd=False
        for i in f:
            n,p=i[:-1].split(',')
            if n==name:
                if p==passwd:
                    correct_pwd=True
                    break
                else:
                    break
        if correct_pwd:
            return redirect('/welcome?name={}'.format(name))
        else:
            return redirect('/invalid')

@app.route('/invalid')
def invalid():
    return '<h1>Invalid</h1>'

@app.route('/welcome')
def welcome():
    name=request.args['name']
    html='<a href="/change?name={}">Change pwd</a>'.format(name)
    return html

@app.route('/change',methods=['GET','POST'])
def change():
    name=request.args['name']
    # print(passwd)
    if request.method=='GET':
        html='''
<form method="post">
new passwd<input type=password name=new1><br>
confirm passwd<input type=password name=new2><br>
<input type=submit>
</form>'''
        return html
    else:
        new1=request.form['new1']
        new2=request.form['new2']
        if new1!=new2:
            return redirect('/fail_change')
        else:
            info=[]
            with open('info.csv','r') as f:
                for i in f:
                    info.append(i)
            with open('info.csv','w') as f:
                for i in info:
                    n,p=i.split(',')
                    if name==n:
                        f.write(name+','+new1+'\n')
                    else:
                        f.write(i)
            return redirect('/success')

@app.route('/success')
def success():
    return '<h1>Success change pwd</h1>'

@app.route('/fail_change')
def fail_change():
    return '<h1>Fail change password</h1>'
