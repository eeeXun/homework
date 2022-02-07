from flask import Flask
app=Flask(__name__)

@app.route('/multiply/<int:n>')
def multipy(n):
    table='<table border="1">'
    for i in range(n):
        table+='<tr>'
        for j in range(n):
            table+='<td>{}*{}={}</td>'.format(i+1,j+1,(i+1)*(j+1))
        table+='</tr>'

    table+='</table>'

    return table
