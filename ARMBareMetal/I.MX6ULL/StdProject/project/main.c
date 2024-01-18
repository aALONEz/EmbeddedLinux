#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "epit.h"

int main()
{
    Int_Init();//中断初始化,中断的初始化一定要在main函数最前面
    CLK_Init();//初始化配置系统主频
    CLK_Enable();//使能外设时钟
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    KEY_Init();//按键初始化
    EPIT_Init(EPIT1, 0, 33000000, 0, NULL);//EPIT计算公式 Tout = ((Prescaler + 1) * LoadValue) / Tclk    其中 Tclk是输入的时钟源的频率(这里是66MHz) LoadValue装载寄存器的值 Prescaler分频寄存器的值 Tout:EPIT溢出的时间单位S(秒)    此处配置为500ms产生一次溢出
    EPIT_Enable(EPIT1, Enable);
    while(1)
    {
    }
    return 0;
}
