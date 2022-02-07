from module import Ui_Frame
from PyQt5.QtWidgets import QApplication,QMainWindow,QWidget
from PyQt5.QtGui import QFont
import sys

suit={'s':39,'h':26,'d':13,'c':0}
num={'A':13,'K':12,'Q':11,'J':10}
for i in range(10,1,-1):
    num['{}'.format(i)]=i-1

class Win(QMainWindow,Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.sort)
        self.cards=[]
        self.count=[]
        self.output=[]
        self.label_txt=''
    def sort(self):
        self.cards=self.lineEdit.text().split(',')
        self.count=[]
        self.label_txt=','.join(self.cards)
        self.getCount()
        self.selection_sort()
        self.label_1.setText(self.label_txt)
        self.label_1.setFont(QFont('txt',15))

    def getCount(self):
        for card in self.cards:
            self.count.append(suit[card[0]]+num[card[1:]])

    def selection_sort(self):
        for i in range(len(self.cards)):
            index_max=i
            for j in range(i+1,len(self.cards)):
                if self.count[index_max]<self.count[j]:
                    index_max=j
            self.count[i],self.count[index_max]=self.count[index_max],self.count[i]
            self.cards[i],self.cards[index_max]=self.cards[index_max],self.cards[i]
            self.label_txt+='\n\n'+','.join(self.cards)


if __name__=='__main__':
    app=QApplication(sys.argv)
    window=Win()
    window.show()
    sys.exit(app.exec_())
