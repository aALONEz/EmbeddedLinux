#include "int.h"

static uint32_t IRQNesting;//中断嵌套了几次

//中断处理函数数组
System_IRQ_Handler_t IRQTable[NUMBER_OF_INT_VECTORS];

//初始化中断处理函数数组,就是给这个数组赋值一个初始值
void System_IRQTable_Init(void)
{
    IRQNesting = 0;
    for(uint32_t i = 0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        IRQTable[i].IRQHandler = Default_IRQHandler;
        IRQTable[i].UserParam = NULL;//默认参数为NULL
    }
}

//中断初始化函数
void Int_Init(void)
{
    //初始化GIC
    GIC_Init();
    #if 0
    //配置中断向量偏移,如果在start.s里面配置了这里就不需要配置了.
    __set_VBAR(0X87800000);//设置中断向量偏移起始地址为0X87800000
    #endif
    System_IRQTable_Init();//初始化中断处理函数数组
}

//具体的中断处理函数,汇编里面的IRQHandler会调用此函数
void System_IRQHandler(uint32_t Gicc_Iar)
{
    uint32_t INT_Num = Gicc_Iar & 0X3FF;
    //检查中断ID
    if(INT_Num >= NUMBER_OF_INT_VECTORS)
    {
        return;//中断ID不正确直接返回
    }
    //每次有中断就让中断嵌套加1
    IRQNesting++;
    //根据中断ID号读取IRQTable数组,来执行对应的中断服务函数
    IRQTable[INT_Num].IRQHandler(INT_Num, IRQTable[INT_Num].UserParam);
    //处理完中断服务函数就再让嵌套减减
    IRQNesting--;
}

//注册中断处理函数
void Sysytem_Register_IRQHandler(IRQn_Type IRQ, IRQ_Handler_t IRQHandler, void* UserParam)
{
    IRQTable[IRQ].IRQHandler = IRQHandler;
    IRQTable[IRQ].UserParam = UserParam;
}

//默认中断处理函数
void Default_IRQHandler(uint32_t Gicc_Iar, void* Param)
{
    for(;;);//死循环
}

