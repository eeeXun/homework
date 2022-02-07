from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys, random, math

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)
        self.valueIsSet = False

    def clickfoo(self):
        self.dataInit()
        self.monteCarlo()
        self.update()

    def dataInit(self):
        self.valueIsSet = True
        self.N = int(self.lineEdit.text())
        self.P = int(self.lineEdit_2.text())

    def monteCarlo(self):
        allPoint = [[random.uniform(0, 1), random.uniform(0, 1)]
                         for i in range(self.N)]
        counter = 0
        self.underPoint = []
        self.upperPoint = []
        for point in allPoint:
            if point[1] <= math.pow(point[0], self.P):
                counter += 1
                self.underPoint.append(point)
            else:
                self.upperPoint.append(point)
        Area = counter / self.N
        self.label_3.setText("面積大約為{}".format(Area))

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setFont(QFont("Monospace", 15))
        painter.setPen(Qt.white)
        painter.drawLine(600, 150, 1100, 150)
        painter.drawLine(600, 150, 600, 650)
        # draw Function
        if self.valueIsSet:
            for i in range(1000):
                tmp = i / 1000
                painter.drawPoint(600 + tmp * 500, 150 + math.pow(tmp, self.P) * 500)
            for point in self.underPoint:
                x = point[0]
                y = point[1]
                painter.drawPoint(600 + x * 500, 150 + y * 500)
            painter.setPen(Qt.red)
            for point in self.upperPoint:
                x = point[0]
                y = point[1]
                painter.drawPoint(600 + x * 500, 150 + y * 500)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
