#include "led.h"
#include "clk.h"
#include "delay.h"
#include "beep.h"
#include "key.h"

int main()
{
    //初始化LED
    CLK_Enable();//使能时钟
    LED_Init();//LED初始化
    BEEP_Init();//蜂鸣器初始化
    KEY_Init();//按键初始化
    
    char Key_Status = 0;

    while(1)
    {
        if((KEY_Get_Status() == 1) && (Key_Status == 0))
        {
            BEEP_Switch(ON);
            Key_Status = 1;
        }
        else if((KEY_Get_Status() == 1) && (Key_Status == 1))
        {
            BEEP_Switch(OFF);
            Key_Status = 0;
        }
    }
    return 0;
}
