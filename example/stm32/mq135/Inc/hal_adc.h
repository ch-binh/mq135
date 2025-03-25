
#ifndef __ADC_H__
#define __ADC_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern ADC_HandleTypeDef hadc1;

void MX_ADC1_Init(void);

uint32_t hal_adc_read(void);

#endif /* __ADC_H__ */
