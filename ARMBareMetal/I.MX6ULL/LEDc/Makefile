objname = LED

objs = start.o main.o

$(objname).bin : $(objs)#工程目标
	arm-linux-gnueabihf-ld -Timx6ull.lds $^ -o $(objname).elf
	arm-linux-gnueabihf-objcopy -O binary -S $(objname).elf $@
	arm-linux-gnueabihf-objdump -D -m arm $(objname).elf > $(objname).dis

%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(objname).bin $(objname).elf $(objname).dis load.imx load.img
