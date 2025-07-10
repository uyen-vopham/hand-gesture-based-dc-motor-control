
//*------------------------------------*START CALL LIBRARIES*----------------------------------------*//
#include "stm32f4xx.h"                  
#include "pwm.h"
#include "Config_GPIO.h"
#include "delay.h"
#include "uyen_uart.h"
#include <stdlib.h>
#include <stdbool.h> // thu vien khai bao kieu true/false
#include "ctype.h"
#include "uyen_encoder.h"
#include <math.h>
#include <stdio.h> // co ham printf
#include "timer_interupt.h"
#include <string.h>
#include "button_gpio.h"
#include "i2c_lcd.h"


#define size_Json  5
//----khai bao bien ------------------------------------------------------------------------------------------//
uint8_t rx_index = 0;

unsigned long last_uart,last_dirLed = 0U;
 
uint8_t button = 0; 
float  motor = 0.0f, dir = 1; float setpoint = 0.0f; //global variablle used to send to it.c for PID program
extern bool status_LED ;  // gui trang thai cua led
bool ledState;

char check_rx[10], speed_lcd[10], dir_lcd[10];

extern bool flag_LED, start_btn, stop_btn ;
extern volatile int interrupt_occurred ;


uint16_t data_rx = 0; char rx_buffer[50];//buffer chua data nhan ve tu python

float sp_rx, motor_rx, dir_rx = 0.0f; int  button_rx = 0;//data nhan ve tu python

//buffer chua data tu STM gui len python


extern float speed; extern int8_t DIR;  //data tu STM gui len python

uint8_t button_stm = 0;
extern uint8_t count_reset;
extern float output;
int count_led = 0;


bool state_dir,state_dir_ = false ;

//----goi function-----------------------------------------------------------------------------------------------//
void clearbufferEnd(void); 
void resetData(void);

//*---------------------------------------------*END FUNCTION DECLEARATION*---------------------------------------*//

int main(void)
  {	
	//*----------------------------------------------*START CALL FUNCTION*-------------------------------------------*//
 	PWM_TIM1_init();
	Delay_init();
	I2C_LCD_Init();
	I2C_LCD_BackLight(1);
		
		
		
	I2C_LCD_Clear();
	LCD_SetCursor(0,0);
	I2C_LCD_Puts("INITIALIZING!");
	
	//UART3_config();
	Config_GPIO(); blueLED_DISPLAY(0);redLed_DISPLAY(1);

	ConfigEncoder();
	Timer3_Interrupt();
	config_uart1(115200);
	last_uart = millis();
	last_dirLed = millis();
	EXTILine0_Config(); EXTILine1_Config(); EXTIReset_Config();
		
	SysTick_Config(SystemCoreClock / 1000);
	I2C_LCD_Clear();
	LCD_SetCursor(0,0);
	I2C_LCD_Puts("INITIALIZING!");
	delay_ms(100);
	I2C_LCD_Clear();
	//*---------------------------------------*END CALL FUNCTION*------- -------------------------------------------*//
	
	while(1)
	{	
			LCD_SetCursor(0,1);I2C_LCD_Puts("SPEED: ");
			sprintf(speed_lcd, "%.2f RPM", speed);
		
			LCD_SetCursor(0,7); I2C_LCD_Puts(speed_lcd);
		
			//LCD_SetCursor(0,7); I2C_LCD_Puts("20 RPM");
//			LCD_SetCursor(1,1);I2C_LCD_Puts("MOTOR: ");
//			dir == 1 ? (strcpy(dir_lcd, "FORWARD")) : (strcpy(dir_lcd, "REVERSE"));
			//LCD_SetCursor(1,7); I2C_LCD_Puts(dir_lcd);
//			LCD_SetCursor(1,7); I2C_LCD_Puts(dir_lcd);
//		
		
		resetData();
		
			//dao chieu dong co
			dir == 1 ? (GPIO_SetBits(GPIOA, GPIO_Pin_9),state_dir = true) : (GPIO_ResetBits(GPIOA, GPIO_Pin_9), state_dir = false); 
			
			if(state_dir == true)
			{
				yelLed_DISPLAY(1);
			}
			else
			{
				yelLed_DISPLAY(0);
			}
		
		
//			if (state_dir != state_dir_)
//			{
//				if( (unsigned long) (millis() - last_dirLed) >= 100) 
//				{
//					
//					ledState == 1 ? (ledState = 0,yelLed_DISPLAY(0)): (ledState=1,yelLed_DISPLAY(1));
//					count_led++;
// 
//					last_dirLed = millis();
//				}
//				
//				state_dir_ = state_dir;
//			}


		
			button_stm = (start_btn == true && stop_btn == false) ? 1 : 0;
			
	

			if(button_stm==1) 
			{
				ledBNT_START(1); ledBTN_STOP(0);
				button_stm = 0;
			}
			else
			{
				ledBTN_STOP(1);ledBNT_START(0);
				button_stm = 1;
			}

		
		if( (unsigned long) (millis() - last_uart) >= 300) 
		{

			char JSON[20];char Str_S1[size_Json];char Str_S2[size_Json]; char Str_S3[size_Json];
			int i;
			for(i=0; i<50; i++)
			{
				Str_S1[i] = 0;Str_S2[i] = 0; JSON[i] = 0; Str_S3[i] = 0;
			}

			sprintf(Str_S1, "%.2f", speed);sprintf(Str_S2, "%d", button_stm); sprintf(Str_S3, "%d", status_LED);
			
			strcat(JSON,Str_S1); 
			strcat(JSON,",");
			strcat(JSON,Str_S2);
			strcat(JSON,",");
			strcat(JSON,Str_S3);
			strcat(JSON,"\r\n");
			send_string_uart((u8 *)JSON,1);
			last_uart = millis();
		}
		
	}	
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) ==SET)
		{	
			while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
			{
			}
		data_rx = USART_ReceiveData(USART1);
			
		if (data_rx != '\n')
			{
				rx_buffer[rx_index++] = data_rx;
			}
		else
			{
				uint16_t uyen =	sscanf(rx_buffer, "%f,%d,%f,%f", &sp_rx, &button_rx, &motor_rx, &dir_rx)==4;			

			  setpoint = sp_rx;
				button = button_rx;
				motor = motor_rx;
				dir = dir_rx;
				
				

				clearbufferEnd();
			}
		}	
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void clearbufferEnd(void)
{
	int i = 0;
	for (i = 0; i<50 ;i++)
	{
		rx_buffer[i] = 0; 
	}
	rx_index = 0;
}


void resetData(void)
{
	if(count_reset %2 == 0)
	{
		//button_stm = 0;
		ledBTN_RESET(1);
	//	test_sp = 0; 
		delay_ms(1000);
		count_reset = 1;
		
	}
	else
	{
		ledBTN_RESET(0);
	}
}

























/*
	start_btn == true ? (button_stm = 1) : (button_stm = 0);
stop_btn == true ? (button_stm = 0) : (button_stm = 1);		






			
			if(start_btn == true && stop_btn == false )
			{
				button_stm = 1;
			}
			else
			{
				button_stm = 0;
			}
*/













