#include "key.h"

/// @brief 按键初始化
/// @param  无
void KEY_Init(void)
{
    //1.配置复用为GPIO1_IO18
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    //2.配置引脚电气属性,//(位0)低斜率速率(就是电平变化的速度),//(位3~位5)输出驱动器禁用(输入模式不需要,所以禁用),//(位6~位7)引脚工作频率(SPEED)设置为100MHz,
        //(位11)禁用开漏输出使能,//(位12)开启上拉或者保持功能,//(位13)上拉电阻开启(与前一个功能共同组合为开启上拉电阻),//(位14~位15)22千欧上拉电阻.
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF040);
    //3.初始化配置GPIO
    GPIO_Pin_Config_t GPIO_Pin_Config_Struct;
    GPIO_Pin_Config_Struct.Direction = Input;
    GPIO_Pin_Config_Struct.OutputLogic = HighLevel;//输入模式可不使用,但是要给这个成员赋值.

    GPIO_Init(GPIO1, 18, &GPIO_Pin_Config_Struct);
}

/// @brief 获取按键状态(按键引脚连接在GPIO1_IO18)
/// @param  无
/// @return 0表示按键未按下 1表示按键按下
char KEY_Get_Status(void)
{
    if(GPIO_PinRead(GPIO1, 18) == LowLevel)
    {
        Delay_Ms(10);//按下消抖
        while(GPIO_PinRead(GPIO1, 18) == LowLevel);
        Delay_Ms(10);//松手消抖
        return 1;
    }
    return 0;
}
