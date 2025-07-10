from PyQt5.QtCore import QThread, pyqtSignal, pyqtSlot
from PyQt5.QtGui import QFont,QPixmap,QImage
import cv2
import mediapipe as mp
import numpy as np
import time
from math_uyen import uyenMath
class webcam_thread (QThread):
    frame_ready = pyqtSignal(QImage)
    handPose = pyqtSignal(str)
    def __init__(self,camera):
        super(webcam_thread,self).__init__()
        self.start_time = time.time()
        self.frame_rate = 0
        self.frame_count = 0
        self.A = 0
        self.B = 0
        self.C = 0
        self.D = 0
        self.E = 0
        self.F = 0
        self.G = 0
        self.H = 0
        self.I = 0
        self.K = 0
        self.mp_drawing = mp.solutions.drawing_utils
        self.mp_hands = mp.solutions.hands
        self.math = uyenMath()
        self.point_0 = 0
        self.point_4 = 0
        self.shapeHand = 0
        self.camera = camera
    def run(self):
        # gesture = mp.solutions.gesture.Gesture()
        cap = cv2.VideoCapture(0)
        with self.mp_hands.Hands(min_detection_confidence = 0.8, min_tracking_confidence = 0.5) as hands:
            while cap.isOpened():
                ret, frame = cap.read()
                if ret:
                    self.frame_count += 1
                    elapsed_time = time.time() - self.start_time
                    if elapsed_time >= 1.0:
                        self.frame_rate = self.frame_count / elapsed_time
                        self.frame_count = 0
                        self.start_time = time.time()
                        print("Frame rate:", self.frame_rate)

                    rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                    rgb_image = cv2.flip(rgb_image, 1)
                    rgb_image.flags.writeable = False
                    result = hands.process(rgb_image)
                    rgb_image.flags.writeable = True

                    # rgb_image = cv2.cvtColor(rgb_image, cv2.COLOR_RGB2BGR)
                    # gesture_results = gesture.process(rgb_image)
                    if result.multi_hand_landmarks:
                        for num, hand in enumerate(result.multi_hand_landmarks):
                            self.mp_drawing.draw_landmarks(rgb_image, hand, self.mp_hands.HAND_CONNECTIONS)
                    
                            for idx, landmark in enumerate(hand.landmark):
                                x = landmark.x
                                y = landmark.y
                                z = landmark.z
                                keypoint_id = self.mp_hands.HandLandmark(idx).value
                                # print(f"Keypoint {keypoint_id} - x: {x}, y: {y}, z: {z}")
                                # print(type(keypoint_id))
                                #keypoint 0
                                self.point_0 = np.array([hand.landmark[0].x, hand.landmark[0].y, hand.landmark[0].z ])
                                #keypoint_id == 1:
                                point_1 = np.array([hand.landmark[1].x, hand.landmark[1].y, hand.landmark[1].z ])
                                #keypoint_id == 2:
                                point_2 = np.array([hand.landmark[2].x, hand.landmark[2].y, hand.landmark[2].z ])
                                # #keypoint_id == 3:
                                point_3 = np.array([hand.landmark[3].x, hand.landmark[3].y, hand.landmark[3].z ])
                                # #keypoint_id == 4:
                                self.point_4 = np.array([hand.landmark[4].x, hand.landmark[4].y, hand.landmark[4].z ])
                                # print('point4', self.point_4)
                                # #keypoint_id == 5:
                                point_5 = np.array([hand.landmark[5].x, hand.landmark[5].y, hand.landmark[5].z ])
                                # #keypoint_id == 6:
                                point_6 = np.array([hand.landmark[6].x, hand.landmark[6].y, hand.landmark[6].z ])
                                # #keypoint_id == 7:
                                point_7 = np.array([hand.landmark[7].x, hand.landmark[7].y, hand.landmark[7].z ])
                                # #keypoint_id == 8:
                                point_8 = np.array([hand.landmark[8].x, hand.landmark[8].y, hand.landmark[8].z ])
                                # #keypoint_id == 9:
                                point_9 = np.array([hand.landmark[9].x, hand.landmark[9].y, hand.landmark[9].z ])
                                # #keypoint_id == 10:
                                point_10 = np.array([hand.landmark[10].x, hand.landmark[10].y, hand.landmark[10].z ])
                                # #keypoint_id == 11:
                                point_11 = np.array([hand.landmark[11].x, hand.landmark[11].y, hand.landmark[11].z ])
                                # #keypoint_id == 12:
                                point_12 = np.array([hand.landmark[12].x, hand.landmark[12].y, hand.landmark[12].z ])
                                # #keypoint_id == 13:
                                point_13 = np.array([hand.landmark[13].x, hand.landmark[13].y, hand.landmark[13].z ])
                                # #keypoint_id == 14:
                                point_14 = np.array([hand.landmark[14].x, hand.landmark[14].y, hand.landmark[14].z ])
                                # #keypoint_id == 15:
                                point_15 = np.array([hand.landmark[15].x, hand.landmark[15].y, hand.landmark[15].z ])
                                # #keypoint_id == 16:
                                point_16 = np.array([hand.landmark[16].x, hand.landmark[16].y, hand.landmark[16].z ])
                                # #keypoint_id == 17:
                                point_17 = np.array([hand.landmark[17].x, hand.landmark[17].y, hand.landmark[17].z ])
                                # #keypoint_id == 18:
                                point_18 = np.array([hand.landmark[18].x, hand.landmark[18].y, hand.landmark[18].z ])
                                # #keypoint_id == 19:
                                point_19 = np.array([hand.landmark[19].x, hand.landmark[19].y, hand.landmark[19].z ])
                                #keypoint_id == 20 :
                                point_20 = np.array([hand.landmark[20].x, hand.landmark[20].y, hand.landmark[20].z ]) 
                                # tinh goc A -> I
                                self.A = self.math.cal_degree(point_3, point_2, self.point_0)  
                                self.B = self.math.cal_degree(point_6, point_5, self.point_0) 
                                self.C = self.math.cal_degree(point_7, point_6, point_5)
                                self.D = self.math.cal_degree(point_10, point_9,self.point_0)
                                self.E = self.math.cal_degree(point_11, point_10, point_9)
                                self.F = self.math.cal_degree(point_14, point_13, self.point_0)
                                self.G = self.math.cal_degree(point_15, point_14, point_13)
                                self.H = self.math.cal_degree(point_18, point_17, self.point_0)
                                self.I = self.math.cal_degree(point_19, point_18, point_17)
                                self.K = self.math.cal_degree(self.point_4, point_3, point_2)
                                # print("A", self.A)
                                # print('B', self.B)
                                # print('C', self.C)
                                # print('D', self.D)
                                # print('E', self.E)
                                # print('F', self.F)
                                # print('G', self.G)
                                # print('H', self.H)
                                # print('I', self.I)
                                # print('K', self.K)
                                self.classify(self.A, self.B, self.C, self.D, self.E, self.F, self.G, self.H, self.I, self.K)
                                # handPose = str(self.shapeHand)
                                # print(self.shapeHand)
                    h, w, ch = rgb_image.shape
                    bytes_per_line = ch * w
                    qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
                    self.frame_ready.emit(qt_image)
                    self.handPose.emit(str(self.shapeHand))
                    # cv2.imshow("webcam", rgb_image)

                if cv2.waitKey(1) == 27:  # 27 là mã ASCII của phím ESC
                    break
        cap.release()
        cv2.destroyAllWindows()
    def send_data(self):
        return self.shapeHand

    def classify(self, A, B, C, D, E, F, G, H, I, K):
        if (160 <= A <= 180) and (160 <= B <= 180)and (160 <= C <= 180)and (160 <= D <= 180)and (160 <= E <= 180)and (160 <= F <= 180)and (160 <= G <= 180)and (160 <= H <= 180)and (160 <= I <= 180):
            # print('open')
            self.shapeHand = 0
        if (90 <= A <= 130) and (30 <= B <= 145)and (40 <= C <= 170)and (30 <= D <= 140)and (40 <= E <= 170)and (25 <= F <= 130)and (45 <= G <= 155)and (20 <= H <= 130)and (50 <= I <= 160):
            # print('close-fit')
            self.shapeHand = 1
        if (160 <= A <= 180) and (50 <= B <= 140)and (50 <= C <= 180)and (30 <= D <= 160)and (20 <= E <= 150)and (30 <= F <= 160)and (30 <= G <= 140)and (20 <= H <= 170)and (5 <= I <= 150):
            O1 = self.math.vectorize(self.point_0)
            O = self.point_0
            O2 = self.point_4
            dirVetor_degree = self.math.cal_degree(O1, O, O2)
            if (0 <= dirVetor_degree <= 60):
                # print('Thumb-up')
                self.shapeHand = 2
            elif (120 <= dirVetor_degree <= 180):
                # print('Thumb down')
                self.shapeHand = 3

    def update_frame(self, qt_image):   
        pixmap = QPixmap.fromImage(qt_image)
        self.camera.setPixmap(pixmap)

# uyen = webcam_thread()
# uyen.run()

# print(oke)
