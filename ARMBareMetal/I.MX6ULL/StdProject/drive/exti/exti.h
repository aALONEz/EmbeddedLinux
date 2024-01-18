#ifndef __EXTI_H_
#define __EXTI_H_

//引入相关头文件
#include "imx6ull.h"
#include "gpio.h"

extern void GPIO1_IO18_IRQ_Handler(uint32_t Gicc_Iar, void* Param);


void GPIO1_IO18_Interrupt_Init(void);


#endif // !__EXTI_H_