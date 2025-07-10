import mysql.connector
from mysql.connector import Error
import datetime


class DatabaseMotor:
    def __init__(self, host="localhost", user="root", password="Iamduynhat1997", database_name="my_database"):
        try:
            self.mydb = mysql.connector.connect(host=host, user=user, password=password, database=database_name)
            print("connection successfully")
        except Error as e:
            print("error: ",e)
        
        self.current_date = datetime.date.today()
        
        self.cursor = self.mydb.cursor()
        self.table_name = "database_motor"
    
    def add_columns(self):
        self.alter_table_query = \
        """
        ALTER TABLE {} 
        ADD COLUMN IF NOT EXISTS timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        """.format(self.table_name)
        self.cursor.execute(self.alter_table_query)
        self.mydb.commit()

    def insert_data(self, speed, dir):
        insert_query = \
        """
        INSERT INTO {} (speed, Dir)
        VALUES (%s, %s)
        """.format(self.table_name)
        data = (speed, dir)
        self.cursor.execute(insert_query, data)
        self.mydb.commit()

    def read_data(self):
        #select_query = f"SELECT * FROM {self.table_name}"
        select_query = f"SELECT  speed, dir FROM {self.table_name}"
        self.cursor.execute(select_query)
        result = self.cursor.fetchall()
        return result
    
    def read_data_day(self):
        select_query = f"SELECT speed, dir FROM {self.table_name} WHERE DATE(timestamp) = '{self.current_date}'"
        self.cursor.execute(select_query)
        result = self.cursor.fetchall()
        return result
    
    def read_dataFull(self):
        select_query = f"SELECT speed, dir,timestamp FROM {self.table_name} WHERE DATE(timestamp) = '{self.current_date}'"
        self.cursor.execute(select_query)
        result = self.cursor.fetchall()
        return result
    
    def readTable_current_day(self):
        select_query = f"SELECT * FROM {self.table_name}"
        self.cursor.execute(select_query)
        result = self.cursor.fetchall()
        return result
    


    def read_data_paged(self, page_size, page_number):
        offset = page_size * (page_number - 1)
        select_query = f"SELECT speed, Dir FROM {self.table_name} LIMIT {page_size} OFFSET {offset}"
        self.cursor.execute(select_query)
        result = self.cursor.fetchall()
        return result
    
    def delete_data(self):
        delete_query = f"DELETE FROM {self.table_name}"
        self.cursor.execute(delete_query)
        self.mydb.commit()




    def close(self):
        self.cursor.close()
        self.mydb.close()

if __name__ == "__main__":

    run_fb = DatabaseMotor()
    data = run_fb.read_data()
    print("data: ", data)

        



