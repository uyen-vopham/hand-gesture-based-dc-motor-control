
#ifndef GPIO_Button_
#define GPIO_Button_
#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f4xx.h"
//void button_config(void);	 
void EXTILine0_Config(void);
void EXTILine1_Config(void);
void EXTIReset_Config(void);
 #ifdef __cplusplus
}
#endif
#endif
