#include "delay.h"

extern uint32_t __msTick ;

uint32_t millis(void)
{
	return __msTick;
}

void Delay_init(void)
{

	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef          TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	TIM_Cmd(TIM6,ENABLE);
}

void delay_us(uint32_t delay)
{
	TIM_SetCounter (TIM6,0);
	while(TIM_GetCounter(TIM6) < delay)  // doc gia tri chua trong thanh ghi dem
	{ 
	}
}

void delay_ms(uint32_t u32DelayInMs)
{
	while (u32DelayInMs) {
				TIM_SetCounter (TIM6,0);
		while(TIM_GetCounter(TIM6)<1000){ // doc gia tri chua trong thanh ghi dem
		}
			--u32DelayInMs;
		}

}


