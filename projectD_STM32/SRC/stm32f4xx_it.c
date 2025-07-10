#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "math.h"
#include "Config_GPIO.h"
uint32_t __msTick = 0U;	

int16_t encoder = 0U;


//float so1 = 0.0f;
float speed = 0.0f, error_pid = 0.0f;// rpm
extern float setpoint, motor, dir; extern uint8_t button; //global variable converted from data recieved python
int8_t DIR = 1; //bien huong cua dong co 1:fw, -1/;rv
float output = 0.0f, KP = 0.0f, KI = 0.0f, KD = 0.0f; 

int16_t counter, preCount = 0U ;

bool status_LED = false;
  // Khai báo các h?ng s? PID
  float kp = 5.0; 
  float ki = 0.1; 
  float kd = 0.1;

bool flag_LED = false;
extern bool flag_exti;
void SysTick_Handler(void);
void SysTick_Handler(void)
{

__msTick++;
	
}


/*
speed = (pulse_count * frequency) / (pulses_per_rev * time_elapsed)
speed = (pulse_count * 100) / (pulses_per_rev * 0.01)
*/
float pid_speed(float target, float rpm) 
{

  
  // Khai báo bi?n PID
  static float last_error = 0;

  // Tính sai s?
  error_pid = target - rpm;

  // Tính thành ph?n proportional
  KP = kp * error_pid;

  // Tính thành ph?n integral
  KI +=  (error_pid * 0.01f);

  // Tính thành ph?n derivative
  KD = kd*(error_pid - last_error)/0.01f;

 
  last_error = error_pid;

  // T?ng h?p các thành ph?n và tính toán d?u ra
  output = KP + ki*KI + KD;

  return output;
}

void TIM3_IRQHandler(void) //  interrupt 10ms 
{
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
  {		
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // clear flag interrupt
		
		encoder = TIM5 -> CNT; //toc do xung duoc doc tu timer 5
		
		counter = (encoder - preCount);  preCount = encoder; 

		if (counter < 0)
		{
			counter = counter*(-1.0);
		}
		speed = ((counter / 13728.0)* (1/0.01)*60); // toc do dong co vong/phut rpm

		output = pid_speed(setpoint,speed) ; 
		output > 95 ? (output = 95) : (output = output); output < 0 ? (output = 0) : (output = output);
		
		if (motor == 1 && button ==1)
				{
						blueLED_DISPLAY(1); redLed_DISPLAY(0);TIM1->CCR1 = output * 100/100;	//xuat xung	
						status_LED = true;
						
				}
		else
			{
				status_LED = false;
				redLed_DISPLAY(1);
				output = 0;
				blueLED_DISPLAY(0);
				TIM1->CCR1 = 0 * 100/100;	//xuat xung
			}
  }
}
