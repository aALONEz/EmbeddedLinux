objname = LED
objs = start.o main.o
ld = arm-linux-gnueabihf-ld
gcc = arm-linux-gnueabihf-gcc
objcopy = arm-linux-gnueabihf-objcopy
objdump = arm-linux-gnueabihf-objdump

$(objname).bin : $(objs)
	$(ld) -Timx6ull.lds -o $(objname).elf $^
	$(objcopy) -O binary -S $(objname).elf $@
	$(objdump) -D -m arm $(objname).elf > $(objname).dts

%.o : %.c
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(objname).elf $(objname).dts load.imx load.img $(objname).bin

burn:
	./imxdownload_windows $(objname).bin 
