#include "key.h"

/// @brief 按键初始化
/// @param  无
void KEY_Init(void)
{
    //配置复用为GPIO1_IO18
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    //配置引脚电气属性,//(位0)低斜率速率(就是电平变化的速度),//(位3~位5)输出驱动器禁用(输入模式不需要,所以禁用),//(位6~位7)引脚工作频率(SPEED)设置为100MHz,
        //(位11)禁用开漏输出使能,//(位12)开启上拉或者保持功能,//(位13)上拉电阻开启(与前一个功能共同组合为开启上拉电阻),//(位14~位15)22千欧上拉电阻.
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF040);
    //初始化配置GPIO
    GPIO_Pin_Config_t GPIO_Pin_Config_Struct;
    GPIO_Pin_Config_Struct.Direction = Input;//输入模式
    GPIO_Pin_Config_Struct.OutputLogic = HighLevel;//输入模式可不使用,但是要给这个成员赋值.
    GPIO_Pin_Config_Struct.Int_Mode = Falling_Edge;//下降沿触发

    GPIO_Init(GPIO1, 18, &GPIO_Pin_Config_Struct);
    //使能对应的中断
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    //注册中断处理函数
    Sysytem_Register_IRQHandler(GPIO1_Combined_16_31_IRQn, GPIO1_IO16_31_IRQ_Handler, NULL);//其中GPIO1_IO18_IRQ_Handler是自己定义的中断处理函数.
    //使能GPIO中的指定引脚中断
    GPIO_Enable_Interrupt(GPIO1, 18);
    //使能定时器
    EPIT_Init(EPIT2, 0, 660000, 0, NULL);
}
