#ifndef __REGISTER_H_
#define __REGISTER_H_

//定义要使用的寄存器
//时钟相关寄存器
#define CCM_CCGR0       *((volatile unsigned long*)0X020C4068)
#define CCM_CCGR1       *((volatile unsigned long*)0X020C406C)
#define CCM_CCGR2       *((volatile unsigned long*)0X020C4070)
#define CCM_CCGR3       *((volatile unsigned long*)0X020C4074)
#define CCM_CCGR4       *((volatile unsigned long*)0X020C4078)
#define CCM_CCGR5       *((volatile unsigned long*)0X020C407C)
#define CCM_CCGR6       *((volatile unsigned long*)0X020C4080)

//GPIO复用寄存器
#define MUX_GPIO1_IO03  *((volatile unsigned long*)0X020E0068)

//GPIO电气属性寄存器
#define PAD_GPIO1_IO03  *((volatile unsigned long*)0X020E02F4)

//GPIO电平状态寄存器
#define GPIO1_DR        *((volatile unsigned long*)0X0209C000)

//GPIO模式选择寄存器
#define GPIO1_GDIR      *((volatile unsigned long*)0X0209C004)

#endif
