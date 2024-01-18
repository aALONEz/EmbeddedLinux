#include "beep.h"

/// @brief 蜂鸣器初始化.
/// @param  
void BEEP_Init(void)
{
    GPIO_Pin_Config_t BEEP_Pin_Config;
    //1.复用为GPIO5_IO01
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    //2.配置引脚电气属性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0XB0);
    //3.GPIO初始化
    BEEP_Pin_Config.Direction = Output;
    BEEP_Pin_Config.OutputLogic = HighLevel;
    GPIO_Init(GPIO5, 1, &BEEP_Pin_Config);
}

/// @brief 切换蜂鸣器状态
/// @param Status ON为打开蜂鸣器 OFF为关闭蜂鸣器
void BEEP_Switch(char Status)
{
    if(Status == ON)
    {
        GPIO_PinWrite(GPIO5, 1, LowLevel);
    }
    else
    {
        GPIO_PinWrite(GPIO5, 1, HighLevel);
    }
}
