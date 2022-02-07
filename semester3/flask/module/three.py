from flask import request

def f4():
    a = int(request.values['n1'])
    b = int(request.values['n2'])
    return "{} + {} = {}".format(a, b, a+b)
