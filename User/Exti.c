#include "Exti.h"

void EXTI_Config(Tools_GPIOx GPIOx, uint16_t GPIOpin) 
{
    GPIO_InitTypeDef GPIO_IS;
    EXTI_InitTypeDef EXTI_IS;
    
    RCC_APB2PeriphClockCmd(GPIOx.rccGPIOx | GPIOx.rccAFIO, ENABLE);   
    NVIC_Configuration();

    GPIO_IS.GPIO_Pin = GPIOpin;
    GPIO_IS.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOx.self, &GPIO_IS);

    GPIO_EXTILineConfig(GPIOx.GPIO_PSx, GPIO_PinSource0);
    EXTI_IS.EXTI_Line = EXTI_Line0;
    EXTI_IS.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_IS.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿中断
    EXTI_IS.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_IS);
       
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure one bit for preemption priority */ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* 配置P[A|B|C|D|E]5为中断源 */  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);
}
