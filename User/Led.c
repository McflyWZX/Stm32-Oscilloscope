/**
  ******************************************************************************
  * @file    Led.c 
  * @author  Mcfly
  * @version V3.5.0
  * @date    02-April-2017
  * @brief   led应用函数库
  * 		 D13 - D1, D14 - D3
  */
  
 #include "Led.h"

 /*
  * Funciton Name: LED_GPIO_Config
  * brief: Config the LED to I/O port
  * input: null
  * output: null
  */
void LED_GPIO_Config(Tools_GPIOx GPIOx, uint16_t GPIOpin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //enable GPIOD's PeriphClock
    RCC_APB2PeriphClockCmd(GPIOx.rccGPIOx, ENABLE);
    //Select control GPIOD's pin
    GPIO_InitStructure.GPIO_Pin = GPIOpin;
    //Set Pin mode to Push-pull output(推挽输出）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //Set speed to 50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //Call library function to Init GPIOD
    GPIO_Init(GPIOx.self, &GPIO_InitStructure);
    //Close D1 and D3
    GPIO_SetBits(GPIOx.self, GPIO_Pin_13 | GPIO_Pin_14);
}
//LED3 reserse
void LED_Reverse(GPIO_TypeDef* GPIOx, uint16_t GPIOpin)
{
    GPIO_WriteBit(GPIOx, GPIOpin, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOx, GPIOpin))));
}














