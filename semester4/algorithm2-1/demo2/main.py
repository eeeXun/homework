from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys

Ingredients = {"S": "Salmon", "T": "Tuna", "I": "Istiophoridae", "F": "Fenneropenaeus",
               "B": "Borealis", "A": "Adductor", "H": "Haliotis", "G": "Gratilla",
               "K": "Kuroge", "C": "Chionoecetes", "E": "Eriocheir", "P": "Palinuridae"}

class SubWin(QWidget):
    def __init__(self, myItems, cost):
        super().__init__()
        self.setFixedSize(10000, 10000)
        self.myItems = myItems
        self.cost = cost
        self.N = len(myItems)
        self.Index = {self.myItems[i]: self.myItems.index(self.myItems[i]) for i in range(self.N)}
        self.tree = self.buildTree()
        self.points = []
        self.lines = []
        self.setPoint()

    def buildTree(self):
        tree = []
        root = self.cost[1][self.N][1]
        index_root = self.Index[root]
        left = self.myItems[0: index_root]
        right = self.myItems[index_root + 1: self.N + 1]
        self.buildTreeHelper(left, right)
        tree = [root, left, right]
        return tree

    def buildTreeHelper(self, left, right):
        if left == []:
            left[:] = [None]
        else:
            tmp_row = self.Index[left[0]] + 1
            tmp_column = self.Index[left[-1]] + 1
            root = self.cost[tmp_row][tmp_column][1]
            index_root = left.index(root)
            tmp_left = left[0: index_root]
            tmp_right = left[index_root + 1: self.N + 1]
            left[:] = [root, tmp_left, tmp_right]
            self.buildTreeHelper(tmp_left, tmp_right)
        if right == []:
            right[:] = [None]
        else:
            tmp_row = self.Index[right[0]] + 1
            tmp_column = self.Index[right[-1]] + 1
            root = self.cost[tmp_row][tmp_column][1]
            index_root = right.index(root)
            tmp_left = right[0: index_root]
            tmp_right = right[index_root + 1: self.N + 1]
            self.buildTreeHelper(tmp_left, tmp_right)
            right[:] = [root, tmp_left, tmp_right]

    def setPoint(self):
        root = self.tree[0]
        left = self.tree[1]
        right = self.tree[2]
        x = 500
        y = 1000
        rx = 150
        self.points = []
        self.points.append([QRect(x, y, 200, 20), QRectF(x, y, 200, 20), Ingredients[root]])
        self.lines = []
        if left[0]:
            self.lines.append([x + 200 / 2, y + 20, x + 200 / 2 - rx, y + 50])
        if right[0]:
            self.lines.append([x + 200 / 2, y + 20, x + 200 / 2 + rx, y + 50])
        self.setPointHelper(left, x - rx, y + 50, rx / 2)
        self.setPointHelper(right, x + rx, y + 50, rx / 2)

    def setPointHelper(self, tmp_list, x, y, rx):
        root = tmp_list[0]
        if not root:
            return
        else:
            left = tmp_list[1]
            right = tmp_list[2]
            self.points.append([QRect(x, y, 200, 20), QRectF(x, y, 200, 20), Ingredients[root]])
            if left[0]:
                self.lines.append([x + 200 / 2, y + 20, x + 200 / 2 - rx, y + 50])
            if right[0]:
                self.lines.append([x + 200 / 2, y + 20, x + 200 / 2 + rx, y + 50])
            self.setPointHelper(left, x - rx, y + 50, rx)
            self.setPointHelper(right, x + rx, y + 50, rx)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setFont(QFont("Monospace", 15))
        painter.setPen(Qt.white)
        # table
        tmp_count = 1
        item_width = 200
        item_height = 20
        for i in range(self.N + 1):
            for j in range(self.N + 1):
                painter.drawRect(QRect(0 + item_width * j, 0 + item_height * i,
                                       item_width, item_height))
        for item in self.myItems:
            painter.drawText(QRectF(tmp_count * item_width, 0, item_width, item_height),
                             Ingredients[item])
            painter.drawText(QRectF(0, tmp_count * item_height, item_width, item_height),
                             Ingredients[item])
            tmp_count += 1
        for i in range(1, self.N + 1):
            for j in range(i, self.N + 1):
                painter.drawText(QRectF(j * item_width,
                                        i * item_height,
                                        item_width, item_height),
                                 str(self.cost[i][j][0]) + self.cost[i][j][1])
        # table
        # graph
        for point in self.points:
            painter.drawRect(point[0])
            painter.drawText(point[1], point[2])
        for line in self.lines:
            painter.drawLine(line[0], line[1], line[2], line[3])
        # graph

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)
        self.myItems = []
        self.myFreq = []
        self.N = 0
        self.cost = []

    def clickfoo(self):
        self.dataInit()
        self.optimalSearch()
        self.drawOutput()

    def dataInit(self):
        self.myItems = list(self.lineEdit.text())
        self.myFreq = [int(i) for i in self.lineEdit_2.text().split(",")]
        self.N = len(self.myItems)
        self.cost = [[[sys.maxsize, ""] for x in range(self.N + 2)] for y in range(self.N + 2)]

    def optimalSearch(self):
        for i in range(1, self.N + 1):
            self.cost[i][i] = [self.myFreq[i - 1], self.myItems[i - 1]]
        for i in range(1, self.N + 2):
            self.cost[i][i -1] = [0, ""]
        for j in range(1, self.N):
            for i in range(1, self.N - j + 1):
                for k in range(1, i + j + 1):
                    tmp = self.cost[i][k - 1][0] + self.cost[k + 1][i + j][0]
                    if tmp < self.cost[i][i + j][0]:
                        self.cost[i][i + j] = [tmp, self.myItems[k - 1]]
                tmp = 0
                for k in range(i, i + j + 1):
                    tmp += self.myFreq[k - 1]
                self.cost[i][i + j][0] += tmp

    def drawOutput(self):
        subWin = SubWin(self.myItems, self.cost)
        self.scrollArea.setWidget(subWin)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
