# -*- coding: utf-8 -*-
import serial, serial.tools.list_ports

from PyQt5.QtWidgets import QApplication, QMainWindow,QPushButton
from PyQt5.QtCore import pyqtSignal
from PyQt5 import uic
from PyQt5.QtGui import QPixmap
from threading import Thread, Event
from webcam import webcam_thread
import time   ,sys
from collections import Counter
from function import PID_GRAPH,drawDB_UI
from database import DatabaseMotor
from exportData import DataExport

class MainUI(QMainWindow):
    data_available = pyqtSignal(str)
    def __init__(self):
        super(MainUI, self).__init__()
        uic.loadUi("main_window.ui", self)

        self.setpoint_qt.setText(str(0));self.feedback_qt.setText(str(0))

        self.dbMotor = DatabaseMotor(); #self.dbMotor.delete_data()
        self.start_time = time.time(); self.starttime_readDB = time.time() 

        self.speed_db = 0; self.dir_db = str(0); self.getdataDB = 0; self.getSpeedCol = []; self.getDisCol = []; self.counts_dir = {0: 0, 1: 0} 
        
        self.plot_UI = PID_GRAPH(self.screen)
        self.plot_UI.initGraph()

        self.plotDB = drawDB_UI(self.screen1,self.screenDB_Dir)

        self.WebcamThread = webcam_thread(self.camera); self.WebcamThread.start()
        self.WebcamThread.frame_ready.connect(self.WebcamThread.update_frame); self.WebcamThread.handPose.connect(self.detectHand)
        

        self.exportPDF = DataExport();
       
        self.data_available.connect(self.update_view)
        self.thread = None
        self.alive = Event()

        self.stop_requested = False
        self.thread_db = None
        self.alive_db = Event()

    
        self.serialPort = serial.Serial()
        self.serialPort.timeout = 0.5
        self.baudList = {'9600': 9600, '19200': 19200,'115200': 115200}
        self.cbbBaud.addItems(self.baudList)
     
        self.portList = []
        self.listing_port()
        self.pixmap_list = [QPixmap('images/m_on.png'), QPixmap('images/m_off.png'), QPixmap('images/blue_light.png'),
        QPixmap('images/red_light.png'), QPixmap('images/black_light.png'), QPixmap('images/Closed_Fist.png'), 
        QPixmap('images/Open_Palm.png'), QPixmap('images/Thumb_Up.png'), QPixmap('images/Thumb_Down.png'),
        QPixmap('images/Motor_Fw.png'), QPixmap('images/Motor_Rv.png'), QPixmap('images/nothing.png') ]

        self.lb_Motor.setPixmap(self.pixmap_list[1])
        self.blue_light.setPixmap(self.pixmap_list[4])
        self.red_light.setPixmap(self.pixmap_list[4])

        self.cbbPort.addItems(self.portList)
        self.cbbPort.currentIndexChanged.connect(self.listing_port)
        self.btnUpdate.clicked.connect(self.update_port)
        self.btnConnect.clicked.connect(self.connect_serial)
        self.btn_Start.clicked.connect(self.motor_ON)
        self.btn_Stop.clicked.connect(self.motor_OFF)
        self.setpoint_qt.returnPressed.connect(self.sendSP)
        self.btnExit.clicked.connect(self.closeWindow)
        self.btnDatabase.clicked.connect(self.start_DBThread)
        self.btn_export.clicked.connect(self.converPDF)

    
        # self.motor_display()
        self.btn_Start = 0; self.btn_Stop = 0

        #data python gửi đi---------------------------------
        self.rx_data_array = []
        self.SP = 0; self.motor_ = 0; self.dir = 1; self.btn_ui = 0
        self.count_motor = 0;  self.SP = 0 #1.9,1.7,0.08
        self.Data_ARM = []

        #data nhận từ STM------------------------------------
        self.speed_current = 0;self.led_statusSTM = 0;self.btn_statusSTM = 0
        self.dbGroupBox.setVisible(False)

    def converPDF(self):
        data = self.dbMotor.read_dataFull()
        self.exportPDF.create_pdf(data, 'projectD.pdf')
        self.exportPDF.export_data_to_csv(data, 'projectD.csv')
    
    def call_DB(self):

        self.dbGroupBox.setVisible(not self.dbGroupBox.isVisible())
        while not self.stop_requested:
            
            current_time = time.time()
            if current_time - self.start_time >= 3:
                self.start_time = current_time
                self.speed_db = float(self.speed_current); self.dir_db = str(self.dir)
                #self.speed_db = float(20.5); self.dir_db = str(1)
                self.dbMotor.insert_data(self.speed_db, self.dir_db)
        
            if current_time - self.starttime_readDB > 5:
                self.starttime_readDB = current_time
                data  = self.dbMotor.read_data_day()
                self.getSpeedCol.clear() ;self.getDisCol.clear()   
                for row in data:
                    getSpeed = row[0];getdir = row[1]
                    self.getSpeedCol.append(getSpeed);self.getDisCol.append(int(getdir))
                self.frequency_speed = Counter(self.getSpeedCol);               
                speed_under_10 = sum(count for value, count in self.frequency_speed.items() if value < 10)
                count_upper_10 = sum(count for value, count in self.frequency_speed.items() if value > 10)
                size_speed = [speed_under_10,count_upper_10]
                #print("size_speed",size_speed)
                self.counts_dir = {1: 0, -1: 0}
                for value in self.getDisCol:
                    self.counts_dir[value] += 1
                size_dir = [self.counts_dir[1], self.counts_dir[-1]] 
          
                self.plotDB.plot_graph(size_speed,size_dir)

            time.sleep(0.5)

    def start_DBThread(self):
        try:
            if (self.btnDatabase.isChecked()):
                self.start_threadFB()
                print("Checked")
            else:
                self.dbGroupBox.setVisible(not self.dbGroupBox.isVisible())
                self.stop_threadDB()
                print("UnChecked")
        except KeyboardInterrupt:
            print("Interrupted Thread")

    def start_threadFB(self):
        self.thread_db = Thread(target = self.call_DB)
        self.thread_db.setDaemon(1)
        self.alive_db.set()
        self.stop_requested = False
        self.thread_db.start()

    def stop_threadDB(self):
        if(self.thread_db is not None):
            self.stop_requested = True
            #self.dbMotor.close()
            self.alive_db.clear()
            self.thread_db.join()
            self.thread_db = None
    
    def listing_port(self):
        self.portList = [port.device for port in serial.tools.list_ports.comports()]
        selected_COM = self.cbbPort.currentText()
        print(self.portList)
        print("Selected COM: ",selected_COM )

    def update_port(self):
        self.listing_port()
        self.cbbPort.clear()
        self.cbbPort.addItems(self.portList)

    def connect_serial (self):
        if (self.btnConnect.isChecked()):
            port = self.cbbPort.currentText()
            baud = self.cbbBaud.currentText()
            print(port, '', baud)
            self.serialPort.port = port
            self.serialPort.baudrate = baud
            self.check_serial()

            if(self.serialPort.is_open):
                self.btnConnect.setText("Disconnect")
                self.btnConnect.setStyleSheet("background-color: #00FF00;font-weight: bold;font-size: 10pt")
        else:
            self.disconnect_serial()
            self.btnConnect.setText("Connect")
            self.btnConnect.setStyleSheet("background-color: #FF0000;font-weight: bold;font-size: 10pt")

    def check_serial(self):
        try:
            self.serialPort.open()
            if(self.serialPort.is_open):
                self.start_thread()
                print("Kết nối thành công")
        except:
            print('Chưa kết nối được')  
        
    def start_thread(self):
        self.thread = Thread(target = self.read_serial)
        self.thread.setDaemon(1)
        self.alive.set()
        self.thread.start()
    def stop_thread(self):
        if(self.thread is not None):
            self.alive.clear()
            self.thread.join()
            self.thread = None
    def read_serial(self):
        while(self.alive.isSet() and self.serialPort.is_open):
            data_rx = self.serialPort.readline().decode("utf-8").strip()
            #print("data_rx: ", data_rx)
            if(len(data_rx)>1):
                self.data_available.emit(data_rx)
    def prepare_data(self,data):
        if(self.serialPort.is_open):
            messages = str(data) + "\n"
            self.serialPort.write(messages.encode ())
    def start_send (self):    
            datasend = '1'
            self.serialPort.write(datasend.encode())
    def disconnect_serial(self):
        self.stop_thread()
        self.serialPort.close()

    def update_view(self, data_rx): #đọc data rx về và hiện data lên qt designer
        
        self.rx_data_array = data_rx.split(',')
        #print("Test data: ",data_rx )
        self.speed_current = (self.rx_data_array[0])

        self.btn_statusSTM = int(self.rx_data_array[1])
        if (self.rx_data_array[2] == '0'): # RUN
            self.red_light.setPixmap(self.pixmap_list[3]) # redlight ON
            self.blue_light.setPixmap(self.pixmap_list[4]) # blue light OFF
        elif (self.rx_data_array[2] == '1'): # OFF
            self.red_light.setPixmap(self.pixmap_list[4])
            self.blue_light.setPixmap(self.pixmap_list[2])

        self.feedback_qt.setText(self.speed_current)

        self.plot_UI.update_data(self.SP, float(self.speed_current))
   
    def sendData2STM (self, sp, btn_motor, motor, direction):
        datasend2STM = str(sp) + ',' + str(btn_motor) + ',' + str(motor) + ',' + str(direction) 
        return datasend2STM

    def sendSP(self):
        self.SP = int(self.setpoint_qt.text())
        self.Data_ARM = self.sendData2STM(self.SP, self.btn_ui, self.motor_, self.dir) 
        self.prepare_data(self.Data_ARM )

    def motor_OFF(self):
        self.btn_ui = 0
       
        self.btn.setText(str(self.btn_ui))
        self.lbMotor_State.setText("Stopped")
        if (self.btn_ui == 0):
            self.lb_Motor.setPixmap(self.pixmap_list[1])
            self.Data_ARM = self.sendData2STM(self.SP, self.btn_ui, self.motor_, self.dir)
            # self.Data_ARM = str(self.btn_ui)
            self.prepare_data(self.Data_ARM )

    def motor_ON(self):
        self.btn_ui = 1
        self.lbMotor_State.setText("Enabled")

        self.btn.setText(str(self.btn_ui))
        #print("count: ",self.count_motor)
        if (self.btn_ui == 1):
            self.lb_Motor.setPixmap(self.pixmap_list[0])
            self.Data_ARM = self.sendData2STM(self.SP, self.btn_ui, self.motor_, self.dir)
            self.prepare_data(self.Data_ARM )

    def detectHand (self, hand): #detect ban tay va tra ve hinh dang qua so, 0:five,1:close-fit, 2:thumb up, 3:thumb down 
        hand = int(hand)
        if hand == 0:
            self.motor_ = 0
            self.hand_display.setPixmap(self.pixmap_list[6])
        elif hand == 1:
            self.motor_ = 1
            self.hand_display.setPixmap(self.pixmap_list[5])
        elif hand == 2:
            self.dir = 1
            self.hand_display.setPixmap(self.pixmap_list[7])
            self.motor_run_qt.setPixmap(self.pixmap_list[9])
        elif hand == 3:
            self.dir = -1
            self.hand_display.setPixmap(self.pixmap_list[8])
            self.motor_run_qt.setPixmap(self.pixmap_list[10])
        
        if self.btn_ui == 1 and self.motor_ == 1:
            self.lbMotor_State.setText("Running")
        elif self.btn_ui == 1 and self.motor_ == 0:
            self.lbMotor_State.setText("Enabled")
        else:
            self.lbMotor_State.setText("Stopped")

        #self.sendData2STM(self.SP, self.btn_ui, self.motor_, self.dir)
        self.Data_ARM = self.sendData2STM(self.SP, self.btn_ui, self.motor_, self.dir) #gửi đi
        self.prepare_data(self.Data_ARM )
        #print('direction: ',self.dir)
        send = str(self.motor_) + ',' + str(self.dir)
        self.uyenvidai.setText(send)
    def closeWindow(self):
        mainUI.close()


if __name__ == "__main__":
    app = QApplication([sys.argv])
    mainUI = MainUI()
    mainUI.show()
    app.exec_()
    
