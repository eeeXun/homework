from tkinter import *
from urllib.request import urlopen

url = "http://ipv6.ncnu.org/Course/PyGUI/Exercise/ncnu_dept.txt"
html = urlopen(url)
data = html.read().decode("utf-8").split("\n")[:-1]
college = []
Deparments = {}
for i in data:
    d, n = i.split(" ")
    if d not in Deparments:
        college.append(d)
        Deparments[d] = []
    Deparments[d].append(n)

def itemSelected(event):
    obj = event.widget
    index = obj.curselection()
    dps = Deparments[college[index[0]]]
    lb2.delete(0, END)
    lb2.insert(END, *dps)

root = Tk()
lb1 = Listbox(root)
lb2 = Listbox(root)
for d in Deparments:
    lb1.insert(END, d)
lb1.pack(side=LEFT)
lb1.bind("<<ListboxSelect>>", itemSelected)
lb2.pack()
root.mainloop()
