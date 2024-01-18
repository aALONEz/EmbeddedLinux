#include "delay.h"

/// @brief 延时函数初始化
/// @param  无
void Delay_Init(void)
{
    //1.配置GPT2的CR寄存器
    GPT2->CR &= 0X0;//CR寄存器清零
    GPT2->CR |= (1 << 15);//软复位
    while(((GPT2->CR >> 15) & 0X01));//等待软复位完成
    GPT2->CR |= (1 << 1);//启用GPT2定时器时重置计数器和预分频计数器的值.
    GPT2->CR |= (1 << 6);//配置外设时钟作为时钟源.ipk_clk
    //2.配置GPT2的PR寄存器,设置分频值
    GPT2->PR &= 0X0;//PR寄存器清零
    GPT2->PR |= (65 << 0);//配置为66分频
    //3.配置输出比较通道1寄存器的值.
    GPT2->OCR[0] &= 0X0;//OCR1寄存器清零
    /* 1MHz计数1下就是1us,那么这里就是0XFFFFFFFFus约等于71.5分钟 */
    GPT2->OCR[0] |= 0XFFFFFFFF;//设置OCR1寄存器的值
    GPT_Enable(GPT2, Disable);
}


/// @brief us级延时
/// @param n 要延时多少us
void Delay_Us(volatile unsigned int n)
{
    GPT_Enable(GPT2, Enable);//使能定时器,开启计时
    while((GPT2->CNT) < n);//这里没有使用自己编写的GPT_ReadCount函数,这样可以更快速
    GPT_Enable(GPT2, Disable);//失能定时器
}

/// @brief ms级延时
/// @param n 要延时多少ms
void Delay_Ms(volatile unsigned int n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        Delay_Us(1000);
    }
}
