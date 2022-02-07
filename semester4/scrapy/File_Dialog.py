from tkinter import *
from tkinter import filedialog

def loadFile():
    fname = filedialog.askopenfile()
    content = fname.read()
    myEntry.insert(0, content)

def saveFile():
    myinput = myEntry.get()
    fname = filedialog.asksaveasfile()
    fname.write(myinput)

root = Tk()
myEntry = Entry(root)
myEntry.pack(side=BOTTOM)
Button(root, text="Load", command=loadFile).pack(side=LEFT)
Button(root, text="Save", command=saveFile).pack(side=LEFT)

root.mainloop()
