from tkinter import *

puzzle = [[" ", "1", "2"], ["3", "4", "5"], ["6", "7", "8"]]
empty = [0, 0] # Row, Column
arrowSet = ["↑", "↓", "←", "→",]
font_config = ("Monospace", 20, "bold")

root = Tk()
puzzleSet = [[Label(root) for i in range(3)] for j in range(3)]
for i in range(3):
    for j in range(3):
        puzzleSet[i][j].config(text=puzzle[i][j], font=font_config, borderwidth=2, relief="sunken")
        puzzleSet[i][j].grid(row=i, column=j)
upBtn = Button(root, text=arrowSet[0], font=font_config, command=lambda:move("up"))
upBtn.grid(row=3, column=1)
downBtn = Button(root, text=arrowSet[1], font=font_config, command=lambda:move("down"))
downBtn.grid(row=5, column=1)
leftBtn = Button(root, text=arrowSet[2], font=font_config, command=lambda:move("left"))
leftBtn.grid(row=4, column=0)
rightBtn = Button(root, text=arrowSet[3], font=font_config, command=lambda:move("right"))
rightBtn.grid(row=4, column=2)

def move(direction):
    tmpR = empty[0]
    tmpC = empty[1]
    if direction == "up":
        if tmpR != 2:
            puzzle[tmpR][tmpC] = puzzle[tmpR + 1][tmpC]
            puzzleSet[tmpR][tmpC]["text"] = puzzle[tmpR][tmpC]
            puzzle[tmpR + 1][tmpC] = " "
            puzzleSet[tmpR + 1][tmpC]["text"] = " "
            empty[:] = [tmpR + 1, tmpC]
    elif direction == "down":
        if tmpR != 0:
            puzzle[tmpR][tmpC] = puzzle[tmpR - 1][tmpC]
            puzzleSet[tmpR][tmpC]["text"] = puzzle[tmpR][tmpC]
            puzzle[tmpR - 1][tmpC] = " "
            puzzleSet[tmpR - 1][tmpC]["text"] = " "
            empty[:] = [tmpR - 1, tmpC]
    elif direction == "left":
        if tmpC != 2:
            puzzle[tmpR][tmpC] = puzzle[tmpR][tmpC + 1]
            puzzleSet[tmpR][tmpC]["text"] = puzzle[tmpR][tmpC]
            puzzle[tmpR][tmpC + 1] = " "
            puzzleSet[tmpR][tmpC + 1]["text"] = " "
            empty[:] = [tmpR, tmpC + 1]
    else:
        if tmpC != 0:
            puzzle[tmpR][tmpC] = puzzle[tmpR][tmpC - 1]
            puzzleSet[tmpR][tmpC]["text"] = puzzle[tmpR][tmpC]
            puzzle[tmpR][tmpC - 1] = " "
            puzzleSet[tmpR][tmpC - 1]["text"] = " "
            empty[:] = [tmpR, tmpC - 1]

root.mainloop()
