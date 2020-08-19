#include "Usart.h"

/* 
* 函数名：USART1_Config 
* 描述 ：USART1 GPIO 配置,工作模式配置。115200 8-N-1 
* 输入 ：无 
* 输出 : 无 
* 调用 ：外部调用 
*/
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* config USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* USART1 GPIO config */
    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* Configure USART1 Rx (PA.10) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate = 115200;
    //配置串口传输的字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    //配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    //配置奇偶校验位
    USART_InitStructure.USART_Parity = USART_Parity_No;
    //配置硬件流控制（当外设处于准备好的状态时，硬件启动自动控制，不需要软件再进行干预）
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //配置串口模式，此处为全双工
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    //使能USART1接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //使能USART1
    USART_Cmd(USART1, ENABLE);

    /*串口中断配置*/
    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    //抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //子优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* 
 * 函数名：fputc 
 * 描述 ：重定向c库函数printf到USART1 
 * 输入 ：无 
 * 输出 ：无 
 * 调用 ：由printf调用 
 */
int fputc(int ch, FILE *f)
{
    /* 将Printf内容发往串口 */
    USART_SendData(USART1, (unsigned char)ch);
    // while (!(USART1->SR & USART_FLAG_TXE));
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
        ;
    return (ch);
}

void Usart1SendData(uint16_t Data)
{
    USART_SendData(USART1, Data);
    // while (!(USART1->SR & USART_FLAG_TXE));
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
        ;
}
