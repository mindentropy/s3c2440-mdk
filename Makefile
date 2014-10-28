ASFLAGS = -mcpu=arm9tdmi  -gstabs
CFLAGS = -mcpu=arm9tdmi -Wall -g -I.
LDFLAGS = -Tled_test.lds -Wl,--build-id=none -nostartfiles -Lgcc -L.
OBJS = led_test.o main.o
EXE = led_test.elf

$(EXE): $(OBJS)
	arm-linux-gnueabi-gcc -Wall -o $(EXE) $(OBJS) $(LDFLAGS)
	arm-linux-gnueabi-objcopy -O binary $(EXE) led_test.bin

%.o:%.s
	arm-linux-gnueabi-as $(ASFLAGS) $< -o $@

%.o:%.c
	arm-linux-gnueabi-gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(EXE)
	rm -f *.bin

