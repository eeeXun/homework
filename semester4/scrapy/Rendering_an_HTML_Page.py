import requests
from tkinter import *
from tkhtmlview import HTMLLabel

def fetch():
    url = ent.get()
    r = requests.get(url)
    html = r.text
    lbl.set_html(html)

root = Tk()
ent = Entry(root)
btn = Button(root, text="Fetch", command=fetch)
ent.pack(side=TOP)
btn.pack(side=TOP)
lbl = HTMLLabel(root)
lbl.pack()
root.mainloop()
