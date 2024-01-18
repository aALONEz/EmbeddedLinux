.global _start //全局标号

_start:
    //使能所有外设时钟
    //CCGR0
    ldr r0, = 0X020C4068
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR1
    ldr r0, = 0X020C406C
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR2
    ldr r0, = 0X020C4070
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR3
    ldr r0, = 0X020C4074
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR4
    ldr r0, = 0X020C4078
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR5
    ldr r0, = 0X020C407C
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //CCGR6
    ldr r0, = 0X020C4080
    ldr r1, = 0XFFFFFFFF
    str r1, [r0]

    //配置IO复用
    ldr r0, = 0X020E0068//IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03寄存器地址
    ldr r1, = 0X00000005//要向寄存器写入的数据
    str r1, [r0]        //将0X00000005写入到0X020E0068寄存器

    //配置电气属性
    ldr r0, = 0X020E02F4//IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03寄存器地址
    ldr r1, = 0X00000070//要向寄存器写入的数据
    str r1, [r0]        //将0X00000070写入到0X020E0068寄存器.

    //配置GPIO模式
    ldr r0, = 0X0209C004//GPIO1_GDIR寄存器地址
    ldr r1, = 0X00000008//要向寄存器写入的数据
    str r1, [r0]        //将0X00000008写入到0X0209C004寄存器.

    //配置GPIO电平状态
    ldr r0, = 0X0209C000//GPIO1_DR寄存器地址
    ldr r1, = 0X00000000//要写入寄存器的值
    str r1, [r0]        //将0X00000000写入到0X0209C000寄存器.

    //编写一个死循环,当CPU执行完上面的代码之后下面如果没有死循环就不知道CPU在干嘛,此时CPU就是不知道在干嘛这个时候是不行的.
loop:
    b loop//b强制跳转

