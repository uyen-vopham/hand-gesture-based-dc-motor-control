#ifndef delay_H_
#define delay_H_
#ifdef __cplusplus
 extern "C" {
#endif 
#include "stm32f4xx.h"
void Delay_init(void);
void delay_ms(uint32_t u32DelayInMs);
uint32_t millis(void);
	 
#ifdef __cplusplus
}
#endif

#endif


	 

	

