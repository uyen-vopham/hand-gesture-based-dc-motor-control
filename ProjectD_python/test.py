class SinhVien:
    def __init__(self,hoten,mssv):
        self.name = hoten
        self.mssv = mssv
        self.__diemMax = 10
        
    def diem_TB(self,*a): ## diem_TB(7,5,5) toan = 7, tiếng việt = 5 , tin học = 9
        if(len(a) == 0):
            dtb = 0
        else:
            tong = 0
            for i in a:
                if i <= self.__diemMax:
                    tong = tong + i
                else:
                    print("Đã nhập điểm lớn hơn điểm max")
                    return 
            dtb = tong / len(a)
        return dtb
    
    
    def get_diemMax(self):
        return self.__diemMax    
    def set_diemmax(self, new_diemMax):
        self.__diemMax = new_diemMax