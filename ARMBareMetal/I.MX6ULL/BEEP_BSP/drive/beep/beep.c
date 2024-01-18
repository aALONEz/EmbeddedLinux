#include "beep.h"

/// @brief 蜂鸣器初始化.
/// @param  
void BEEP_Init(void)
{
    //1.复用为GPIO5_IO01
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    //2.配置引脚电气属性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0XB0);
    //3.GPIO初始化
    GPIO5->GDIR |= (1 << 1);//配置为输出模式
    //4.配置GPIO电平状态
    GPIO5->DR |= (1 << 1);//默认蜂鸣器不鸣叫
}

/// @brief 切换蜂鸣器状态
/// @param Status ON为打开蜂鸣器 OFF为关闭蜂鸣器
void BEEP_Switch(char Status)
{
    if(Status == ON)
    {
        GPIO5->DR &= ~(1 << 1);
    }
    else
    {
        GPIO5->DR |= (1 << 1);
    }
}
