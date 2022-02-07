from UI import Ui_Frame
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QBrush, QFont
from PyQt5.QtCore import Qt, QRectF, QPoint, QRect
import sys

Ingredients = {"Salmon": {"size": 153, "value": 253}, "Tuna": {"size": 260, "value": 530},
               "Istiophoridae": {"size": 67, "value": 153}, "Fenneropenaeus": {"size": 93, "value": 196},
               "Borealis": {"size": 152, "value": 250}, "Adductor": {"size": 50, "value": 87},
               "Haliotis": {"size": 58, "value": 191}, "Gratilla": {"size": 13, "value": 33},
               "Kuroge": {"size": 166, "value": 431}, "Chionoecetes": {"size": 77, "value": 90},
               "Eriocheir": {"size": 151, "value": 180}, "Palinuridae": {"size": 60, "value": 100}}

class SubWin(QWidget):
    def __init__(self, considerings):
        super().__init__()
        self.setFixedSize(10000, 10000)
        self.considerings = considerings
        # print(self.considerings)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setFont(QFont("Monospace", 15))
        painter.setPen(Qt.white)
        # painter.drawText(QRectF(10, 10, 200, 20), "Fenneropenaeus")
        consider_x = 0
        consider_y = 0
        consider_height = 30
        item_x = -200
        item_y = 30
        item_width = 200
        item_height = 30
        tmp_count = 0
        for consider in self.considerings:
            consider_width = 15 * (len(consider) + 6)
            painter.drawText(QRectF(consider_x, consider_y, consider_width, consider_height),
                             "僅考慮 " + consider)
            for item in self.considerings[consider]:
                if tmp_count == 4:
                    tmp_count = 0
                    item_x = 0
                    item_y += 30
                    consider_y += 30
                else:
                    item_x += 200
                painter.drawRect(QRect(item_x, item_y, item_width, item_height))
                painter.drawText(QRectF(item_x, item_y, item_width, item_height), item)
                tmp_count += 1
            consider_y += 100
            item_x = -200
            item_y += 100
            tmp_count = 0

class Win(QMainWindow, Ui_Frame):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.clickfoo)
        self.considerings = {}
        self.best = []
        self.cost = []
        self.value = []
        self.resultMax = []

    def clickfoo(self):
        self.dataInit()
        self.knapsack()
        self.drawResult()
        self.drawMax()
        # print(self.considerings)

    def dataInit(self):
        self.totalSize = int(self.lineEdit.text())
        self.myItems = self.lineEdit_2.text().split(",")
        self.considerings = {}
        self.best = [""] * (self.totalSize + 1)
        self.cost = [0] * (self.totalSize + 1)
        self.value = [0] * (self.totalSize + 1)

    def knapsack(self):
        tmp_considering = ""
        for item in self.myItems:
            for bagSize in range(1, self.totalSize + 1):
                if bagSize - Ingredients[item]["size"] >= 0:
                    if self.cost[bagSize] < (self.cost[bagSize - Ingredients[item]["size"]] +
                                       Ingredients[item]["value"]):
                        self.cost[bagSize] = self.cost[bagSize - Ingredients[item]["size"]] + \
                            Ingredients[item]["value"]
                        self.best[bagSize] = item
            if len(self.considerings) == 0:
                tmp_considering = item
            else:
                tmp_considering += "、" + item
            self.considerings[tmp_considering] = self.getItem()
        self.resultMax = self.getItem()

    def getItem(self):
        tmp_cost = self.totalSize
        tmp_best = self.best[tmp_cost]
        result = []
        while tmp_cost > 0 and tmp_best != "":
            tmp_size = Ingredients[tmp_best]["size"]
            result.append(tmp_best)
            tmp_cost -= Ingredients[tmp_best]["size"]
            tmp_best = self.best[tmp_cost]
        return result

    def drawResult(self):
        subWin = SubWin(self.considerings)
        self.scrollArea.setWidget(subWin)

    def drawMax(self):
        tmp_max = {}
        tmp_value = 0
        for item in self.resultMax:
            if item not in tmp_max:
                tmp_max[item] = 1
            else:
                tmp_max[item] +=1
            tmp_value += Ingredients[item]["value"]
        tmp_label = "當胃容量大小為{}".format(self.totalSize)
        for item in tmp_max:
            tmp_label += ",拿{} {}個".format(item, tmp_max[item])
        tmp_label += ",得總價值 {}".format(tmp_value)
        self.label_3.setText(tmp_label)
        self.label_3.setFont(QFont("Monospace", 15))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Win()
    window.show()
    sys.exit(app.exec_())
