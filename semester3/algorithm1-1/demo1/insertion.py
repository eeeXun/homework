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
        self.insertion_sort()
        self.label_1.setText(self.label_txt)
        self.label_1.setFont(QFont('txt',15))

    def getCount(self):
        for card in self.cards:
            self.count.append(suit[card[0]]+num[card[1:]])

    def insertion_sort(self):
        for i in range(1,len(self.cards)):
            key_count=self.count[i]
            key_card=self.cards[i]
            j=i-1
            while j>=0 and key_count>self.count[j]:
                self.count[j+1]=self.count[j]
                self.cards[j+1]=self.cards[j]
                j-=1
            self.count[j+1]=key_count
            self.cards[j+1]=key_card
            self.label_txt+='\n\n'+','.join(self.cards)


if __name__=='__main__':
    app=QApplication(sys.argv)
    window=Win()
    window.show()
    sys.exit(app.exec_())
