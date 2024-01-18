#include "register.h"//引入自己定义的寄存器头文件

//使能外设时钟函数
void CLK_Enable(void)
{
    CCM_CCGR0 = 0XFFFFFFFF;
    CCM_CCGR1 = 0XFFFFFFFF;
    CCM_CCGR2 = 0XFFFFFFFF;
    CCM_CCGR3 = 0XFFFFFFFF;
    CCM_CCGR4 = 0XFFFFFFFF;
    CCM_CCGR5 = 0XFFFFFFFF;
    CCM_CCGR6 = 0XFFFFFFFF;
}

void LED_Init(void)
{
    MUX_GPIO1_IO03 = 0X5;//复用为GPIO1_IO03
    PAD_GPIO1_IO03 = 0X70;//配置GPIO1_IO03电气属性
    GPIO1_GDIR = 0X8;//配置为输出模式
    GPIO1_DR = 0X8;//配置IO3引脚输出高电平,默认不点亮
}

/* 主频396MHz约为1us */
void Delay_Us(volatile unsigned int n)
{
    n *= 2;
    while(n--);
}
/* 主频396MHz约为1ms */
void Delay_Ms(volatile unsigned int n)
{
    while(n--)
    {
        Delay_Us(1024);
    }
}

void LED_ON(void)
{
    GPIO1_DR &= ~(1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
}

void LED_OFF(void)
{
    GPIO1_DR |= (1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
}

int main()
{
    //初始化LED
    CLK_Enable();//使能时钟
    LED_Init();//初始化LED
    
    while(1)
    {
        LED_ON();
        Delay_Ms(1000);//延时一秒
        LED_OFF();
        Delay_Ms(1000);
    }
    return 0;
}