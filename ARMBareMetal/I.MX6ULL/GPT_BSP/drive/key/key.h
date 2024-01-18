#ifndef __KEY_H_
#define __KEY_H_

//引入相关头文件
#include "imx6ull.h"
#include "delay.h"
#include "gpio.h"
#include "epit.h"

extern void GPIO1_IO16_31_IRQ_Handler(uint32_t Gicc_Iar, void* Param);

//相关函数声明
void KEY_Init(void);

#endif // !__KEY_H_