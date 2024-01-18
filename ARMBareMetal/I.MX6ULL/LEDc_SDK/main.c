#include "fsl_iomuxc.h"//引入头文件
#include "fsl_common.h"
#include "MCIMX6Y2.h"

//使能外设时钟函数
void CLK_Enable(void)
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

void LED_Init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);//配置复用
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X70);//配置电气属性
    GPIO1->GDIR = 0X8;//配置为输出模式
    GPIO1->DR = 0X8;//配置IO3引脚输出高电平,默认不点亮
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
        Delay_Us(800);
    }
}

void LED_ON(void)
{
    GPIO1->DR &= ~(1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
}

void LED_OFF(void)
{
    GPIO1->DR |= (1 << 3);//配置为低电平.LED亮。这里必须要配置为0X0才可以点亮LED，0是不可以的
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