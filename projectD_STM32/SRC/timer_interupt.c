 #include "timer_interupt.h"
void Timer3_Interrupt(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
		NVIC_InitTypeDef 		NVIC_InitStructure;
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	 
	//SystemCoreClock
	
	/*
	Tan so = Toc do xung nhip / (TIM_Prescaler + 1) / (TIM_Period + 1)
	*/
    /* Time base configuration */
		TIM_TimeBaseInitStructure.TIM_Prescaler =  ((SystemCoreClock/2)/1000000)-1; // 84HZ
    TIM_TimeBaseInitStructure.TIM_Period =  10000-1;   
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3, ENABLE);   
	
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
	
}
