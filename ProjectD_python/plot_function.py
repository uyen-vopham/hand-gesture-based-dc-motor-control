from matplotlib.figure import Figure
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PyQt5.QtCore import QObject
import time

class PID_GRAPH(QObject):
    def __init__(self,screen):
        super(PID_GRAPH, self).__init__()
        self.screen = screen

    def initGraph(self):
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.screen.addWidget(self.canvas)
        self.ax = self.figure.add_subplot(111)
        self.num_display = 500;self.y_data_rp = [];self.y_data_sp = []
        self.line_rp, = self.ax.plot([], [], color='r',linewidth=1.5,label='FB')
        self.line_sp, = self.ax.plot([], [],color='b',linewidth=1.5,label='SP')

        self.ax.set_ylim(-20,100)
        self.ax.legend() # when use more properties in ax.plot we need to use to display

    def update_data(self,get_sp,get_rp):
        
        y_range = [-20, 100]
        self.y_data_rp.append(get_sp)
        self.y_data_sp.append(get_rp)

        if len(self.y_data_rp) > self.num_display:self.y_data_rp.pop(0)
        if len(self.y_data_sp) > self.num_display: self.y_data_sp.pop(0)
            
        num_points = min(self.num_display, len(self.y_data_rp))
        #print("testpoint: ", num_points)

        x_data = [time.time() - i * 0.01  for i in range(num_points)]
        #print("test x_data: ",x_data )

        self.line_rp.set_data(x_data, self.y_data_rp)
        self.line_sp.set_data(x_data, self.y_data_sp)

        self.ax.set_ylim(y_range)
        self.ax.relim()
        self.ax.autoscale_view()
        self.canvas.draw()