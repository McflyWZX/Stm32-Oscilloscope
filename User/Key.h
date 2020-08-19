#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY_ON 0
#define KEY_OFF 1

void Key_GPIO_Config(GPIO_TypeDef* GPIOx, uint16_t GPIOpin, uint32_t rccGPIOx);
u8 Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIOpin);

#endif /* __KEY_H */