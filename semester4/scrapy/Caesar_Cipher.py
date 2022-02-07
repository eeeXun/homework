from tkinter import *

def enco():
    t = text1.get("1.0", "end")
    shift = int(text2.get("1.0", "end")[:-1])
    result = ""
    for i in t:
        if i.isalpha():
            tmp = ord(i.upper()) + shift
            if tmp > 90:
                tmp -= 26
            result += chr(tmp)
        else:
            result += i
    text3.delete(1.0, "end")
    text3.insert("end", result)

def deco():
    t = text3.get(1.0, "end")
    shift = int(text2.get(1.0, "end")[:-1])
    result = ""
    for i in t:
        if i.isalpha():
            tmp = ord(i.upper()) - shift
            if tmp < 65:
                tmp += 26
            result += chr(tmp)
        else:
            result += i
    text1.delete(1.0, "end")
    text1.insert("end", result)

root = Tk()
text1 = Text(root, height=5, width=30)
text2 = Text(root, height=2, width=30)
text3 = Text(root, height=5, width=30)
bt1 = Button(root, text="->", command=enco)
bt2 = Button(root, text="<-", command=deco)
text1.pack(side=LEFT)
text3.pack(side=RIGHT)
text2.pack(side=TOP)
bt1.pack(side=TOP)
bt2.pack(side=TOP)
root.mainloop()
