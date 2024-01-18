#ifndef __GPT_H_
#define __GPT_H_

#include "imx6ull.h"
#include "int.h"

typedef enum
{
    Output_Compare_1 = 0,
    Output_Compare_2,
    Output_Compare_3,
    Input_Capture_1,
    Input_Capture_2,
    Rollover,
}GPT_Interrupt_Type_t;

extern void GPT1_IRQ_Handler(uint32_t Gicc_Iar, void* Param);
extern void GPT2_IRQ_Handler(uint32_t Gicc_Iar, void* Param);

void GPT_Init(GPT_Type* GPTx, uint16_t Prescaler, uint32_t CompareValue, Peripheral_State_t InterruptState);
void GPT_Enable(GPT_Type* GPTx, Peripheral_State_t GPT_Statue);
uint8_t GPT_Inspect_InterruptBit(GPT_Type* GPTx, GPT_Interrupt_Type_t GPT_Interrupt_Type);
void GPT_Clean_InterruptBit(GPT_Type* GPTx, GPT_Interrupt_Type_t GPT_Interrupt_Type);
uint32_t GPT_ReadCount(GPT_Type* GPTx);

#endif // !__GPT_H_