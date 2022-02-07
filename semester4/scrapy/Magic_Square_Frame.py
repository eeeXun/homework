from tkinter import *
from tkinter import simpledialog

def packMagicSquare(square):
    for i in range(len(square)):
        frame = Frame(root)
        frame.pack()
        for j in square[i]:
            Label(frame, text=str(j), borderwidth=2, relief="raised").pack(side=LEFT)

def getMagicSquare(N):
    myData = [[[] for i in range(N)] for j in range(N)]
    now_x = N//2
    now_y = 0

    for i in range(1, N**2 + 1):
        myData[now_y][now_x] = i
        next_x = now_x + 1
        next_y = now_y - 1
        if next_x >= N:
            next_x = 0
        if next_y < 0:
            next_y = N - 1
        if myData[next_y][next_x]:
            next_x = now_x
            next_y = now_y + 1
        now_x, now_y = next_x, next_y

    return myData

root = Tk()
root.title("Magic Square")
N = simpledialog.askinteger("Input N", "Please input an odd number.")
if N%2 == 0:
    Label(root, text="Can't handle it! Please input old number").pack()
else:
    square = getMagicSquare(N)
    packMagicSquare(square)

root.mainloop()
