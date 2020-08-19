/**
  ******************************************************************************
  * @file    First_Demo/USER/main.c 
  * @author  MCD Application Team & MCFLY
  * @version V0.2
  * @date    15-June-2017
  * @brief   Main program body
  ******************************************************************************
  * 这是根据野火教程制作的一个ADC检测程序，结果通过Usart1发送。使用了ST库。现在使用STM32F103ZET6
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_ili9325_lcd.h"
#include "Led.h"
#include "Key.h"
#include "ADC.h"
#include "delay.h"

//ADC1 转换的电压值通过MDA 方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

//局部变量，用于保存转换计算后的电压值
float ADC_ConvertedValueLocal;

void Delay(__IO u32 nCount);

uint8_t oneFarme[260];
uint16_t SV;
uint8_t isPL = 0;
/* 
* 函数名：main 
* 描述 ：主函数 
* 输入 ：无 
* 输出 ：无 
*/

void GUI_INIT()
{
	setPointerColor(WHITE, BLACK);
	LCD_ShowString(100,0,100,16,16, "10KHZ");
	setPointerColor(GRAYBLUE, BLACK);
	LCD_DrawRectangle(19,15,281,225);

	setPointerColor(RED, BLACK);
	LCD_ShowString(1,14,18,12,12, "3V3");
	LCD_ShowString(1,218,18,12,12, " 0V");
	LCD_ShowString(1,156,18,12,12, " 1V");
	LCD_ShowString(1,94,18,12,12, " 2V");
	LCD_ShowString(1,32,18,12,12, " 3V");

	setPointerColor(GREEN, BLACK);
	for(uint16_t i = 0; i < 7; i++)
	{
		LCD_DrawLine(20 + i * 50, 225, 20 + i * 50, 227);
		setPointerColor(BRED, BLACK);
		for(uint16_t j = 1; j < 5; j++)
		{
			LCD_DrawLine(20 + i * 50 + j * 10, 225, 20 + i * 50 + j * 10, 226);
		}
		setPointerColor(GREEN, BLACK);
	}
	
	LCD_ShowString(16,228,18,12,12, "0ms");
	LCD_ShowString(66,228,18,12,12, "5ms");
	LCD_ShowString(116,228,24,12,12, "10ms");
	LCD_ShowString(166,228,24,12,12, "15ms");
	LCD_ShowString(216,228,24,12,12, "20ms");
	LCD_ShowString(266,228,24,12,12, "25ms");
	
	setPointerColor(CYAN, BLACK);
	LCD_ShowString(282,15,30,12,12, "Plock");
	
}
int main(void)
{
	/* USART1 config 115200 8-N-1 */
	Key_GPIO_Config(GPIOE, GPIO_Pin_0, RCC_APB2Periph_GPIOE);
	Key_GPIO_Config(GPIOC, GPIO_Pin_13, RCC_APB2Periph_GPIOC);
	delay_init();
	ADC1_Init();
	LCD_Init();
	LCD_Display_Dir(1);	
	LCD_Clear(BLACK);
	GUI_INIT();
	Delay(0x99);

	ADC_SoftwareStartConvCmd(ADC1, DISABLE); 

	
	while(1)
	{
		if(!Key_Scan(GPIOE, GPIO_Pin_0))
		{
			if(isPL == 0xff)
			{
				isPL = 0x00;
				LCD_ShowString(282,25,30,12,12, "NO ");
			}else if(isPL == 0x00){
				isPL = 0xff;
				LCD_ShowString(282,25,30,12,12, "YES");
			}
		}
		if(isPL == 0xff)
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
			delay_us(2);

			while(ADC_ConvertedValue < 2000);

			while(ADC_ConvertedValue > 2000);
		}
		for (int i = 0; i < 260; i ++)
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
			delay_us(2);
			ADC_SoftwareStartConvCmd(ADC1, DISABLE); 
			delay_us(90);
			oneFarme[i] = 208 - (ADC_ConvertedValue / 20);
			delay_us(7);
		}
		LCD_Fill(20,16,280,224,BLACK);	
		
		setPointerColor(MAGENTA, BLACK);
		for (int i = 1; i < 260; i ++)
		{
			LCD_DrawLine(i - 1 + 20, oneFarme[i - 1] + 16, i + 20, oneFarme[i] + 16);
		}
		while(!Key_Scan(GPIOC, GPIO_Pin_13));
	}
}

void Delay(__IO u32 nCount)
{
	for (; nCount != 0; nCount--);
}
