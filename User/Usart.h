#ifndef __Usart1_H
#define __Usart1_H

#include "stdio.h"
#include "Usart.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"

void USART1_Config(void);
int fputc(int ch, FILE *f);
void Usart1SendData(uint16_t Data);

#endif