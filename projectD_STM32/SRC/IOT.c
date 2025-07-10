#include "IOT.h"
#include <string.h> // strstr
#include "uart_config.h"
#include <stdbool.h> // thu vien khai bao kieu true/false
	 
long timeout = 500U;
long last = 0;
bool codulieu = false;

uint8_t rx_data1; // luu byte nhan duoc
uint8_t  rx_index1; // contro cua rx_bufer
char rx_buffer1[size]; // luu chuoi nhan duoc


uint8_t rx_data2; // luu byte nhan duoc
uint8_t  rx_index2; // contro cua rx_bufer
char rx_buffer2[size]; // luu chuoi nhan duoc
char DataSendAT[50];
extern uint32_t __msTick ;	




void ClearBufferTimeOut(void)
	{
		int i = 0;
		for(i=0;i<size;i++)
		{
			rx_buffer1[i]=0;
			
		}
		rx_index1 = 0;
	}
	
void ReceiveTimeOut(void)
{
	rx_buffer1[rx_index1++]= rx_data1;
}

void ShowDataTimeOut(void)
{
	if(codulieu == true) // da co du lieu
	{
		if(millis()-last>=timeout)
		{
			send_string_uart((u8 *)"show data buffer : \r\n ",3);
			send_string_uart((u8 *)rx_buffer1,3);
			
			// su ly du lieu o day
			
			
			if(strstr(rx_buffer1,"ABC")!= NULL) // kiem tra xem trong mang rx_buffer con ton tai "ABC" hay khong, neu co ton tai thi la != NULL tuc la co gia tri
			{
				send_string_uart((u8 *)"ON DEN: \r\n ",3);
				
			}
			else
			{
				send_string_uart((u8 *)"OFF DEN	 : \r\n ",3);
			}
		
			ClearBufferTimeOut();
			last = millis();
			codulieu = false;
		}
		
	}
}

void ReceiveEnd(void)
	{
	int i = 0;
		if(rx_data1 != '\n')
		{
			rx_buffer1[rx_index1++] = rx_data1;
			
		}
		else
		{
			// show data
			send_string_uart((u8 *)"Showdata \r\n ",3);
			send_string_uart((u8 *)rx_buffer1,3);
			send_string_uart((u8 *)"\r\n ",3);
			
			////// lay du lieu gui qua esp
			for(i=0;i<50;i++) // xoa mang
			{
				DataSendAT[i] = 0;
			}
			
		
			if(strstr(rx_buffer1,"ABC") != NULL) // ham nay xet ky tu lien ke voi nhau, Vd ABCD thi oke, ABDC thi khong thuc hien
			// vd gui ABCDEF thi se nhay vao ON Den voi truong hop la dung else if neu dung if(strstr(rx_buffer1,"DEF") != NULL) thi se thuc hien 2 lenh luon ON DEN xong roi OFF DEN
		
			{
			
			send_string_uart((u8 *)"ON DEN : \n ",3);
			}
			else if(strstr(rx_buffer1,"DEF") != NULL)
			{
			send_string_uart((u8 *)"OFF DEN: \n ",3);
			
			}
			clearbufferEnd();
			
		}
		
	}
	
void clearbufferEnd(void)
{
	int i = 0;
	for (i = 0; i<size ;i++)
	{
		rx_buffer1[i] = 0; 
	}
	rx_index1 = 0;
}


uint32_t millis(void)
{
	return __msTick;
}
