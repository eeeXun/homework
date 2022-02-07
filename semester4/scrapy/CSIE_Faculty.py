from selenium import webdriver
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "https://www.csie.ncnu.edu.tw/member/professor"

browser.get(url)
infos = browser.find_elements_by_class_name("personcard_wrap ")
for info in infos:
    tmp = info.text.split()
    print(tmp[0], tmp[3])
browser.close()
