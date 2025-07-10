#ifndef GPIO_H_
#define GPIO_H_
#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f4xx.h"

// MACRO
#define blueLED_DISPLAY(x) GPIO_WriteBit(GPIOE, GPIO_Pin_8, (x) ? Bit_SET : Bit_RESET)
#define redLed_DISPLAY(x) GPIO_WriteBit(GPIOE, GPIO_Pin_7, (x) ? Bit_SET : Bit_RESET)
#define yelLed_DISPLAY(x) GPIO_WriteBit(GPIOE, GPIO_Pin_6, (x) ? Bit_SET : Bit_RESET)

#define ledBNT_START(x) GPIO_WriteBit(GPIOE, GPIO_Pin_9, (x) ? Bit_SET : Bit_RESET)
#define ledBTN_STOP(x) GPIO_WriteBit(GPIOE, GPIO_Pin_10, (x) ? Bit_SET : Bit_RESET)
#define ledBTN_RESET(x) GPIO_WriteBit(GPIOE, GPIO_Pin_11, (x) ? Bit_SET : Bit_RESET)

void Config_GPIO(void);
	 
 #ifdef __cplusplus
}
#endif
#endif





