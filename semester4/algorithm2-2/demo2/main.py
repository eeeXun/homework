from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys

class SubWin(QWidget):
    def __init__(self, startPoint, allPoint, process, including):
        super().__init__()
        self.setFixedSize(10000, 10000)
        self.startPoint = startPoint
        self.allPoint = allPoint
        self.process = process
        self.including = including

    def textPoints(self, n):
        return [0, 60 * n, 150, 20]

    def columnPoints(self, i, j, k):
        return [150 * k, 60 * i + 20 * (j + 1), 150, 20]
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setFont(QFont("Monospace", 15))
        painter.setPen(Qt.white)
        # draw init & include
        painter.drawText(QRectF(*self.textPoints(0)), "Initial")
        for i in range(len(self.including)):
            painter.drawText(QRectF(*self.textPoints(i + 1)), "Including " + self.including[i])
        # draw process
        for i in range(len(self.process)):
            for j in range(2):
                for k in range(len(self.allPoint) + 1):
                    tmpPoint = self.columnPoints(i, j, k)
                    painter.drawRect(*tmpPoint)
                    # draw start point
                    if j == 1 and k == 0:
                        painter.drawText(QRectF(*tmpPoint), self.startPoint)
                    # draw allPoint
                    if j == 0 and k >= 1:
                        painter.drawText(QRectF(*tmpPoint), self.allPoint[k - 1])
                    # draw process
                    if j == 1 and k >= 1:
                        painter.drawText(QRectF(*tmpPoint), str(self.process[i][k - 1]))

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)

    def clickfoo(self):
        self.dataInit()
        self.dijkstra()
        self.drawOutput()

    def dataInit(self):
        self.startPoint = self.lineEdit.text()
        self.allPoint = [self.startPoint]
        allPath = [i.split(" ") for i in self.lineEdit_2.text().split(",")]
        tmpSet = set()
        for path in allPath:
            tmpSet.add(path[0])
            tmpSet.add(path[1])
        for i in tmpSet:
            if i != self.startPoint:
                self.allPoint.append(i)
        self.N = len(self.allPoint)
        self.Index = {self.allPoint[i]: self.allPoint.index(self.allPoint[i]) for i in range(self.N)}
        self.cost = [[9999 for i in range(self.N)] for j in range(self.N)]
        for i in range(self.N):
            self.cost[i][i] = 0
        for path in allPath:
            self.cost[self.Index[path[0]]][self.Index[path[1]]] = int(path[2])
            self.cost[self.Index[path[1]]][self.Index[path[0]]] = int(path[2])
        self.visited = [False] * (self.N)

    def findMin(self):
        minCost = 9999
        minIndex = 0
        for i in range(1, self.N):
            if not self.visited[i] and self.cost[0][i] < minCost:
                minCost = self.cost[0][i]
                minIndex = i
        return minIndex, minCost

    def dijkstra(self):
        self.process = [self.cost[0][:]]
        self.visited[0] = True
        self.including = []
        for i in range(self.N - 1):
            minIndex, minCost = self.findMin()
            costFromStartToMin = [minCost + self.cost[minIndex][j]
                                  for j in range(self.N)]
            for j in range(self.N):
                if costFromStartToMin[j] < self.cost[0][j]:
                    self.cost[0][j] = costFromStartToMin[j]
            self.including.append(self.allPoint[minIndex])
            self.process.append(self.cost[0][:])
            self.visited[minIndex] = True

    def drawOutput(self):
        subWin = SubWin(self.startPoint, self.allPoint, self.process, self.including)
        self.scrollArea.setWidget(subWin)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
