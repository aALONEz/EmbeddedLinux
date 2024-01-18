.global _start          //声明全局符号"_start"

_start:
    //下面的中断服务函数的函数名都是可以自定义的,但是它们的顺序和地址是不可以改变的.复位中断服务函数必须要在0X00的位置
    ldr pc, = Rest_Handler          //复位中断服务函数
    ldr pc, = Undefined_Handler     //未定义指令中断服务函数
    ldr pc, = SVC_Handler           //SVC中断服务函数
    ldr pc, = PreAbort_Handler      //预取中止中断服务函数
    ldr pc, = DataAbort_Handler     //数据中止中断服务函数
    ldr pc, = NotUsed_Handler       //未使用,站位用非中断服务函数
    ldr pc, = IRQ_Handler           //IRQ中断服务函数
    ldr pc, = FIQ_Handler           //FIQ中断服务函数

//复位中断服务函数
Rest_Handler:
    //关闭IRQ中断
    cpsid i                         //关闭IRQ

    //关闭I/DCache 和 MMU 修改SCTLR寄存器,使用读改写方式 Cortex-A系列的都要这么操作
    MRC p15, 0, r0, c1, c0, 0       //读取SCTLR寄存器的数据到r0寄存器
    bic r0, r0, #(1 << 12)          //关闭ICache
    bic r0, r0, #(1 << 11)          //关闭分支预测
    bic r0, r0, #(1 << 2)           //关闭DCache
    bic r0, r0, #(1 << 1)           //关闭对齐故障检查
    bic r0, r0, #(1 << 0)           //关闭MMU
    MCR p15, 0, r0, c1, c0, 0       //将修改后的r0寄存器的值写入到SCTLR寄存器

    //配置中断向量偏移,Cortex-A系列的都要这么操作
    ldr r0, = 0X87800000            //将r0里面保存新的中断向量的首地址
    dsb                             //数据同步
    isb                             //指令同步
    MCR p15, 0, r0, c12, c0, 0      //将r0寄存器的值写入到VBAR寄存器
    dsb                             //数据同步
    isb                             //指令同步

.global _bss_start      //声明全局符号"_bss_start"
.global _bss_end        //声明全局符号"_bss_end"

_bss_start:
    .word __bss_start   //.word 是一个伪指令，用于在内存中分配一个字（32位，4个字节）的空间，并将指定的数值存储在这个位置。这个指令通常用于初始化变量，存储常数或者地址。这里也就是将链接脚本__bss_start的值存放在_bss_start这个全局符号里面

_bss_end:
    .word __bss_end

        //清除bss段,bss段就是定义但是没有初始化的变量
    ldr r0, _bss_start      //获取全局符号_bss_start保存的值,并存到r0寄存器中
    ldr r1, _bss_end        //获取全局符号_bss_end保存的值,并存到r1寄存器中
    mov r2, #0

bss_loop:
    stmia r0!, {r2}         //stmia指令:向r0这个地址写入r2寄存器里面的值,感叹号"!"表示在执行操作之后递增寄存器的值。类似C语言的++
    cmp r0, r1              //比较r0和r1的值
    ble bss_loop            //ble指令是两个指令的组合,b就是跳转.le是小于等于.也就是当上面的cmp指令r0的值满足小于等于r1的值这个条件就会跳转到bss_loop.如果不满足就执行下面的配置SP指针的代码

    //配置IRQ模式,SYS模式,SVC模式的SP指针

        //配置CPSR寄存器,将处理器配置为IRQ模式
    mrs r0, cpsr        //使用mrs指令读出cpsr寄存器的值
    bic r0, r0, #0X1F   //使用bic按位清零指令,将r0的值低5位清零
    orr r0, r0, #0X12   //使用orr按位或指令,将r0的值或等于0X12赋值给r0
    msr cpsr, r0        //使用,msr指令将r0寄存器的值写入到cpsr
        //配置IRQ模式SP指针
    ldr sp, = 0X80C00000    //配置SP寄存器的值0X80400000,也就是将栈顶指针配置到0X80400000

        //配置CPSR寄存器,将处理器配置为SYS模式
    mrs r0, cpsr        //使用mrs指令读出cpsr寄存器的值
    bic r0, r0, #0X1F   //使用bic按位清零指令,将r0的值低5位清零
    orr r0, r0, #0X1F   //使用orr按位或指令,将r0的值或等于0X1F赋值给r0
    msr cpsr, r0        //使用,msr指令将r0寄存器的值写入到cpsr
        //配置SYS模式SP指针
    ldr sp, = 0X80800000    //配置SP寄存器的值0X80400000,也就是将栈顶指针配置到0X80400000

        //配置CPSR寄存器,将处理器配置为SVC模式
    mrs r0, cpsr        //使用mrs指令读出cpsr寄存器的值
    bic r0, r0, #0X1F   //使用bic按位清零指令,将r0的值低5位清零
    orr r0, r0, #0X13   //使用orr按位或指令,将r0的值或等于0X13赋值给r0
    msr cpsr, r0        //使用,msr指令将r0寄存器的值写入到cpsr
        //配置SVC模式SP指针
    ldr sp, = 0X80400000    //配置SP寄存器的值0X80400000,也就是将栈顶指针配置到0X80400000

        //打开IRQ中断
    cpsie i

        //跳转到main函数
    b main                  //使用b指令跳转到main函数。

//未定义指令中断服务函数
Undefined_Handler:
    ldr r0, = Undefined_Handler
    bx r0

//SVC中断服务函数
SVC_Handler:
    ldr r0, = SVC_Handler
    bx r0

