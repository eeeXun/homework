from b2 import Ui_Frame
from PyQt5.QtWidgets import QApplication,QMainWindow,QWidget
from PyQt5.QtGui import QFont
from PyQt5.QtGui import QPainter,QBrush
from PyQt5.QtCore import Qt,QRectF,QPoint
import sys

class draw_circle(QWidget):
    def __init__(self,circles_point,circles_list):
        super().__init__()
        self.setFixedSize(10000,10000)
        self.circles_point=circles_point
        self.circles_list=circles_list
    def paintEvent(self,event):
        painter=QPainter(self)
        painter.setBrush(Qt.cyan)
        for i in self.circles_point:
            painter.drawEllipse(i[0],i[1],i[2])

        painter.setPen(Qt.black)
        painter.setFont(QFont('txt',15))
        for i in range(len(self.circles_list)):
            for j in range(len(self.circles_list[i])):
                painter.drawText(QRectF(200*j,20+200*i,100,100),Qt.AlignCenter,str(self.circles_list[i][j]))

class Win(QMainWindow,Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.sort)
        # self.bub=[]
        self.circles_list=[]
        self.circles_point=[]
        self.txt=[]

    def sort(self):
        self.bub=[]
        self.getTextList()
        self.circles_list=[]
        self.getBubList()
        self.bubble_sort()
        self.circles_point=[]
        self.setPoint()
        self.draw()

    def getTextList(self):
        tmp=self.lineEdit.text().split(',')
        for i in tmp:
            self.bub.append(int(i))

    def getBubList(self):
        self.circles_list.append([])
        for i in self.bub:
            self.circles_list[len(self.circles_list)-1].append(i)

    def bubble_sort(self):
        for i in range(len(self.bub)-1,-1,-1):
            for j in range(i):
                if self.bub[j]<self.bub[j+1]:
                    self.bub[j],self.bub[j+1]=self.bub[j+1],self.bub[j]
                    self.getBubList()

    def setPoint(self):
        for i in range(len(self.circles_list)):
            for j in range(len(self.circles_list[i])):
                self.circles_point.append([QPoint(50+200*j,70+200*i),self.circles_list[i][j]*8,self.circles_list[i][j]*8])
        self.update()

    def draw(self):
        cir=draw_circle(self.circles_point,self.circles_list)
        self.scrollArea.setWidget(cir)


if __name__=='__main__':
    app=QApplication(sys.argv)
    window=Win()
    window.show()
    sys.exit(app.exec_())
