from tkinter import *

myDic = {}
for i in range(10, 18):
    myDic[chr(i + 55)] = str(i)
for i in range(18, 23):
    myDic[chr(i + 56)] = str(i)
for i in range(23, 30):
    myDic[chr(i + 57)] = str(i)
myDic["X"] = str(30)
myDic["Y"] = str(31)
myDic["W"] = str(32)
myDic["Z"] = str(33)
myDic["I"] = str(34)
myDic["O"] = str(35)

def checkLen(P):
    if len(P) == 10:
        validateBtn.config(state=NORMAL)
    else:
        validateBtn.config(state=DISABLED)
    return True

def isValid():
    tmpNum = idNumber.get()
    if ord(tmpNum[0]) >= 65 and ord(tmpNum[0]) <= 90 and tmpNum[1:].isdigit():
        tmpNum = myDic[tmpNum[0]] + tmpNum[1:]
        tmpSum = int(tmpNum[0]) + int(tmpNum[-1])
        for i in range(1, 10):
            tmpSum += (10 - i) * int(tmpNum[i])
        if tmpSum % 10 == 0:
            label2.config(text="Valid")
        else:
            label2.config(text="Incorrect", fg="red")
    else:
        label2.config(text="Incorrect", fg="red")

root = Tk()
reg = root.register(checkLen)
label = Label(root, text="ID", font="Monospace 15")
label2 = Label(root, text="",  font="Monospace 15")
validateBtn = Button(root, text="Verify", state=DISABLED, font="Monospace 15",
                     activebackground="yellow", command=isValid)

idNumber = Entry(root, validate='key', validatecommand=(reg, "%P"))
label.grid(row=0)
idNumber.grid(row=0, column=1)
validateBtn.grid(row=1, column=1, sticky=E+W)
label2.grid(row=2, column=1)

root.mainloop()
