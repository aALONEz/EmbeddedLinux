#ifndef __GPIO_H_
#define __GPIO_H_

//引入相关头文件
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

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
}GPIO_Pin_Config_t;

//相关函数声明
void GPIO_Init(GPIO_Type *Base, uint32_t Pin, GPIO_Pin_Config_t *Config);
void GPIO_PinWrite(GPIO_Type *Base, uint32_t Pin, BitValue_t Value);
BitValue_t GPIO_PinRead(GPIO_Type *Base, uint32_t Pin);

#endif // !__GPIO_H_