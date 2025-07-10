#include "uyen_encoder.h"
	

void Encoder1_Tim2_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);
	

	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

   
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    
		
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
		TIM2->CR1 |= TIM_CR1_CEN;
    //TIM_Cmd(TIM2,ENABLE);
		TIM2->CNT = 0;//2147483648
    //TIM_SetCounter(TIM2, 10000);

		
	
}

void Encoder2_Tim5_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
		
  
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
		
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
		
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    //TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

		
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM5,ENABLE);
    TIM5->CNT = 0U;//TIM_SetCounter(TIM5, 10000);  2147483648
}

void ConfigEncoder(void) // this is a function setting all encoder 
{
//	 Encoder1_Tim2_Init();
	 Encoder2_Tim5_Init();
}