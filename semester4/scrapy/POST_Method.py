import requests
from bs4 import BeautifulSoup

x = input("x=? ")
y = input("y=? ")
data = {"x": x, "y": y}
url = "http://ms15.ipv6.club.tw/~solomon/PHP/addition-post.php"
r = requests.post(url, data=data)
bsObj = BeautifulSoup(r.text, "html.parser")
expression = bsObj.find("span", {"id": "expression"}).get_text()
result = bsObj.find("span", {"id": "result"}).get_text()
print("{}={}".format(expression, result))
