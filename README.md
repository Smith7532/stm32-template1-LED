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
## 4.实验步骤

## 5.实验代码

## 6.实验结果

## 7.总结