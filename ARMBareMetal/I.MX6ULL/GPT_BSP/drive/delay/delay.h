#ifndef __DELAY_H_
#define __DELAY_H_

#include "imx6ull.h"
#include "gpt.h"


void Delay_Init(void);
void Delay_Us(volatile unsigned int n);
void Delay_Ms(volatile unsigned int n);

#endif
