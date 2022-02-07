from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)

    def clickfoo(self):
        self.dataInit()
        self.matrixChain()
        self.resultMatrix = self.buildMatrix(0, self.N - 1)
        self.drawResult()

    def dataInit(self):
        self.matrix = list(self.lineEdit.text())
        tmp =  [i.split("*") for i in self.lineEdit_2.text().split(",")]
        self.r = [int(i[0]) for i in tmp]
        self.r.append(int(tmp[-1][1]))
        self.N = len(self.matrix)
        self.Index = {self.matrix[i]: self.matrix.index(self.matrix[i]) for i in range(self.N)}
        self.cost = [[[sys.maxsize, ""] for x in range(self.N)] for y in range(self.N)]

    def matrixChain(self):
        for i in range(self.N):
            self.cost[i][i] = [0, self.matrix[i]]
        for j in range(1, self.N):
            for i in range(self.N - j):
                for k in range(i + 1, i + j + 1):
                    tmp = self.cost[i][k - 1][0] + self.cost[k][i + j][0] + \
                        self.r[i] * self.r[k] * self.r[i + j + 1]
                    if(tmp < self.cost[i][i + j][0]):
                        self.cost[i][i + j] = [tmp, self.matrix[k]]

    def buildMatrix(self, start, end):
        if start == end:
            return self.matrix[start]
        elif (start - end) == 1:
            return [self.matrix[start], self.matrix[end]]
        else:
            index_root = self.Index[self.cost[start][end][1]]
            leftNode = [start, index_root - 1]
            rightNode = [index_root, end]
            leftMatrix = self.buildMatrix(*leftNode)
            rightMatrix = self.buildMatrix(*rightNode)
            return [leftMatrix, rightMatrix]

    def drawResult(self):
        resultTimes = "矩陣相乘次數最小值:" + str(self.cost[0][self.N -1 ][0]) + " 次"
        self.label_4.setText(resultTimes)
        resultStr = self.strProcess(str(self.resultMatrix[0]) + str(self.resultMatrix[1]))
        self.label_3.setText(resultStr)

    def strProcess(self, s):
        keeping = ["[", "]", ",", "'", " "]
        replacement = ["(", ")", "", "", ""]
        for i in range(5):
            s = s.replace(keeping[i], replacement[i])
        return s

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
