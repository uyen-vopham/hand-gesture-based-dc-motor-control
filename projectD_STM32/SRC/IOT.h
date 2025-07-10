#ifndef IOT_H_
#define IOT_H_
#ifdef __cplusplus
 extern "C" {
#endif 
#include "stm32f4xx.h"
#include "cJSON.h" 
	 
#define size  500 // kich thuoc cua chuoi


void ShowDataTimeOut(void);
void ReceiveTimeOut(void);
void ClearBufferTimeOut(void);

void ReceiveEnd(void); // co byte ket thuc
void clearbufferEnd(void);

uint32_t millis(void);
	 
#ifdef __cplusplus
}
#endif
#endif

