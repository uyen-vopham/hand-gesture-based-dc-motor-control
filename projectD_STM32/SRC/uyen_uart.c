#include "uyen_uart.h"	
#define EN_IT_USART1_RX

 void config_uart1(int baudrate)
{ 
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //tx
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//rx
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1,&USART_InitStructure);
	 
	 USART_Cmd(USART1, ENABLE);
	 GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
#ifdef EN_IT_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

#endif	 
 }

 
 
  void config_uart2(int baudrate)
{ 
	//int i;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //tx
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//rx
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

 
   USART_Init(USART2,&USART_InitStructure);
	 USART_Cmd(USART2, ENABLE);
	 GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	 
 }

void UART3_config(void)
{
	NVIC_InitTypeDef           NVIC_InitStructure;
	USART_InitTypeDef 		     USART_InitStructure;
	GPIO_InitTypeDef           GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	 		// clock USART
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  // clock GPIO
		
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_10 | GPIO_Pin_11;			// TX-RX UART
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
 	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
 	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);   // USART3_TX
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);  // USART3_RX
	// Uart configure
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART3, &USART_InitStructure);	

	//enable the USART receive interrupt
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 	
	
	USART_Cmd(USART3, ENABLE);

}


void send_string_uart(u8 *p,u8 num_uart) // Ham nay dung de gui mot chuoi ra cong UART
{

	if(num_uart==1)// Neu num_uart = 1 thi ta dang chon cong UART1 de gui, tuong tu voi num_uart =2,3,4
	{
		while(*p)
		{
			USART_SendData(USART1, (uint8_t) *p++);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			{};	
		}
	}
	
}

void Vsend_char(u8 ch)
{
		USART_SendData(USART2, (uint8_t) ch);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
		{};		
}

void Vsend_char_UART1(u8 ch)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{};		
}





