#include "Config_GPIO.h"
void Config_GPIO(void)
{
	GPIO_InitTypeDef           GPIO_InitStructure;

	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); 
	//GPIO D_DIR
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	//GPIO A_DIR
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
}

