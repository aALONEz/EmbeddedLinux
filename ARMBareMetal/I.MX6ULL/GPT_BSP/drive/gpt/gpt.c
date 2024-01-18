#include "gpt.h"

GPT_Interrupt_Type_t GPT_Interrupt_Type = Output_Compare_1;


/// @brief GPT定时器初始化,初始化为restart模式,使用输出比较通道1
/// @param GPTx 哪个GPT,取值范围是GPT1,GPT2
/// @param Prescaler 分频值,实际分频系数是Prescaler + 1
/// @param CompareValue 比较寄存器填写的值
/// @param InterruptState 是否开启中断,可以是Enable 和 Disable
void GPT_Init(GPT_Type* GPTx, uint16_t Prescaler, uint32_t CompareValue, Peripheral_State_t InterruptState)
{
    GPT_Interrupt_Type = Output_Compare_1;
    if(Prescaler > 4095)//检查分频器的值
    {
        Prescaler = 4095;
    }
    //1.配置GPTx的CR寄存器
    GPTx->CR &= 0X0;//CR寄存器清零
    GPTx->CR |= (1 << 15);//软复位
    while(((GPTx->CR >> 15) & 0X01));//等待软复位完成
    GPTx->CR |= (1 << 1);//启用GPT定时器时重置计数器和预分频计数器的值.
    GPTx->CR |= (1 << 6);//配置外设时钟作为时钟源.ipk_clk
    //2.配置GPTx的PR寄存器,设置分频值
    GPTx->PR &= 0X0;//PR寄存器清零
    GPTx->PR |= (Prescaler << 0);
    //3.配置输出比较通道1寄存器的值.
    GPTx->OCR[0] &= 0X0;//OCR1寄存器清零
    GPTx->OCR[0] |= CompareValue;//设置OCR1寄存器的值
    //4.开启中断
    if(InterruptState == Enable)
    {
        GPTx->IR &= ~(1 << 0);//清零对应中断位
        GPTx->IR |= (1 << 0);//配置输出比较通道1使能
        if(GPTx == GPT1)
        {
            //开启GIC对应中断ID
            GIC_EnableIRQ(GPT1_IRQn);
            //注册中断服务函数
            Sysytem_Register_IRQHandler(GPT1_IRQn, GPT1_IRQ_Handler, (void*)(&GPT_Interrupt_Type));
        }
        else
        {
            //开启GIC对应中断ID
            GIC_EnableIRQ(GPT2_IRQn);
            Sysytem_Register_IRQHandler(GPT2_IRQn, GPT2_IRQ_Handler, (void*)(&GPT_Interrupt_Type));
        }
    }
    GPT_Enable(GPTx, Disable);
}

/// @brief GPT定时器模式启用/禁用
/// @param GPTx 哪个GPT,取值范围是GPT1,GPT2
/// @param GPT_Statue 要设置GPT定时器的状态,可以是Enable或者Disable
void GPT_Enable(GPT_Type* GPTx, Peripheral_State_t GPT_Statue)
{
    if(GPT_Statue == Enable)
    {
        GPTx->CR |= (1 << 0);
    }
    else
    {
        GPTx->CR &= ~(1 << 0);
    }
}

/// @brief 获取GPT指定中断的状态
/// @param GPTx 哪个GPT,取值范围是GPT1,GPT2
/// @param GPT_Interrupt_Type 中断类型
/// @return 指定中断的状态
uint8_t GPT_Inspect_InterruptBit(GPT_Type* GPTx, GPT_Interrupt_Type_t GPT_Interrupt_Type)
{
    return (((GPTx->SR) >> GPT_Interrupt_Type) & 0X01);
}

/// @brief 清除GPT指定中断的标志位
/// @param GPTx 哪个GPT,取值范围是GPT1,GPT2
/// @param GPT_Interrupt_Type 中断类型
void GPT_Clean_InterruptBit(GPT_Type* GPTx, GPT_Interrupt_Type_t GPT_Interrupt_Type)
{
    GPTx->SR |= (1 << GPT_Interrupt_Type);
}

/// @brief 返回计数器当前的值
/// @param GPTx 哪个GPT,取值范围是GPT1,GPT2
/// @return 当前GPT定时器的计数器的值
uint32_t GPT_ReadCount(GPT_Type* GPTx)
{
    return (GPTx->CNT);
}
