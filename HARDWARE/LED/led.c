#include "led.h"
#include "stm32f10x.h"

void LED_init(void){
    GPIO_InitTypeDef GPIO_InitStruct; //定义 GPIO初始化结构体
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//GPIOE时钟使能

    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;  //GPIO模式
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//pin口
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//速度

    GPIO_Init(GPIOB,&GPIO_InitStruct);//初始化GPIO B组
    GPIO_Init(GPIOE,&GPIO_InitStruct);//初始化GPIO E组

    GPIO_SetBits(GPIOB,GPIO_Pin_5);//置1（LED关闭）
    GPIO_SetBits(GPIOE,GPIO_Pin_5);//置1（LED关闭）
}
