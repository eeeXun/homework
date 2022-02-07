from tkinter import *
import random

horse_char = "~/-\\^"
finish = 11
font_config = ("Monospace", 20, "bold")
root = Tk()

class Horse:
    def __init__(self, pos):
        self.position = pos
    def forward(self):
        self.position += 1
    def __str__(self):
        if self.position < finish:
            return "{}{}{}|".format(" " * self.position , horse_char, " " * (10 - self.position))
        else:
            return "{}{}".format(" " * 11, horse_char)

def run():
    global horses
    global labels
    startbtn.pack_forget()
    restartbtn.config(state=DISABLED)
    for i in range(8):
        labels[i].config(text = horses[i])
    chosen_horse = random.randint(0, 7)
    horses[chosen_horse].forward()
    labels[chosen_horse].config(text = horses[chosen_horse])
    if horses[chosen_horse].position == finish:
        win_label.config(text = "Horse {} wins!".format(chosen_horse + 1))
        for i in range(8):
            horses[i] = Horse(0)
        restartbtn.pack(side=LEFT)
        restartbtn.config(state=NORMAL)
        quitbtn.pack(side=LEFT)
    else:
        root.after(100, run)

horses = []
for i in range(8):
    horses.append(Horse(0))

labels = []
for i in range(8):
    labels.append(Label(root, text = str(horses[i]), font = font_config))
    labels[i].pack()

startbtn = Button(root, text="Start", command=run)
restartbtn = Button(root, text="Restart", command=run)
quitbtn = Button(root, text="Quit", command=root.destroy)
win_label = Label(root, text="", font = font_config)
startbtn.pack()
win_label.pack()
root.mainloop()
