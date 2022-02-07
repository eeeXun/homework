from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys
from math import sin, cos, pi

center_X = 400
center_Y = 400
Rx = 200
Ry = 200
rx = 20
ry = 20

class SubWin(QWidget):
    def __init__(self, myShops, allPaths, myPaths):
        super().__init__()
        self.setFixedSize(10000, 10000)
        self.myShops = myShops
        self.allPaths = allPaths
        self.myPaths = myPaths
        self.N = len(self.myShops)
        self.shop_Points = {}
        self.setPoint()

    def setPoint(self):
        for i in range(self.N):
            self.shop_Points[self.myShops[i]] = [center_X + Rx * cos(2 * pi * (i / self.N)),
                                                 center_Y + Ry * sin(2 * pi * (i / self.N))]

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setFont(QFont("Monospace", 15))
        painter.setPen(Qt.white)
        # draw Algorithm
        shiftY = 500
        for i in range(len(self.myPaths) + 1):
            painter.setPen(Qt.white)
            for path in self.allPaths:
                startShop = path[0]
                endShop = path[1]
                startX = self.shop_Points[startShop][0]
                startY = self.shop_Points[startShop][1] + (i) * shiftY
                endX = self.shop_Points[endShop][0]
                endY = self.shop_Points[endShop][1] + (i) * shiftY
                painter.drawLine(startX, startY, endX, endY)
                # painter.drawText(QRectF((startX + endX) / 2,
                #                         (startY + endY) / 2,
                #                         rx, ry), str(path[2]))
                painter.drawText(QRectF(startX / 3 + 2 * endX / 3,
                                       startY / 3 + 2 * endY / 3,
                                       rx, ry), str(path[2]))
            for shop in self.shop_Points:
                tmp_centerX = self.shop_Points[shop][0]
                tmp_centerY = self.shop_Points[shop][1] + (i) * shiftY
                painter.drawEllipse(QPoint(tmp_centerX, tmp_centerY), rx, ry)
                painter.drawText(QRectF(tmp_centerX - rx, tmp_centerY - ry, 2 * rx, 2 * ry),
                                 Qt.AlignCenter, shop)
            painter.setPen(Qt.red)
            for j in range(i):
                startShop = self.myPaths[j][0]
                endShop = self.myPaths[j][1]
                startX = self.shop_Points[startShop][0]
                startY = self.shop_Points[startShop][1] + (i) * shiftY
                endX = self.shop_Points[endShop][0]
                endY = self.shop_Points[endShop][1] + (i) * shiftY
                painter.drawLine(startX, startY, endX, endY)

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)
        self.myShops = []
        self.allPaths = []
        self.visited = []
        self.myPaths = []

    def clickfoo(self):
        self.dataInit()
        self.prime()
        self.drawOutput()

    def dataInit(self):
        self.myShops = list(self.lineEdit.text())
        self.allPaths = [[i[1], i[3], int(i[5])] for i in self.lineEdit_2.text().split()]
        self.myPaths = []

    def prime(self):
        self.visited = ["A"]
        while len(self.visited) < len(self.myShops):
            searchingPaths = []
            minPath = ["", "", sys.maxsize]
            for path in self.allPaths:
                if self.XORvisited(path[0], path[1]):
                    searchingPaths.append(path)
            for path in searchingPaths:
                if path[2] < minPath[2]:
                    minPath = path
            self.myPaths.append(minPath)
            if minPath[0] in self.visited:
                self.visited.append(minPath[1])
            else:
                self.visited.append(minPath[0])

    def XORvisited(self, a, b):
        if (a in self.visited and b not in self.visited) or \
                (a not in self.visited and b in self.visited):
            return True
        else:
            return False

    def drawOutput(self):
        subWin = SubWin(self.myShops, self.allPaths, self.myPaths)
        self.scrollArea.setWidget(subWin)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
