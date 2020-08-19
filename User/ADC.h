#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)


void ADC1_Init(void);

void ADC1_GPIO_Config(void);

void ADC1_Mode_Config(void);