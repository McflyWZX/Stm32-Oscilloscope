#ifndef __EXTI_H
#define __EXTI_H

#include "stmEasyTools.h"
#include "misc.h"
#include "stm32f10x.h"

void EXTI_Config(Tools_GPIOx GPIOx, uint16_t GPIOpin);
static void NVIC_Configuration(void);

#endif /* __EXTI_H */