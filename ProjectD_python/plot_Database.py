from matplotlib.figure import Figure
#from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PyQt5.QtCore import QObject
import time

class drawPie ():
    def __init__(self, PieScreen, screenDB_Dir):
        self.PieScreen = PieScreen
        self.screenDB_Dir = screenDB_Dir

        self.figure_speed = Figure()
        self.canvas_speed = FigureCanvas(self.figure_speed)
        self.PieScreen.addWidget(self.canvas_speed)

        self.ax1 = self.figure_speed.add_subplot(111, frame_on = False)

        self.figure_dir = Figure()
        self.canvas_dir = FigureCanvas(self.figure_dir)
        self.screenDB_Dir.addWidget(self.canvas_dir)
        self.ax2 = self.figure_dir.add_subplot(111, frame_on = False)

    def plotGraph (self, Speed, Dir):
        self.ax1.clear()
        self.ax2.clear()
        label = ['Giá trị 1', 'Giá trị 2']; sizes = Speed; explode = (0, 0.1)
        print(sizes)
        self.ax1.pie(sizes,explode=explode,labels=label,autopct='%1.1f%%', shadow=True, startangle=90)
        self.ax1.axis('equal')

        label2 = 'For', 'Rev'; sizes2 = Dir; explode2 = (0, 0.1)
        self.ax2.pie(sizes2, explode=explode2,labels=label2,autopct='%1.1f%%', shadow=True, startangle=90)
        self.ax2.axis('equal')

        self.canvas_speed.draw()
        self.canvas_dir.draw()

