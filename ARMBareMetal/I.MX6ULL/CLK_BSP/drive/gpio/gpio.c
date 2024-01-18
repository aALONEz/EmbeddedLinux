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
/// @return 读取到的电平状态 HighLevel表示高电平 LowLevel表示低电平
BitValue_t GPIO_PinRead(GPIO_Type *Base, uint32_t Pin)
{
    BitValue_t Value;
    Value = (((Base->DR) >> Pin) & 0X1);
    if(Value == HighLevel)
    {
        return HighLevel;
    }
    else
    {
        return LowLevel;
    }
}
