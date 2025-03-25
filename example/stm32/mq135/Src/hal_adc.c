#include "hal_adc.h"

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config
   */
  hadc1.Instance = ADC1_INSTANCE;
  hadc1.Init.ScanConvMode = ADC1_SCAN_CONV_MODE;
  hadc1.Init.ContinuousConvMode = ADC1_CONT_CONV_MODE;
  hadc1.Init.DiscontinuousConvMode = ADC1_DISCONT_CONV_MODE;
  hadc1.Init.ExternalTrigConv = ADC1_EXT_TRIG_CONV;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
   */
  sConfig.Channel = MQ135_ADC_CHANNEL;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC1_SAMPLING_TIME;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (adcHandle->Instance == ADC1)
  {

    /* ADC1 clock enable */
    ADC1_CLK_ENABLE();
    GPIOA_CLK_DISABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    */
    GPIO_InitStruct.Pin = MQ135_ADC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(MQ135_ADC_PORT, &GPIO_InitStruct);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *adcHandle)
{

  if (adcHandle->Instance == ADC1)
  {
    /* Peripheral clock disable */
    ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    */
    HAL_GPIO_DeInit(MQ135_ADC_PORT, MQ135_ADC_PIN);
  }
}

uint32_t hal_adc_read(void)
{
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);

  uint32_t adc_val = HAL_ADC_GetValue(&hadc1);

  HAL_ADC_Stop(&hadc1);
  return adc_val;
}
