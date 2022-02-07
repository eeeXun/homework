from flask import request

def f3():
    html='<form action="answer" method="GET">'
    html+='<table>'
    html+='<tr><td>HI! {}</td><tr>'.format(request.args['username'])
    html+='<tr><td>input two number<input type=text name=n1>+<input type=text name=n2></td></tr>'
    html+='<tr><td><input type=submit>'
    html+='</table>'
    html+='</form>'
    return html
