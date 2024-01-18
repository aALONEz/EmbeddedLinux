#include "exti.h"
#include "epit.h"
#include "led.h"

uint8_t LED_Status = 0;

/// @brief GPIO1_IO18的中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 要传递给中断处理函数的参数,void*
void GPIO1_IO18_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    if(GPIO_PinRead(GPIO1, 18) == 0)
    {
        LED_Switch(LED0, LED_Status);
        LED_Status = !LED_Status;

        //清除中断标志位.
        GPIO_Clean_InterruptBit(GPIO1, 18);
    }
}

/// @brief EPIT1的中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 要传递给中断处理函数的参数,void*
void EPIT1_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    if(EPIT_Inspect_InterruptBit(EPIT1) == 1)
    {
        LED_Switch(LED0, LED_Status);
        LED_Status = !LED_Status;

        //清除中断标志位.
        EPIT_Clean_InterruptBit(EPIT1);
    }
}

/// @brief EPIT2的中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 要传递给中断处理函数的参数,void*
void EPIT2_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    if(EPIT_Inspect_InterruptBit(EPIT2) == 1)
    {
        //清除中断标志位.
        EPIT_Clean_InterruptBit(EPIT2);
    }
}
