objname = LED

$(objname).bin : $(objname).s
	arm-linux-gnueabihf-gcc -g -c $(objname).s -o $(objname).o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 $(objname).o -o $(objname).elf
	arm-linux-gnueabihf-objcopy -O binary -S -g $(objname).elf $(objname).bin
	arm-linux-gnueabihf-objdump -D $(objname).elf > $(objname).dis

clean:
	rm -rf *.o load.img load.imx $(objname).dis $(objname).bin $(objname).elf