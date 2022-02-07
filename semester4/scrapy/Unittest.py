from selenium import webdriver
from selenium.webdriver.support.select import Select
import unittest
import os

options = webdriver.ChromeOptions()
options.add_argument("-headless")
drivePath = os.getenv("HOME") + "/Downloads/chromedriver"
browser = webdriver.Chrome(executable_path=drivePath, options=options)
url = "http://lilina.csie.ncnu.edu.tw/~solomon/Lang/PHP/hw10_5_select.html"
x = [5, 10, 15, 20]
y = [5, 10, 15, 20]

class TestWeb(unittest.TestCase):

    def mytest(self, op, optext):
        for i in x:
            for j in y:
                browser.get(url)
                browser.find_element_by_id("x").send_keys(i)
                browser.find_element_by_id("y").send_keys(j)
                op_select = Select(browser.find_element_by_id("operation"))
                op_select.select_by_value(optext)
                browser.find_element_by_id("submit").click()
                real_ans = round(eval("{}{}{}".format(i, op, j)), 5)
                my_ans = round(float(browser.find_element_by_tag_name("body").text), 5)
                with self.subTest(x=i, y=j):
                    self.assertEqual(my_ans, real_ans)

    def test_add(self):
        self.mytest("+", "add")
    def test_sub(self):
        self.mytest("-", "sub")
    def test_mul(self):
        self.mytest("*", "mul")
    def test_div(self):
        self.mytest("/", "div")

if __name__ == "__main__":
    unittest.main()
    browser.close()
