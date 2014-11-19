ASFLAGS = -mcpu=arm9tdmi  -gstabs
CFLAGS = -mcpu=arm9tdmi -Wall -g -nostdlib -nodefaultlibs -O0 -ffreestanding -I.
LDFLAGS =  -Wl,--build-id=none -nostartfiles -Lgcc -nostdlib -nodefaultlibs -L.
OS_OBJS = os_glue.o os_main.o
LOADER_OBJS = loader_glue.o loader_main.o
COMMON_OBJS = clock_pm.o sdram.o common.o interrupt.o uart.o wdt.o gpio_def.o led.o spkr.o nand.o
EXELOADER = mdk_loader.elf
EXEOS = mdk_os.elf
LOADER_LDSCRIPT = -Tloader.lds
OS_LDSCRIPT = -Tmdkos.lds
TOOLCHAIN_PREFIX=arm-linux-gnueabi-
CC = $(TOOLCHAIN_PREFIX)gcc
AS = $(TOOLCHAIN_PREFIX)as
LD = $(TOOLCHAIN_PREFIX)ld
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy

mdkloader: $(EXELOADER)

mdkos: $(EXEOS)


$(EXELOADER):  $(LOADER_OBJS) $(COMMON_OBJS)
	$(CC) -Wall -o $(EXELOADER) $(LOADER_OBJS) $(COMMON_OBJS) $(LOADER_LDSCRIPT) $(LDFLAGS) 
	$(OBJCOPY) -O binary $(EXELOADER) mdk_loader.bin
	ls -al mdk_loader.bin

$(EXEOS):  $(OS_OBJS) $(COMMON_OBJS)
	$(CC) -Wall -o $(EXEOS) $(OS_OBJS) $(COMMON_OBJS) $(OS_LDSCRIPT) $(LDFLAGS)
	$(OBJCOPY) -O binary $(EXEOS) mdk_os.bin
	ls -al mdk_os.bin

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(COMMON_OBJS)
	rm -f $(EXEOS)
	rm -f $(EXELOADER)
	rm -f $(OS_OBJS)
	rm -f $(LOADER_OBJS)
	rm -f *.bin
	rm -f *.elf

