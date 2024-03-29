.global _start

_start:
    //设置处理器进入SVC模式
    mrs r0, cpsr        //读取cpsr的值存放到r0寄存器
    bic r0, r0, #0X1F   //按位清零,将寄存器r0的值与立即数0x1F进行按位清零操作(需要清零哪一位就对哪一位,立即数对应的位设置为1)，结果存入r0
    orr r0, r0, #0X13   //将r0寄存器按位或立即数0X13
    msr cpsr, r0        //将r0寄存器写入到cpsr寄存器.将设置处理器进入SVC模式

    //如果是其他的处理器根据其情况还要初始化DDR

    //设置SP指针(栈顶指针)
    ldr sp, = 0X80400000//配置sp寄存器的地址
    b main              //跳转到C语言的main函数
