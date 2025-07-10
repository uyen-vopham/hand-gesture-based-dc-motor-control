import math
import numpy as np

class uyenMath ():
    
    def cal_degree (self, A, B, C):
        xA, yA, zA = A
        xB, yB, zB = B
        xC, yC, zC = C
        BA_ = np.array([xA-xB, yA-yB, zA-zB])
        BC_ = np.array([xC-xB, yC-yB, zC-zB])
        TichVoHuong = BA_[0]*BC_[0] + BA_[1]*BC_[1] + BA_[2]*BC_[2]
        # DoDaiVector = (math.sqrt(pow(AB_[0],2) + pow(AB_[1],2) + pow(AB_[2],2))) * (math.sqrt(pow(BC_[0],2)+pow(BC_[1],2)+pow(BC_[2],2)))
        DoDaiVectorAB_ = math.sqrt(BA_[0]*BA_[0] + BA_[1]*BA_[1] + BA_[2]*BA_[2])
        DoDaiVectorBC_ = math.sqrt(BC_[0]*BC_[0] + BC_[1]*BC_[1] + BC_[2]*BC_[2])

        DoDaiVector = DoDaiVectorAB_ * DoDaiVectorBC_
        angle_radient = math.acos(TichVoHuong/DoDaiVector)
        angle_degree = math.degrees(angle_radient)
        #print(angle_degree)
        return angle_degree
    
    def vectorize(self, O):
        xO, yO, zO = O
        O1 = np.array([xO, 0, zO])
        return O1






