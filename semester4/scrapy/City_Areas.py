from selenium import webdriver
from selenium.webdriver.support.select import Select
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "https://www.post.gov.tw/post/internet/Postal/index.jsp?ID=208"
city_area = {}

browser.get(url)
city_select = Select(browser.find_element_by_id("city_zip6"))
city = city_select.options[1:]
for c in city:
    c = c.text
    city_select.select_by_value(c)
    area = browser.find_element_by_id("cityarea_zip6").text.split("\n")
    city_area[c] = area

with open("cityarea.csv", "w") as f:
    for c in city_area:
        for a in city_area[c]:
            f.write("{},{}\n".format(c, a))
browser.close()
