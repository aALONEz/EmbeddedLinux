#include "epit.h"
#include "led.h"
#include "beep.h"
#include "gpio.h"
#include "gpt.h"

uint8_t BEEP_Statue = 0;
uint8_t LED_Status = 0;

/// @brief GPIO1_IO16~GPIO1_IO31的中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 要传递给中断处理函数的参数,void*
void GPIO1_IO16_31_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    //按键中断,也就是GPIO1_IO18的外部中断
    if(GPIO_Inspect_InterruptBit(GPIO1, 18) == 1)
    {
        //开启定时器2(EPIT2)
        EPIT_Enable(EPIT2, Enable);
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
        //EPIT1中断要做的事情

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
        //失能定时EPIT2
        EPIT_Enable(EPIT2, Disable);
        //联动按键的操作
        if(GPIO_PinRead(GPIO1, 18) == LowLevel)
        {
            //要执行的操作
            if(BEEP_Statue == 0)
            {
                BEEP_Switch(ON);
                BEEP_Statue = 1;
            }
            else if(BEEP_Statue != 0)
            {
                BEEP_Switch(OFF);
                BEEP_Statue = 0;
            }
        }
        //清除中断标志位.
        EPIT_Clean_InterruptBit(EPIT2);
    }
}

/// @brief GPT1中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 传递给中断处理函数的参数
void GPT1_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    GPT_Interrupt_Type_t GPT_Interrupt_Type = *(GPT_Interrupt_Type_t*)Param;
    if(GPT_Inspect_InterruptBit(GPT1, GPT_Interrupt_Type) == 1)
    {
        switch (GPT_Interrupt_Type)
        {
        case Output_Compare_1:
        {
            //输出通道1中断要做的操作
            LED_Switch(LED0, LED_Status);
            LED_Status = !LED_Status;
            break;
        }
        case Output_Compare_2:
        {
            //输出通道2中断要做的操作


            break;
        }
        case Output_Compare_3:
        {
            //输出通道3中断要做的操作


            break;
        }
        case Input_Capture_1:
        {
            //输入通道1中断要做的操作


            break;
        }
        case Input_Capture_2:
        {
            //输入通道1中断要做的操作


            break;
        }
        default:
        {
            //溢出中断要做的操作

            break;
        }
        }
        //清除中断标志位
        GPT_Clean_InterruptBit(GPT1, GPT_Interrupt_Type);
    }
}

/// @brief GPT2中断处理函数
/// @param Gicc_Iar 中断ID
/// @param Param 传递给中断处理函数的参数
void GPT2_IRQ_Handler(uint32_t Gicc_Iar, void* Param)
{
    GPT_Interrupt_Type_t GPT_Interrupt_Type = *(GPT_Interrupt_Type_t*)Param;
    if(GPT_Inspect_InterruptBit(GPT2, GPT_Interrupt_Type) == 1)
    {
        switch (GPT_Interrupt_Type)
        {
        case Output_Compare_1:
        {
            //输出通道1中断要做的操作
            
            break;
        }
        case Output_Compare_2:
        {
            //输出通道2中断要做的操作


            break;
        }
        case Output_Compare_3:
        {
            //输出通道3中断要做的操作


            break;
        }
        case Input_Capture_1:
        {
            //输入通道1中断要做的操作


            break;
        }
        case Input_Capture_2:
        {
            //输入通道1中断要做的操作


            break;
        }
        default:
        {
            //溢出中断要做的操作

            break;
        }
        }
        //清除中断标志位
        GPT_Clean_InterruptBit(GPT2, GPT_Interrupt_Type);
    }
}
