#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "exti.h"

uint8_t LED_Status = 1;

int main()
{
    Int_Init();//中断初始化,中断的初始化一定要在main函数最前面
    CLK_Init();//初始化配置系统主频
    CLK_Enable();//使能外设时钟
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    KEY_Init();//按键初始化
    GPIO1_IO18_Interrupt_Init();//注册GPIO1_IO18的中断

    while(1)
    {
    }
    return 0;
}

void GPIO1_IO18_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    if(GPIO_PinRead(GPIO1, 18) == 0)
    {
        LED_Switch(LED0, LED_Status);
        LED_Status = !LED_Status;

        //清除中断标志位.
        GPIO_Clean_InterruptBit(GPIO1, 18);
    }
}
