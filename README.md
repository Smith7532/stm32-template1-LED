# 实验1-LED实验
[toc]
## 1. 实验目的和要求
1. 简单熟悉stm32开发板的硬件（尤其是GPIO）
1. 了解keil软件的操作方法
1. 基本了解stm32开发的工程模板
1. stm32IO口8种输入输出模式的了解
1. 实现板上两颗LED灯（同时或交替闪烁）的效果
## 2.实验设备
1. stm32f103zet6开发板（正点原子战舰v3版）
1. keil软件
1. flymcu——stm32串口下载软件
## 3.实验原理
### 3.1 硬件连接
STM32F103 板载总共有 3 个 LED，其原理图如图所示
<img src="/img/LEDpcb.png" width = "300" height = "200" alt="LED电路原理">
其中 PWR 是系统电源指示灯，为蓝色。
LED0(DS0)和 LED1(DS1)分别接在 PB5 和 PE5 上。
<img src="/img/LED0PB5.png" width = "300" height = "100" alt="LED0在PB5上">
<img src="/img/LED1PE5.png" width = "300" height = "100" alt="LED1在PE5上">
LED0为红色，LED1为绿色
### 3.2 STM32的GPIO
STM32 的 IO 口 可以由软件配置成如下 8 种模式：
* 上拉输入：上拉就是把电位拉高，比如拉到Vcc。上拉就是将不确定的信号通过一个电阻嵌位在高电平！电阻同时起限流作用！弱强只是上拉电阻的阻值不同，没有什么严格区分。
* 下拉输入：就是把电压拉低，拉到GND。与上拉原理相似。
* 浮空输入：浮空（floating）就是逻辑器件的输入引脚即不接高电平，也不接低电平。由于逻辑器件的内部结构，当它输入引脚悬空时，相当于该引脚接了高电平。一般实际运用时，引脚不建议悬空，易受干扰。 通俗讲就是让管脚什么都不接，浮空着。
* 模拟输入：模拟输入是指传统方式的输入.数字输入是输入PCM数字信号,即0,1的二进制数字信号,通过数模转换,转换成模拟信号,经前级放大进入功率放大器,功率放大器还是模拟的。
* 开漏输出：输出端相当于三极管的集电极. 要得到高电平状态需要上拉电阻才行. 适合于做电流型的驱动,其吸收电流的能力相对强(一般20ma以内).
* 推挽输出：可以输出高,低电平,连接数字器件; 推挽结构一般是指两个三极管分别受两互补信号的控制,总是在一个三极管导通的时候另一个截止。高低电平由IC的电源低定。
* 推挽式复用输出：可以理解为GPIO口被用作第二功能时的配置情况（即并非作为通用IO口使用）。
* 开漏复用输出：可以理解为GPIO口被用作第二功能时的配置情况（即并非作为通用IO口使用）。


GPIO 相关的函数和定义分布在固件库文件 stm32f10x_gpio.c 和头文件 stm32f10x_gpio.h 文 件中。

GPIO初始化
``` c
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | B | C, ENABLE); //使能APB2总线外设时钟

RCC_ APB2PeriphResetCmd (RCC_APB2Periph_GPIOA | B | C, DISABLE); //释放GPIO复位

配置各个PINport(模拟输入_AIN、输入浮空_IN_FLOATING、输入上拉_IPU、输入下拉_IPD、
开漏输出_OUT_OD、推挽式输出_OUT_PP、推挽式复用输出_AF_PP、开漏复用输出_AF_OD); //GPIO初始化完毕
```

## 4.实验步骤及实验代码
1. 使用TEMPLATE0，在工程目录新建HARDWARE/LED文件夹，在LED文件夹内新建led.h头文件和led.c源文件。
    并把它们加到工程内，并在includepath内加上".../HARDWARE/LED"
    <img src="/img/contents.png" width = "300" height = "600" alt="工程目录">
    ``` c
    /*led.h文件*/
    #ifndef __LED_H
    #define __LED_H

    void LED_init(void);//LED初始化函数声明

    #endif // !__LED_H

    ```


    ``` c
    /*led.c文件*/
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
    ```
1. IO口初始化都要先进行对应时钟使能，GPIO 是挂载在 APB2 总线上的外设，所以使能APB2的时钟，其次配置GPIO初始化结构体，再使用GPIO_Init()函数进行初始化，并置一个初值（将LED关闭）。
1. 编写main.c
    ``` c
    #include "stm32f10x.h"
    #include "led.h"
    #include "delay.h"//为了使用delay_ms()函数

    int main(void)
    {

        LED_init();//初始化LED
        delay_init();//初始化delay

        while (1)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_5);//关LED0
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);//开LED1

            delay_ms(500);//延时500ms，以便能观察到实验现象

            GPIO_ResetBits(GPIOB, GPIO_Pin_5);//开LED0
            GPIO_SetBits(GPIOE, GPIO_Pin_5);//关LED1

            delay_ms(500);延时500ms，以便能观察到实验现象
        }
    }

    ```
1. 编译完成后，使用flyMCU下载到开发板内，观察实验结果，调试。
## 5.实验结果



## 6.总结
1. 对stm32开发的工程文件体系有了一个粗略的认识。
1. 对编写自己的硬件开发库有一个框架的认识。
1. 明白对GPIO的初始化过程

