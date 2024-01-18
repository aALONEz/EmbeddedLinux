#include "led.h"
#include "clk.h"
#include "delay.h"

int main()
{
    //初始化LED
    CLK_Enable();//使能时钟
    LED_Init();//初始化LED
    
    while(1)
    {
        LED_Switch(LED0, ON);
        Delay_Ms(1000);//延时一秒
        LED_Switch(LED0, OFF);
        Delay_Ms(1000);
    }
    return 0;
}
