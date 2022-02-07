from selenium import webdriver
from tkinter import *
from tkhtmlview import HTMLLabel
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "https://www.csie.ncnu.edu.tw/member/professor"
html = "<ol>"

browser.get(url)
infos = browser.find_elements_by_class_name("personcard_wrap ")
for info in infos:
    links = info.find_elements_by_tag_name("a")
    person_name = links[0].text
    person_link = links[0].get_attribute("href")
    mail = links[1].text
    mail_link = links[1].get_attribute("href")
    img = info.find_element_by_tag_name("img").get_attribute("src")
    html += '<li><a href={}><img src="{}" width="100" height="100"></a><a href="{}">{}</a><a href="{}">{}</a>'.format(person_link, img, person_link, person_name, mail_link, mail)
browser.close()
html += "</ol>"
print(html)

root = Tk()
xscrollbar = Scrollbar(root, orient=HORIZONTAL)
yscrollbar = Scrollbar(root)
xscrollbar.pack(side=BOTTOM, fill=X)
yscrollbar.pack(side=RIGHT, fill=Y)
lbl = HTMLLabel(root, html=html)
lbl.pack()
yscrollbar.config(command=lbl.yview)
xscrollbar.config(command=lbl.xview)
lbl.config(yscrollcommand=yscrollbar.set)
lbl.config(xscrollcommand=xscrollbar.set)
root.mainloop()
