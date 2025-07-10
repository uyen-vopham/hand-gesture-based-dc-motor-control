#include "button_gpio.h"
#include "delay.h"
#include <stdbool.h>
//#include <stdbool.h> 
NVIC_InitTypeDef  NVIC_InitStructure;   // NGAT VA UU TIEN NGAT 
EXTI_InitTypeDef  EXTI_InitStructure;   // NGAT NGOAI

//uint8_t count_START_ROBOT = 0U;
uint8_t count1=0, count2 = 0U, count1_ = 0U,count2_=0U;
uint8_t count_reset=1U; 


//uint8_t enable_START = 0 ;
bool flag_exti = false, start_btn = false, stop_btn = true;


void EXTILine0_Config(void)	
{
GPIO_InitTypeDef  GPIO_InitStructure;   // GPIO
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //CHO PHEP CLOCK CHAN GPIOE
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // CHO PHEP CLOCK CHAN SYSCFG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   // CAI DAT DAU VAO 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // CAI DAT CO DIEN TRO TREO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;      // CHAN E00
  GPIO_Init(GPIOD, &GPIO_InitStructure);         //  CAI DAT CHAN E
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0); // KET NOI CHAN IO VOI KHOI NGAT
  // CAU HINH LINE 0
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //THIET LAP NGAT VA UU TIEN NGAT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void EXTILine1_Config(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;   // GPIO
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //CHO PHEP CLOCK CHAN GPIOE
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // CHO PHEP CLOCK CHAN SYSCFG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   // CAI DAT DAU VAO 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // CAI DAT CO DIEN TRO TREO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;      // CHAN E00
  GPIO_Init(GPIOD, &GPIO_InitStructure);         //  CAI DAT CHAN E
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1); // KET NOI CHAN IO VOI KHOI NGAT
  // CAU HINH LINE 1
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //THIET LAP NGAT VA UU TIEN NGAT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTIReset_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   // GPIO
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //CHO PHEP CLOCK CHAN GPIOE
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // CHO PHEP CLOCK CHAN SYSCFG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   // CAI DAT DAU VAO 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // CAI DAT CO DIEN TRO TREO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;      // CHAN E00
  GPIO_Init(GPIOD, &GPIO_InitStructure);         //  CAI DAT CHAN E
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2); // KET NOI CHAN IO VOI KHOI NGAT
  // CAU HINH LINE 1
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //THIET LAP NGAT VA UU TIEN NGAT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) // co ngat co duoc enable khong, bit ngat co duoc enable khong
  {
				if(0==GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
				{
					delay_ms(50);
					if (0==GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
						{
							while (0==GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0));
						
								
							count1 ++;
							
							if(count1_ != count1)
							{
										start_btn = true;
										stop_btn = false;
										count1_ = count1;
							}
			
						}
				}
	}
	
    EXTI->PR = EXTI_Line0; // clear co ngat
  }
  
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET) // co ngat co duoc enable khong, bit ngat co duoc enable khong
  {
				if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0)
				{
					delay_ms(50);
					if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0)
						{
							while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0);
							count2 +=1;
			
							if(count2_ != count2)
							{
									start_btn = false;
									stop_btn = true;
								count2_ = count2;
							}
						}
				}
	}
    EXTI->PR = EXTI_Line1; // clear co ngat
  }

	
	void EXTI2_IRQHandler(void) // RESET 
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) // co ngat co duoc enable khong, bit ngat co duoc enable khong
  {
		
				if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0)
				{
					delay_ms(50);
					if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0)
						{
							while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0);
							count_reset +=1;
			
			

						}
				}
		
		
	}
	EXTI->PR = EXTI_Line2; // clear co ngat
    
  }
