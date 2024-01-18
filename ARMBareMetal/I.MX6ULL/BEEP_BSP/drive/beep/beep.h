#ifndef _BEEP_H_
#define _BEEP_H_

//引入相关头文件
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

//函数声明相关
void BEEP_Init(void);
void BEEP_Switch(char Status);

#endif // !_BEEP_H_