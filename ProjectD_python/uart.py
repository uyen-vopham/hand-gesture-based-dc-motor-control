import serial
import time
data_split = []

# Khởi tạo đối tượng Serial với cổng COM1
ser = serial.Serial('COM4', 115200, timeout=1)

# Gửi dữ liệu đi
# ser.write(b'Hello World!')

# Đọc dữ liệu từ cổng serial
while True:

    data = ser.readline()
    data_str = data.decode('utf-8')
    data_split = data_str.split('\n')
    data1 = data_split[0]
    # data2 = data_split[1]
    # data3 = data_split[2]
    buffer = 'A,2.0,B\r\n'
    ser.write(buffer.encode('utf-8'))
    print(data)
    # print(data2)
    time.sleep(1)
# Đóng kết nối với cổng serial
ser.close()