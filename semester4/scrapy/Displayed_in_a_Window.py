from urllib.request import urlopen
from bs4 import BeautifulSoup
from tkinter import *

url =  "https://www.ly.gov.tw/Pages/List.aspx?nodeid=109"
html = urlopen(url)
bsObj = BeautifulSoup(html.read(), "html.parser")

INFOs = bsObj.findAll("div", {"class", "caption"})
partySet = {}

for info in INFOs:
    party = info.find("img", {"class": "six-party-icon"})["alt"]
    name = info.find("div", {"class", "legislatorname"}).get_text()

    if party[:-2] not in partySet:
        partySet[party[:-2]] = [name]
    else:
        partySet[party[:-2]].append(name)

root = Tk()
myRow = 0
myColumn = 0
colors = ["red", "orange", "yellow", "green", "blue", "purple"]

for party in partySet:
    partyLabel = Label(root, text = party, bg = colors[myColumn])
    partyLabel.grid(row = myRow, column = myColumn, sticky = "EW")
    for name in partySet[party]:
        myRow += 1
        nameLabel = Label(root, text = name)
        nameLabel.grid(row = myRow, column = myColumn)
    myRow = 0
    myColumn += 1

root.mainloop()
