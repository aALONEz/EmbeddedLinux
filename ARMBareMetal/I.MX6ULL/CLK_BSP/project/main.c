#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"
#include "key.h"

int main()
{
    CLK_Init();//初始化配置系统主频
    CLK_Enable();//使能外设时钟
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    KEY_Init();//按键初始化

    while(1)
    {
        LED_Switch(LED0, ON);
        Delay_Ms(1000);
        LED_Switch(LED0, OFF);
        Delay_Ms(1000);
    }
    return 0;
}
