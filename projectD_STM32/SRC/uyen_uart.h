#ifndef UART_CONFIG_
#define UART_CONFIG_

#ifdef __cplusplus
 extern "C" {
#endif  
	 
#include "stm32f4xx.h"
void UART3_config(void);
void config_uart1(int baudrate);
void config_uart2(int baudrate);
void Vsend_char(u8 ch);
void Vsend_char_UART1(u8 ch);

void send_string_uart(u8 *p,u8 num_uart);
	 
	 
#ifdef __cplusplus
}
#endif
#endif
