#定义变量   ?=表示如果该变量没有被赋值才对这个变量进行赋值
CROSS_COMPILE 	?= arm-linux-gnueabihf-
NAME			?= LED

OBJS 			?= start.o main.o

GCC 			:= $(CROSS_COMPILE)gcc# :=表示变量的值会在定义时立即展开，而不是在使用时才展开。也就是当使用变量对另一个变量的赋值的时候这个时候需要赋值变量立即展开,而不是赋值一个变量名在这里,而是把变量名所代表的内容赋值给被赋值变量.
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

$(NAME).bin : $(OBJS)
	$(LD) -Timx6ull.lds -o $(NAME).elf $^
	$(OBJCOPY) -O binary -S $(NAME).elf $@
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

%.o : %.c
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(NAME).bin $(NAME).elf $(NAME).dis load.imx load.img
