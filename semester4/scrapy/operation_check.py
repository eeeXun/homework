from selenium import webdriver
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "http://ms15.ipv6.club.tw/~solomon/PHP/operation.html"

x = "4"
y = "2"
op = {"add": "+", "sub": "-", "mul": "*", "div": "/"}
for i in op:
    browser.get(url)
    browser.find_element_by_id("x").send_keys(x)
    browser.find_element_by_id("y").send_keys(y)
    browser.find_element_by_id(i).click()
    browser.find_element_by_id("submit").click()
    real_ans = eval("{}{}{}".format(x, op[i], y))
    my_ans = float(browser.find_element_by_tag_name("body").text)
    print("Operation {} is ".format(op[i]), end="")
    if my_ans == real_ans:
        print("correct.")
    else:
        print("incorrect.")
browser.close()
