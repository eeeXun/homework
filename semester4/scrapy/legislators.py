from urllib.request import urlopen
from bs4 import BeautifulSoup

url = "https://www.ly.gov.tw/Pages/List.aspx?nodeid=109"
html = urlopen(url)
bsObj = BeautifulSoup(html.read(), "html.parser")

nameList = bsObj.findAll("div", {"class", "legislatorname"})

for name in nameList:
    print(name.get_text())
