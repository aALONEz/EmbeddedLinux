#ifndef __EPIT_H_
#define __EPIT_H_

#include "imx6ull.h"
#include "int.h"

//中断函数声明
extern void EPIT1_IRQ_Handler(uint32_t Gicc_Iar, void* Param);
extern void EPIT2_IRQ_Handler(uint32_t Gicc_Iar, void* Param);

//相关函数声明
void EPIT_Enable(EPIT_Type* EPITx, Peripheral_State_t Peripheral_State);
void EPIT_Init(EPIT_Type* EPITx, uint16_t Prescaler, uint32_t LoadValue, uint32_t CompareValue, void* Param);
void EPIT_Clean_InterruptBit(EPIT_Type* EPITx);
uint8_t EPIT_Inspect_InterruptBit(EPIT_Type* EPITx);

#endif // !__EPIT_H_
