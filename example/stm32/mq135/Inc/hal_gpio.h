
#ifndef __GPIO_H__
#define __GPIO_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef enum
{
  PIN_MODE_INPUT,
  PIN_MODE_OUTPUT
} pin_mode_e;

#define LOW 0
#define HIGH 1

void MX_GPIO_Init(void);

void hal_gpio_ds1302_init(void);
void hal_gpio_ds1302_deinit(void);

void hal_gpio_builtin_led_init(void);
void hal_gpio_builtin_led_deinit(void);

#endif /*__ GPIO_H__ */
