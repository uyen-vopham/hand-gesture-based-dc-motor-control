from matplotlib.figure import Figure
#from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PyQt5.QtCore import QObject
import time


class drawDB_UI():

    def __init__(self,screen1,screenDB_Dir):
        self.screen1 = screen1
        self.screenDB_Dir = screenDB_Dir

        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.screen1.addWidget(self.canvas)
        self.ax1 = self.figure.add_subplot(111,frame_on=False)

        self.figure_DR = Figure()
        self.canvas_DR = FigureCanvas(self.figure_DR)
        self.screenDB_Dir.addWidget(self.canvas_DR)
        self.ax2 = self.figure_DR.add_subplot(111,frame_on=False)
        
    def plot_graph(self,size_speed,size_dir):

        #self.figure.clear()
        #size_speed = size_speed; size_dir = size_dir

        self.ax1.clear()
        self.ax2.clear()

        labels = '<10', '>10';explode = (0,0)

        self.ax1.pie(size_speed,labels=labels, explode=explode,autopct='%1.1f%%', shadow=True, startangle=90)
        self.ax1.axis('equal') 


        #self.figure_DR.clear()
        labels_DR = 'FW', 'BW';explode_DR = (0, 0)
        self.ax2.pie(size_dir,labels=labels_DR, explode=explode_DR, autopct='%1.1f%%', shadow=True, startangle=90)
        self.ax2.axis('equal') 

        # Draw canvas
        self.canvas.draw(); self.canvas_DR.draw()


class PID_GRAPH(QObject):
    def __init__(self,screen):
        super(PID_GRAPH, self).__init__()
        self.screen = screen

    def initGraph(self):
        self.figure = Figure(); self.canvas = FigureCanvas(self.figure)
        self.screen.addWidget(self.canvas)
        self.ax = self.figure.add_subplot(111)

        self.num_display = 500;self.y_data_rp = [];self.y_data_sp = []
        self.line_rp, = self.ax.plot([], [], color='r',linewidth=1.5,label='FB')
        self.line_sp, = self.ax.plot([], [],color='b',linewidth=1.5,label='SP')
        self.ax.set_ylim(-20,100)
        self.ax.legend() # when use more properties in ax.plot we need to use to display

    def update_data(self,get_sp,get_rp):
        y_range = [-20, 100]
        self.y_data_rp.append(get_sp); self.y_data_sp.append(get_rp)
        if len(self.y_data_rp) > self.num_display:self.y_data_rp.pop(0)
        if len(self.y_data_sp) > self.num_display: self.y_data_sp.pop(0)
        num_points = min(self.num_display, len(self.y_data_rp))
        #print("testpoint: ", num_points)
        x_data = [time.time() - i * 0.001  for i in range(num_points)]
        

        self.line_rp.set_data(x_data, self.y_data_rp); self.line_sp.set_data(x_data, self.y_data_sp)
        self.ax.set_ylim(y_range)
        self.ax.relim()
        self.ax.autoscale_view()
        self.canvas.draw()