//预取中止中断服务函数
PreAbort_Handler:
    ldr r0, = PreAbort_Handler
    bx r0

//数据中止中断服务函数
DataAbort_Handler:
    ldr r0, = DataAbort_Handler
    bx r0

//未使用,站位用非中断服务函数
NotUsed_Handler:
    ldr r0, = NotUsed_Handler
    bx r0

//IRQ中断服务函数
IRQ_Handler:
    //进入中断首先要保存现场,就是要将所有寄存器的值都压入栈中保存,然后再通过CP15协处理器读取GIC控制器指定存放触发中断的中断ID寄存器,然后将其值保存到r0寄存器,然后再进入SVC模式然后保护lr寄存器的值
    //进入system_irqhandler函数然后通过r0寄存器判断是那个中断ID,然后再调用其对应的中断执行函数,等待中断执行函数执行完成,接着就是出栈和进入IRQ模式写GICC_EOIR寄存器然后恢复现场.就完成了一次中断的处理

    push {lr}                           //保存lr的值,将lr的值压入栈中.lr寄存器又叫做链接寄存器主要是
                                        //用于存储函数调用或者异常返回时的返回地址。当一个函数被调用时，
                                        //调用指令会将返回地址（即调用该函数的下一条指令的地址）存储在 LR 寄存器中，
                                        //以便在函数执行结束后返回到正确的位置。

    push {r0-r3, r12}                   //将r0~r3和r12寄存器当前的值压入栈中,IRQ中断触发会保存r4~r11寄存器的值,所以这里不需要保存.只需要保存它没有保存到的寄存器

    mrs r0, spsr                        //将特殊寄存器spsr的值复制一份放到r0寄存器
    push {r0}                           //将r0寄存器当前的值压入栈中

    MRC p15, 4, r1, c15, c0, 0          //读取CP15协处理器的CBAR寄存器的值到r1寄存器,CBAR寄存器是用来保存GIC控制的寄存器组首地址,当GIC控制的寄存器组首地址偏移0X1000~0X1FFF为GIC的分发器.
                                        //偏移0X2000~0X3FFF为CPU接口端.当知道这些寄存器那么就可以访问GIC了.

    add r1, r1, #0X2000                 //r1寄存器当前的值加0X2000,上面r1寄存器保存GIC寄存器组的首地址,那么偏移0X2000刚好就是CPU接口端寄存器组的首地址
    ldr r0, [r1, #0XC]                  //再将r1寄存器当前的值偏移0XC(偏移0XC就是GICC_IAR寄存器,GICC_IAR寄存器位0~位9可以读取到中断ID),然后再读取偏移后的地址的值,将其值放到r0寄存器
    push {r0, r1}                       //将r0寄存器和r1寄存器当前的值压入栈中

    cps #0X13                           //cps 指令用于控制处理器的程序状态。这里是进入SVC模式,允许其他中断再次进入,因为一旦触发中断,那么就会进入IRQ模式,此时就是从IRQ模式切换到SVC模式

    push {lr}                           //将SVC模式的lr寄存器的当前值压入栈中
    ldr r2, = System_IRQHandler         //加载C语言中断处理函数的地址到r2寄存器.方便后续直接跳转,这个函数有一个参数,汇编里面要给C语言函数传参,要将参数的值保存在r0~r2寄存器里面(仅限参数小于三个),
                                        //我们这里这个函数就是要使用r0寄存器的值,也就是GICC_IAR寄存器的值.来检测是那个中断ID

    blx r2                              //跳转并运行到r2寄存器里面的地址

    pop {lr}                            //当执行完中断处理函数之后会回到这条汇编代码,然后将刚才压入栈中的值(push {lr}压入的lr当时的值)弹出给lr寄存器.也就是当前lr寄存器的值就是刚才压栈时lr寄存器的值
    cps #0X12                           //进入IRQ模式
    pop {r0, r1}                        //将刚才push {r0, r1}这条指令压入栈中的r0,r1当时的值弹出栈并将值给r0,r1
    str r0, [r1, #0X10]                 //中断执行完成,写GICC_EOIR寄存器,将r0寄存器的值(GICC_IAR寄存器的值)写入到[r1, #0X10](r1寄存器保存着CPU接口端寄存器组的首地址.r1偏移0X10是GICC_EOIR寄存器)
                                        //这里主要是将产生中断的中断ID值写入到GICC_EOIR寄存器,r0寄存器里面保存的就是中断ID值

    pop {r0}                            //将122行代码push {r0}压入的r0寄存器的值弹出给r0寄存器
    MSR spsr_cxsf, r0                   //将r0寄存器的值写入到spsr特殊寄存器的cxsf字段

    pop {r0-r3, r12}                    //将119行代码push {r0-r3, r12}压入的r0-r3, r12的值弹出给对应的寄存器
    pop {lr}                            //将114行代码push {lr}压入的lr寄存器的值,弹出到lr寄存器
    subs pc, lr, #4                     //subs 是减法指令，用于将第三个操作数的值减去第二个操作数的值，并将结果存储到第一个操作数中。
                                        //在这里，pc 是程序计数器寄存器，lr 是链接寄存器，#4 是一个立即数，代表要减去的值。

                                        //将链接寄存器（LR 寄存器）的值减去 4，然后将结果存储到程序计数器（PC 寄存器）中，
                                        //从而实现跳转到 LR 寄存器的值减去 4 的地址。


//FIQ中断服务函数
FIQ_Handler:
    ldr r0, = FIQ_Handler
    bx r0

