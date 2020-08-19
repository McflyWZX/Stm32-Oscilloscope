#include "Key.h"
#include "delay.h"

void Key_GPIO_Config(GPIO_TypeDef* GPIOx, uint16_t GPIOpin, uint32_t rccGPIOx)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(rccGPIOx, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIOpin;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

    GPIO_Init(GPIOx, &GPIO_InitStructure);

}

u8 Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIOpin)
{
    if(GPIO_ReadInputDataBit(GPIOx, GPIOpin) == KEY_ON)
    {
        delay_us(100);

        if(GPIO_ReadInputDataBit(GPIOx, GPIOpin) == KEY_ON)
        {
            
            while(GPIO_ReadInputDataBit(GPIOx, GPIOpin) == KEY_ON);
            return KEY_ON;

        } else return KEY_OFF;

    } else return KEY_OFF;
        
}

