from selenium import webdriver
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "https://activity.books.com.tw/books66/"

browser.get(url)
info = browser.find_element_by_class_name("table-td.w_590.pl_20").text.split()
print("{}\n{}\n{}".format(info[1], info[3], info[4]))
browser.close()
