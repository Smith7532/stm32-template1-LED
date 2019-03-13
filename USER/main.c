#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{

  LED_init();
  delay_init();

  while (1)
  {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_ResetBits(GPIOE, GPIO_Pin_5);

    delay_ms(500);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);

    delay_ms(500);
  }
}
