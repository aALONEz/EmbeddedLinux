.global _start          //声明全局符号"_start"
.global _bss_start      //声明全局符号"_bss_start"
.global _bss_end        //声明全局符号"_bss_end"

_bss_start:
    .word __bss_start   //.word 是一个伪指令，用于在内存中分配一个字（32位，4个字节）的空间，并将指定的数值存储在这个位置。这个指令通常用于初始化变量，存储常数或者地址。这里也就是将链接脚本__bss_start的值存放在_bss_start这个全局符号里面

_bss_end:
    .word __bss_end

_start:
    //配置CPSR寄存器,将处理器配置为SVC模式
    mrs r0, cpsr        //使用mrs指令读出cpsr寄存器的值
    bic r0, r0, #0X1F   //使用bic按位清零指令,将r0的值低5位清零
    orr r0, r0, #0X13   //使用orr按位或指令,将r0的值或等于0X13赋值给r0
    msr cpsr, r0        //使用,msr指令将r0寄存器的值写入到cpsr

    //清除bss段,bss段就是定义但是没有初始化的变量
    ldr r0, _bss_start      //获取全局符号_bss_start保存的值,并存到r0寄存器中
    ldr r1, _bss_end        //获取全局符号_bss_end保存的值,并存到r1寄存器中
    mov r2, #0

bss_loop:
    stmia r0!, {r2}         //stmia指令:向r0这个地址写入r2寄存器里面的值,感叹号"!"表示在执行操作之后递增寄存器的值。类似C语言的++
    cmp r0, r1              //比较r0和r1的值
    ble bss_loop            //ble指令是两个指令的组合,b就是跳转.le是小于等于.也就是当上面的cmp指令r0的值满足小于等于r1的值这个条件就会跳转到bss_loop.如果不满足就执行下面的配置SP指针的代码

    //配置SP指针
    ldr sp, = 0X80400000    //配置SP寄存器的值0X80400000,也就是将栈顶指针配置到0X80400000
    b main                  //使用b指令跳转到main函数。
