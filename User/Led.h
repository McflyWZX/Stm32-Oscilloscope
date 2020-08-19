#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "stmEasyTools.h"

#define ON 1
#define OFF 0

//带参宏，可以像内联函数一样使用
#define LED1(a) if (a) \
                    GPIO_SetBits(GPIOD, GPIO_Pin_13); \
                    else        \
                    GPIO_ResetBits(GPIOD, GPIO_Pin_13);

#define LED3(a) if (a) \
                    GPIO_SetBits(GPIOD, GPIO_Pin_14); \
                    else        \
                    GPIO_ResetBits(GPIOD, GPIO_Pin_14);

void LED_GPIO_Config(Tools_GPIOx GPIOx, uint16_t GPIOpin);
void LED_Reverse(GPIO_TypeDef* GPIOx, uint16_t GPIOpin);

#endif /* __LED_H */
