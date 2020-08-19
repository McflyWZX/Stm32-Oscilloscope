#include "Usart.h"

/* 
* ��������USART1_Config 
* ���� ��USART1 GPIO ����,����ģʽ���á�115200 8-N-1 
* ���� ���� 
* ��� : �� 
* ���� ���ⲿ���� 
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
    //���ô��ڴ�����ֳ�
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    //����ֹͣλ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    //������żУ��λ
    USART_InitStructure.USART_Parity = USART_Parity_No;
    //����Ӳ�������ƣ������账��׼���õ�״̬ʱ��Ӳ�������Զ����ƣ�����Ҫ����ٽ��и�Ԥ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //���ô���ģʽ���˴�Ϊȫ˫��
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    //ʹ��USART1�����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //ʹ��USART1
    USART_Cmd(USART1, ENABLE);

    /*�����ж�����*/
    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* 
 * ��������fputc 
 * ���� ���ض���c�⺯��printf��USART1 
 * ���� ���� 
 * ��� ���� 
 * ���� ����printf���� 
 */
int fputc(int ch, FILE *f)
{
    /* ��Printf���ݷ������� */
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
