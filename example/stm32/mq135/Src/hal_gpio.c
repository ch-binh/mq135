
#include "hal_gpio.h"
#include "main.h"


void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  GPIOD_CLK_ENABLE();
  hal_gpio_builtin_led_init();
}


void hal_gpio_builtin_led_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOC_CLK_ENABLE();
  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = BUILTIN_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUILTIN_LED_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN, GPIO_PIN_RESET);
}

void hal_gpio_builtin_led_deinit()
{
  HAL_GPIO_DeInit(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
}
