ASFLAGS = -mcpu=arm9tdmi  -gstabs
CFLAGS = -mcpu=arm9tdmi -Wall -g -nostdlib -nodefaultlibs -O0 -ffreestanding -I.
LDFLAGS = -Tled_test.lds -Wl,--build-id=none -nostartfiles -Lgcc -nostdlib -nodefaultlibs -L.
OBJS = led_test.o clock_pm.o uart.o main.o common.o wdt.o gpio_def.o led.o spkr.o interrupt.o sdram.o nand.o
EXELOADER = mdk_loader.elf

$(EXELOADER): $(OBJS)
	arm-linux-gnueabi-gcc -Wall -o $(EXELOADER) $(OBJS) $(LDFLAGS)
	arm-linux-gnueabi-objcopy -O binary $(EXELOADER) mdk_loader.bin
	ls -al mdk_loader.bin

%.o:%.s
	arm-linux-gnueabi-as $(ASFLAGS) $< -o $@

%.o:%.c
	arm-linux-gnueabi-gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(EXE)
	rm -f *.bin
	rm -f *.elf

