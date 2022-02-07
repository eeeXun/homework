from urllib.request import urlopen
from bs4 import BeautifulSoup

url = "http://www.mis.kuas.edu.tw/main.php?mod=teacher&site_id=0"
html = urlopen(url).read().decode("UTF-8")
bsObj = BeautifulSoup(html, "html.parser")
columnLists = bsObj.findAll("div", {"class": "itemContent"})

for columnList in columnLists:
    name = columnList.find("font", {"color": "blue"}).get_text()
    email = columnList.find("td", {"style": "text-align:center;width:"}).find("a").get_text()
    print(name, email)
