#ifndef __INT_H_
#define __INT_H_

//引入相关头文件
#include "imx6ull.h"


/// @brief 中断处理函数模板,所有的中断处理函数都要是这个类型的
typedef void (*IRQ_Handler_t)(uint32_t Gicc_Iar, void* Param);

//中断处理函数结构体
typedef struct
{
    IRQ_Handler_t IRQHandler;//中断处理函数
    void* UserParam;//传递给中断处理函数的参数
}System_IRQ_Handler_t;

//相关函数声明
void Int_Init(void);
void Default_IRQHandler(uint32_t Gicc_Iar, void* Param);//默认中断处理函数
void Sysytem_Register_IRQHandler(IRQn_Type IRQ, IRQ_Handler_t IRQHandler, void* UserParam);//注册中断处理函数

#endif // !__INT_H_