from flask import Flask,request,redirect

app=Flask(__name__)

@app.route('/')
def index():
    html='<p><a href="/track?site=ncnu">NCNU</a></p>'
    html+='<p><a href="/track?site=bbc">BBC</a></p>'
    html+='<p><a href="/track?site=cnn">CNN</a></p>'
    return html

@app.route('/track',methods=['GET'])
def track():
    import time
    ncnu='https://www.gazette.ncnu.edu.tw/'
    bbc='https://bbc.com'
    cnn='https://cnn.com'
    site=request.args['site']
    ip=request.remote_addr
    now_time=time.localtime()
    time_info='['+str(now_time.tm_year)+'/'+str(now_time.tm_mon)+'/'+\
            str(now_time.tm_mday)+' '+str(now_time.tm_hour)+':'+\
            str(now_time.tm_min)+':'+str(now_time.tm_sec)+']'
    if site=='ncnu':
        with open('log_file','a+') as f:
            f.write(ip+' '+time_info+' '+ncnu+'\n')
        return redirect(ncnu)
    elif site=='bbc':
        with open('log_file','a+') as f:
            f.write(ip+' '+time_info+' '+ncnu+'\n')
        return redirect(bbc)
    else:
        with open('log_file','a+') as f:
            f.write(ip+' '+time_info+' '+ncnu+'\n')
        return redirect(cnn)
