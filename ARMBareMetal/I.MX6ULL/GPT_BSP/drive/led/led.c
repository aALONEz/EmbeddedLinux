#include "led.h"

void LED_Init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);//配置复用
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X70);//配置电气属性
    GPIO1->GDIR = 0X8;//配置为输出模式
    GPIO1->DR = 0X8;//配置IO3引脚输出高电平,默认不点亮
}

static void LED_ON(void)
{
    GPIO1->DR &= ~(1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
}

static void LED_OFF(void)
{
    GPIO1->DR |= (1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
}

void LED_Switch(int LED, int Status)
{
    switch (LED)
    {
    case LED0:
        if(Status == ON)
            LED_ON();
        else
            LED_OFF();
        break;
    
    default:
        break;
    }
}
