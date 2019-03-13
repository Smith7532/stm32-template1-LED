#include "led.h"
#include "stm32f10x.h"

void LED_init(void){
    GPIO_InitTypeDef GPIO_InitStruct; //���� GPIO��ʼ���ṹ��
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOBʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//GPIOEʱ��ʹ��

    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;  //GPIOģʽ
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//pin��
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//�ٶ�

    GPIO_Init(GPIOB,&GPIO_InitStruct);//��ʼ��GPIO B��
    GPIO_Init(GPIOE,&GPIO_InitStruct);//��ʼ��GPIO E��

    GPIO_SetBits(GPIOB,GPIO_Pin_5);//��1��LED�رգ�
    GPIO_SetBits(GPIOE,GPIO_Pin_5);//��1��LED�رգ�
}
