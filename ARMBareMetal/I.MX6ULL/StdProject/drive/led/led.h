#ifndef __LED_H_
#define __LED_H_

//引入相关头文件
#include "clk.h"

#define LED0 0

void LED_Init(void);
void LED_Switch(int LED, int Status);

#endif // !__LED_H_
