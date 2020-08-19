#ifndef __stmETS_H
#define __stmETS_H

#include "stm32f10x.h"

typedef struct
{
    GPIO_TypeDef* self;
    uint32_t rccGPIOx;
    uint32_t rccAFIO;
    uint8_t GPIO_PSx;
}Tools_GPIOx;

static Tools_GPIOx tGPIOA = {GPIOA, RCC_APB2Periph_GPIOA, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOA};

static Tools_GPIOx tGPIOB = {GPIOB, RCC_APB2Periph_GPIOB, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOB};

static Tools_GPIOx tGPIOC = {GPIOC, RCC_APB2Periph_GPIOC, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOC};

static Tools_GPIOx tGPIOD = {GPIOD, RCC_APB2Periph_GPIOD, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOD};

static Tools_GPIOx tGPIOE = {GPIOE, RCC_APB2Periph_GPIOE, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOE};

static Tools_GPIOx tGPIOF = {GPIOF, RCC_APB2Periph_GPIOF, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOF};

static Tools_GPIOx tGPIOG = {GPIOG, RCC_APB2Periph_GPIOG, RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOG};

#endif /* __stmETS_H */