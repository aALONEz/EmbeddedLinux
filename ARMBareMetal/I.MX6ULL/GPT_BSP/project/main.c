#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "epit.h"
#include "gpt.h"

int main()
{
    Int_Init();//中断初始化,中断的初始化一定要在main函数最前面
    CLK_Init();//初始化配置系统主频
    CLK_Enable();//使能外设时钟
    GPT_Init(GPT1, 66 - 1, 1000000 / 2,  Enable);//GPT1定时器初始化
    GPT_Enable(GPT1, Disable);//使能GPT1定时器
    Delay_Init();
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    KEY_Init();//按键初始化
    EPIT_Init(EPIT1, 0, 33000000, 0, NULL);//EPIT计算公式 Tout = ((Prescaler + 1) * LoadValue) / Tclk    其中 Tclk是输入的时钟源的频率(这里是66MHz) LoadValue装载寄存器的值 Prescaler分频寄存器的值 Tout:EPIT溢出的时间单位S(秒)    此处配置为500ms产生一次溢出
    EPIT_Enable(EPIT1, Disable);
    while(1)
    {
        LED_Switch(LED0, ON);
        Delay_Ms(500);
        LED_Switch(LED0, OFF);
        Delay_Ms(500);
    }
    return 0;
}
