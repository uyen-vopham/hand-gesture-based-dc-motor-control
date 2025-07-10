#include "pwm.h"
void PWM_TIM1_init(void)
{

	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	TIM_OCInitTypeDef          TIM_OCInitStructure;
	GPIO_InitTypeDef           GPIO_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler =  168-1;      
  TIM_TimeBaseStructure.TIM_Period = 100-1;   //  f=10khz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 
  TIM_OCInitStructure.TIM_Pulse =0;
	
	// GPIO A _ PWM
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	
	
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);  
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM1, ENABLE);
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	

}
