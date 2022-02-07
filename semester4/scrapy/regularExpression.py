from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

url = "https://market.cloud.edu.tw/web/resources_english.jsp?role=student&gradetype=senior"
html = urlopen(url)
bsObj = BeautifulSoup(html, "html.parser")

pattern = "^Root"

findRoot = bsObj.findAll("a", text = re.compile(pattern))
for item in findRoot:
    print(item.get_text())
