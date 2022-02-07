from tkinter import *
import random

horse_char = "~/-\\^"
finish = 11
font_config = ("Monospace", 20, "bold")

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

root = Tk()

horses = []
for i in range(8):
    horses.append(Horse(0))

labels = []
for i in range(8):
    labels.append(Label(root, text = str(horses[i]), font = font_config))
    labels[i].pack()

def run():
    chosen_horse = random.randint(0, 7)
    horses[chosen_horse].forward()
    labels[chosen_horse].config(text = horses[chosen_horse])
    if horses[chosen_horse].position == finish:
        win_label.config(text = "Horse {} wins!".format(chosen_horse + 1))
    else:
        root.after(100, run)

win_label = Label(root, text="", font = font_config)
win_label.pack()

root.after(100, run)
root.mainloop()
