from urllib.request import urlopen
from bs4 import BeautifulSoup

url = "https://www.ly.gov.tw/Pages/List.aspx?nodeid=109"
html = urlopen(url)
bsObj = BeautifulSoup(html.read(), "html.parser")

INFOs = bsObj.findAll("div", {"class", "caption"})

for info in INFOs:
    party = info.find("img", {"class": "six-party-icon"})["alt"]
    name = info.find("div", {"class", "legislatorname"}).get_text()
    print(party[:-2], name)
