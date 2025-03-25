/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "main.h"
#include "hal_adc.h"
#include "hal_usart.h"
#include "hal_gpio.h"
#include "syscfg.h"
#include "mq135.h"

#define CLOCK_SPEED 8000000

void mq135_com_init(void)
{
  mq135_hw_ops_t mq135_ops = {
      .read = hal_adc_read,
  };
  mq135_set_hw_ops(&mq135_ops);
}

void sw_udelay(uint32_t us)
{
  uint32_t clock_ticks = us * (uint32_t)(CLOCK_SPEED / 1000000);
  for (uint32_t i = 0; i < clock_ticks; i++)
  {
    __NOP();
  }
}

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  mq135_com_init();

  while (1)
  {

    sw_udelay(1000000);

    uint32_t adc_value = mq135_get_adc();
    hal_uart_printf("ADC value: %d\n", adc_value);
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
  }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
