#include "epit.h"


/// @brief EPIT定时器初始化
/// @param EPITx 那个EPIT 此值两个取值范围EPIT1 EPIT2
/// @param Prescaler 分频寄存器的值,实际分频系数是Prescaler + 1
/// @param LoadValue 装载寄存器的值.
/// @param CompareValue 比较寄存器的值
/// @param Param 要传递给中断处理函数的参数
void EPIT_Init(EPIT_Type* EPITx, uint16_t Prescaler, uint32_t LoadValue, uint32_t CompareValue, void* Param)
{
    //1.判断Prescaler参数,Prescaler不可以大于4095
    if(Prescaler > 4095)
    {
        Prescaler = 4095;
    }
    //2.配置CR寄存器
    EPITx->CR = 0;//CR寄存器清零
    EPITx->CR |= (1 << 1);//默认使能EPIT为使用装载寄存器的值重装载计数器的值,而非继续计数器的值
    EPITx->CR |= (1 << 2);//使能比较中断
    EPITx->CR |= (1 << 3);//配置为set-and-forget模式.
    EPITx->CR |= (Prescaler << 4);//配置分频系数,实际分频值为Prescaler + 1
    EPITx->CR |= (0X01 << 24);//配置为使用ipg_clk时钟源
    //3.配置装载寄存器的值
    EPITx->LR &= 0;//清零装载寄存器的值
    EPITx->LR |= LoadValue;//配置装载寄存器的值
    //4.配置比较寄存器的值
    EPITx->CMPR &= 0;//清零比较寄存器的值
    EPITx->CMPR |= CompareValue;//配置比较寄存器的值
    if(EPITx == EPIT1)
    {
        //5.初始化中断
        GIC_EnableIRQ(EPIT1_IRQn);
        //6.注册中断服务函数
        Sysytem_Register_IRQHandler(EPIT1_IRQn, EPIT1_IRQ_Handler, Param);
    }
    else
    {
        //5.初始化中断
        GIC_EnableIRQ(EPIT2_IRQn);
        //6.注册中断服务函数
        Sysytem_Register_IRQHandler(EPIT2_IRQn, EPIT2_IRQ_Handler, Param);
    }
    //7.失能EPIT定时器
    EPIT_Enable(EPITx, Disable);
}

/// @brief EPIT定时器使能
/// @param EPITx 那个EPIT 此值两个取值范围EPIT1 EPIT2
/// @param Peripheral_State 要配置的状态,这个参数只有两个值Enable和Disable
void EPIT_Enable(EPIT_Type* EPITx, Peripheral_State_t Peripheral_State)
{
    if(Peripheral_State == Enable)
    {
        EPITx->CR |= (1 << 0);
    }
    else
    {
        EPITx->CR &= ~(1 << 0);
    }
}

/// @brief 清除EPIT中断标志位
/// @param EPITx 那个EPIT 此值两个取值范围EPIT1 EPIT2
void EPIT_Clean_InterruptBit(EPIT_Type* EPITx)
{
    //清除中断标志位,写SR寄存器位0 为1
    EPITx->SR |= (1 << 0);
}

/// @brief 查看EPIT中断标志位
/// @param EPITx 那个EPIT 此值两个取值范围EPIT1 EPIT2
/// @return 返回1表示有中断 返回0表示没有中断
uint8_t EPIT_Inspect_InterruptBit(EPIT_Type* EPITx)
{
    return ((EPITx->SR) & (1 << 0));
}