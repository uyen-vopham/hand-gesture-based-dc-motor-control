#ifndef __ENCODER_CONFIG_H_
#define __ENCODER_CONFIG_H_
#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f4xx.h"
	
void Encoder1_Tim2_Init(void);
void Encoder2_Tim5_Init(void);
void ConfigEncoder(void);

	 #ifdef __cplusplus
}
#endif

#endif 
