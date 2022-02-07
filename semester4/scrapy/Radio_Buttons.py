import requests

x = input("x=? ")
y = input("y=? ")
data = {"x": x, "y": y, "operator": "mul"}
url = "http://ms15.ipv6.club.tw/~solomon/PHP/operation.php"
r = requests.post(url, data=data)
print(r.text)
