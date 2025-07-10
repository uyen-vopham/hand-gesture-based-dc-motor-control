import mysql.connector

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="7777",
  database="projectd"
)
if mydb:
    print("connect successfully")
else:
    print("Failed")

cursor = mydb.cursor()

#cursor.execute("CREATE TABLE speed (name VARCHAR(255), address VARCHAR(255))")

insert_query = "INSERT INTO speed (name, address) VALUES (%s, %s)"
data = ("John Doe", "123 Main Street")
cursor.execute(insert_query, data)

#cursor.execute("CREATE DATABASE projectD")
#cursor.execute("SHOW DATABASES")

# for x in cursor:
#   print(x)
# cursor.close()
# mydb.close()
