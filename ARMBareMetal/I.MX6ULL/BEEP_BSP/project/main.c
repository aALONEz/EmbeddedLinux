#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"

int main()
{
    //初始化LED
    CLK_Enable();//使能时钟
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    
    while(1)
    {
        LED_Switch(LED0, ON);
        BEEP_Switch(OFF);
        Delay_Ms(1000);//延时一秒
        LED_Switch(LED0, OFF);
        BEEP_Switch(ON);
        Delay_Ms(1000);
    }
    return 0;
}
