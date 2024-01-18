#ifndef __GPIO_H_
#define __GPIO_H_

//引入相关头文件
#include "imx6ull.h"
#include "int.h"

//中断触发方式 枚举
typedef enum
{
    Low_Level = 0,//低电平触发
    High_Level,//高电平触发
    Rising_Edge,//上升沿触发
    Falling_Edge,//下降沿触发
    Bilateral_Edge,//双边沿触发
    Disable_Trigger,//不触发
}GPIO_Bits_ICR_t;

//输入or输出枚举
typedef enum
{
    Input = 0,
    Output,
}GPIO_Pin_Direction_t;

//GPIO_Pin电平状态
typedef enum
{
    LowLevel = 0U,
    HighLevel,
}BitValue_t;

//GPIO_Pin配置结构体
typedef struct
{
    GPIO_Pin_Direction_t Direction;
    uint8_t OutputLogic;
    GPIO_Bits_ICR_t Int_Mode;
}GPIO_Pin_Config_t;

//相关函数声明
void GPIO_Init(GPIO_Type *Base, uint32_t Pin, GPIO_Pin_Config_t *Config);
void GPIO_PinWrite(GPIO_Type *Base, uint32_t Pin, BitValue_t Value);
uint8_t GPIO_PinRead(GPIO_Type *Base, uint32_t Pin);
uint8_t GPIO_Inspect_InterruptBit(GPIO_Type* Base, uint32_t Pin);
void GPIO_Clean_InterruptBit(GPIO_Type* Base, uint32_t Pin);
void GPIO_Disable_Interrupt(GPIO_Type* Base, uint32_t Pin);
void GPIO_Enable_Interrupt(GPIO_Type* Base, uint32_t Pin);
void GPIO_Interrupt_Init(GPIO_Type* Base, const uint32_t Pin, GPIO_Bits_ICR_t Pin_Mode);

#endif // !__GPIO_H_