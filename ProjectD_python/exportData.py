from reportlab.lib.pagesizes import A4
from reportlab.pdfgen import canvas
import csv
class DataExport:
    def __init__(self):
        #self.data = data
        pass

    def export_data_to_csv(self,data, csv_file):
        with open(csv_file, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)

            writer.writerow(['Name: Vo Pham Mai Uyen', 'ID:1831100044'])  # Ghi dòng tiêu đề
            writer.writerow(['Report Database -- PROJECTD'])  # Ghi dòng tiêu đề


            writer.writerow([])  # Ghi một dòng trống
            writer.writerow(['Speed', 'Direction'])  

            for row in data:
                speed, direction, timesstamp = row
                writer.writerow([speed, direction,timesstamp])  


    def create_pdf(self,data, pdf_file):
        
        c = canvas.Canvas(pdf_file, pagesize=A4)

        # Vẽ tiêu đề
        c.setFont("Times-Bold", 16)
        c.drawString(100, 750, "Report Database - PROJECT D")
        c.drawString(100, 720, "Name: Vo Pham Mai Uyen  ID:1831100044")

        c.setFont("Times-Roman", 10) ; y = 700  # Vị trí dòng đầu tiên
        is_first_page = True 
        
        for i,row in enumerate (data):
            speed = row[0]
            direction = row[1]
            timestamp = row[2]
            if y < 50 and not is_first_page:
                c.showPage()
                y = 700  # Đặt lại vị trí dòng cho trang mới
                c.setFont("Times-Roman", 10)  # Đặt lại kích thước chữ cho trang mới
            if is_first_page or i == 0:

                c.drawString(100, y, f"Speed: {speed}")
                c.drawString(200, y, f"Direction: {direction}")
                c.drawString(300, y, f"timestamp: {timestamp}")
                y -= 15  # Giảm vị trí dòng
            else:
                c.drawString(100, y, f"Speed: {speed}")
                c.drawString(200, y, f"Direction: {direction}")
                c.drawString(300, y, f"timestamp: {timestamp}")
                y -= 15  # Giảm vị trí dòng
            is_first_page = False

        c.showPage()
        c.save()

        print("Tạo tệp PDF thành công: " + pdf_file)


