#定义变量   ?=表示如果该变量没有被赋值才对这个变量进行赋值
CROSS_COMPILE 	?= arm-linux-gnueabihf-
NAME			?= CLK#工程名

GCC 			:= $(CROSS_COMPILE)gcc# :=表示变量的值会在定义时立即展开，而不是在使用时才展开。也就是当使用变量对另一个变量的赋值的时候这个时候需要赋值变量立即展开,而不是赋值一个变量名在这里,而是把变量名所代表的内容赋值给被赋值变量.
LD 				:= $(CROSS_COMPILE)ld -z noexecstack#添加-z noexecstack可以告诉链接器不要将可执行堆栈标记为可执行。以免没有.note.GNU-stack 段导致报警警告
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

#头文件相关路径
INCUDIRS		:= 	imx6ull \
					drive/clk \
					drive/led \
					drive/beep \
					drive/key \
					drive/gpio \
					drive/delay

#源文件相关路径
SRCDIRS			:= 	project \
					drive/clk \
					drive/led \
					drive/beep \
					drive/key \
					drive/gpio \
					drive/delay

INCLUDE			:= $(patsubst  %, -I %, $(INCUDIRS))

SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR		:= $(notdir $(SFILES))
CFILENDIR		:= $(notdir $(CFILES))

SOBJS			:= $(patsubst  %, obj/%, $(SFILENDIR:.s=.o))
COBJS			:= $(patsubst  %, obj/%, $(CFILENDIR:.c=.o))

OBJS 			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY : clean

$(NAME).bin : $(OBJS)
	$(LD) -Timx6ull.lds -o $(NAME).elf $^
	$(OBJCOPY) -O binary -S $(NAME).elf $@
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

$(SOBJS) : obj/%.o : %.s
	$(GCC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(GCC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

clean:
	rm -rf $(OBJS) $(NAME).bin $(NAME).elf $(NAME).dis load.imx load.img
