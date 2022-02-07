from tkinter import *

root = Tk()
star=""
# N = 10

for i in range(1, 10):
    star += "*" * i + "\n"

label = Label(root, text = star, justify = "right", font = ("Monospace", 20, "bold"))
label.pack()

root.mainloop()
