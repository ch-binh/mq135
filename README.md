# MQ135 Gas Sensor C Driver

## Overview
The **MQ135** is a gas sensor module used for air quality monitoring. This C driver enables communication with the MQ135 sensor using a microcontroller over an **analog interface**. The communication is just an ADC read. Main purpose is to verify the working state of the MQ135 and evaluate its power consumption

Currently, the example only supports STM32F103. Feel free to contact me if you need assistance or wish to develop additional features.

## Features
- Measure **air quality** based on gas concentration.

## Hardware Requirements
- **Microcontroller** (e.g., STM32, AVR, ESP32, etc.)
- **MQ135 Gas Sensor module**
- **1 ADC pin** for reading sensor data

## Example
- Currently supports an STM32 example, tested on STM32F103C8T6.
The example reads the sensor value and prints it out through UART.

## Wiring Diagram
For example STM32F103C6T6,
you can find the information in `inc/board_config.h`
or below:

| MQ135 Pin | MCU Pin  |
| --------- | -------- |
| VCC       | (MUST)5V |
| GND       | GND      |
| AOUT      | GPIO_A0  |
| UART (TX) | GPIO_A9  |

## Installation
1. **Copy driver files** (`mq135.c`, `mq135.h`) into your project.
2. **Include the header file** in your source code:
  ```c
  #include "mq135.h"
  ```

## Usage

### Initialize hardware abstraction for MQ135
```c
void mq135_com_init(void)
{
  mq135_hw_ops_t mq135_ops = {
      .read = hal_adc_read,
  };
  mq135_set_hw_ops(&mq135_ops);
}



uint32_t mq135_get_adc(void)
{
    return mq135_read_adc();
}

...
```

### Initialize MCU hardware
```c
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  mq135_com_init();
```

### Read Gas Concentration
```c
    sw_udelay(1000000);

    uint32_t adc_value = mq135_get_adc();
    hal_uart_printf("ADC value: %d\n", adc_value);
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
```

### Results:
*I used logic analyzer to print out values*
```c
ADC value: 426
ADC value: 433
ADC value: 434
ADC value: 434
ADC value: 428
ADC value: 429
ADC value: 434
ADC value: 1668
ADC value: 2916
ADC value: 2486
ADC value: 2145 // small gas leak
ADC value: 1848
ADC value: 1633
ADC value: 1463
ADC value: 1308
ADC value: 1144
ADC value: 1003
ADC value: 928
ADC value: 880
ADC value: 4095
ADC value: 4095
ADC value: 4095 // heavy gas leak
ADC value: 4095
ADC value: 2876
ADC value: 2294
ADC value: 1989
ADC value: 1783
ADC value: 1651
ADC value: 1572
ADC value: 1462
```

## Notes
- MQ135 operates at **5V**.

## Power Consumption Experiment
- Measurement device: Nordic PPK2
- Condition: Input supply to VCC (main power source)
- Result: 135mA @ 5V (datasheet: ~1W)

![Power consumption @ 5V, result 135mA](docs/power_consumption.png)

## License
This driver is open-source and can be used freely in any project.

---

**Author:** Binh Pham  
**Contact me**: You can find my contact @ https://github.com/ch-binh  
**Version:** 1.0  
**Last Updated:** March 2025
