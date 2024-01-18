#include "gpio.h"

/// @brief GPIO初始化,不包含复用和电气属性的设置
/// @param Base GPIO_Type结构体
/// @param Pin 引脚编号
/// @param Config GPIO_Pin_Config_t结构体 主要是配置引脚方向,是输入还是输出,输出的默认电平状态是多少
void GPIO_Init(GPIO_Type *Base, uint32_t Pin, GPIO_Pin_Config_t *Config)
{
    if ((Config->Direction) == Output) // 输出模式
    {
        Base->GDIR |= (1U << Pin);
        GPIO_PinWrite(Base, Pin, Config->OutputLogic);
    }
    else // 输入模式
    {
        Base->GDIR &= ~(1U << Pin);
    }
    GPIO_Interrupt_Init(Base, Pin, (Config->Int_Mode));
}

/// @brief GPIO_Pin写值,也就是控制引脚电平状态
/// @param Base GPIO_Type结构体
/// @param Pin 引脚编号
/// @param Value BitValue_t枚举 要写入的电平状态
void GPIO_PinWrite(GPIO_Type *Base, uint32_t Pin, BitValue_t Value)
{
    if (Value == LowLevel) // 输出低电平
    {
        Base->DR &= ~(1U << Pin);
    }
    else //输出高电平
    {
        Base->DR |= (1U << Pin);
    }
}

/// @brief 读取GPIO_Pin引脚电平状态
/// @param Base GPIO_Type结构体
/// @param Pin 引脚编号
/// @return 读取到的电平状态 1表示高电平 0表示低电平
uint8_t GPIO_PinRead(GPIO_Type *Base, uint32_t Pin)
{
    return (((Base->DR) >> Pin) & 0X1);
}

//使能指定Pin中断
void GPIO_Enable_Interrupt(GPIO_Type* Base, uint32_t Pin)
{
    //IMR寄存器控制着对应Pin引脚的中断的使能和关闭
    Base->IMR |= (1 << Pin);
}

//失能指定Pin中断
void GPIO_Disable_Interrupt(GPIO_Type* Base, uint32_t Pin)
{
    //IMR寄存器控制着对应Pin引脚的中断的使能和关闭
    Base->IMR &= ~(1 << Pin);
}

//清除中断标志位
void GPIO_Clean_InterruptBit(GPIO_Type* Base, uint32_t Pin)
{
    //ISR寄存器就是中断标志位,这个寄存器写1清零
    Base->ISR |= (1 << Pin);
}

void GPIO_Interrupt_Init(GPIO_Type* Base, const uint32_t Pin, GPIO_Bits_ICR_t Pin_Mode)
{
    volatile uint32_t* ICR;
    uint32_t TempPin = Pin;
    //默认不使用双边沿触发
    Base->EDGE_SEL &= ~(1 << Pin);
    if(Pin  > 15)//判断是引脚是高16位还是低16位
    {
        ICR = &(Base->ICR2);
        TempPin -= 16;
    }
    else
    {
        ICR = &(Base->ICR1);
    }

    //配置中断触发
    *ICR &= ~(3 << (2 * TempPin));//先将对应位清零
    switch (Pin_Mode)
    {
        case Low_Level:
        case High_Level:
        case Rising_Edge:
        case Falling_Edge:
        {
            *ICR |= (Pin_Mode << (2 * TempPin));
            break;
        }
        case Bilateral_Edge:
        {
            Base->EDGE_SEL |= (1 << Pin);
            break;
        }
        case Disable_Trigger:
        default:
        {
            //如果模式错误或者为不开启中断则关闭对应中断位
            break;
        }
    }
}
