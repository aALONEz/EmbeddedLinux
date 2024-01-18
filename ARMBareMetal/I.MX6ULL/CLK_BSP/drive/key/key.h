#ifndef __KEY_H_
#define __KEY_H_

//引入相关头文件
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "delay.h"
#include "gpio.h"

//相关函数声明
void KEY_Init(void);
char KEY_Get_Status(void);

#endif // !__KEY_H_