import mysql.connector
import time

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="7777",
  database="projectD"
)
if mydb:
    print("connect successfully")
else:
    print("Failed")

cursor = mydb.cursor()
# #cursor.execute("CREATE DATABASE projectD")
# # cursor.execute("CREATE TABLE myDB (speed FLOAT)")


table_name = "mydb"
speed = 20.5
dir = 1


insert_query = """INSERT INTO {} (speed, dir) VALUES (%s, %s)""".format(table_name)
alter_query = "ALTER TABLE {} ADD {} {}".format(table_name, "dir", "VARCHAR(255)")
alter_table_query ="""ALTER TABLE {} ADD COLUMN timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP""".format(table_name)
# cursor.execute(alter_table_query)
# cursor.execute(alter_query)
# while True:
#   data = (speed, dir)
#   cursor.execute(insert_query, data)
#   speed += 1
#   dir += 1
#   mydb.commit() #đẩy dữ liệu lên
#   time.sleep(5)
cursor.execute("SELECT * FROM mydb") # Thay 'table_name' bằng tên bảng bạn muốn truy vấn

# Duyệt qua các hàng trong kết quả
for row in cursor:
    print(row)

cursor.close()
mydb.close()