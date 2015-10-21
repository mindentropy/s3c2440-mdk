# Please note that the linker processes the file in the order that is input. Hence 
# *_glue files should be the first file as the code is hand crafted assembly with
# interrupt vectors starting at the fixed address for e.g.: Reset vector starts 
# at 0x00000000 etc. Therefore the file should be placed at the start.
#

INC_DIR = include
COMMON_INC_DIR = $(INC_DIR)/common

OBJ_DIR := obj
SRC_DIR := src
LIB_DIR := lib
BIN_DIR := bin

COMMON_OBJ_DIR 	:= $(OBJ_DIR)/common
OS_OBJ_DIR 		:= $(OBJ_DIR)/os
LOADER_OBJ_DIR 	:= $(OBJ_DIR)/loader

COMMON_SRC_DIR := $(SRC_DIR)/common
LOADER_SRC_DIR := $(SRC_DIR)/loader
OS_SRC_DIR := $(SRC_DIR)/os

UPLOADER_DIR = test_uploader
UPLOADER := $(UPLOADER_DIR)

OS_OBJS = $(OS_OBJ_DIR)/os_glue.o $(OS_OBJ_DIR)/os_main.o $(OS_OBJ_DIR)/os_vector.o $(OS_OBJ_DIR)/cpu.o $(OS_OBJ_DIR)/cache.o $(OS_OBJ_DIR)/mmu.o
LOADER_OBJS = $(LOADER_OBJ_DIR)/loader_glue.o $(LOADER_OBJ_DIR)/loader_main.o

COMMON_SRC_FILES := $(foreach dir,$(COMMON_SRC_DIR),$(wildcard $(dir)/*.c))
COMMON_OBJS := $(patsubst $(COMMON_SRC_DIR)/%.c, $(COMMON_OBJ_DIR)/%.o,$(COMMON_SRC_FILES))

LOADER_AS_SRC_FILES := $(foreach dir,$(LOADER_SRC_DIR),$(wildcard $(dir)/*.s))
LOADER_AS_OBJ_FILES := $(patsubst $(LOADER_SRC_DIR)/%.s, $(LOADER_OBJ_DIR)/%.o,$(LOADER_AS_SRC_FILES))

OS_AS_SRC_FILES := $(foreach dir,$(OS_SRC_DIR),$(wildcard $(dir)/*.s))
OS_AS_OBJ_FILES := $(patsubst $(OS_SRC_DIR)/%.s,$(OS_OBJ_DIR)/%.o,$(OS_AS_SRC_FILES))

OS_SRC_FILES := $(foreach dir,$(OS_SRC_DIR),$(wildcard $(dir)/*.c))
OS_OBJ_FILES := $(patsubst $(OS_SRC_DIR)/%.c, $(OS_OBJ_DIR)/%.o,$(OS_SRC_FILES))

LOADER_SRC_FILES := $(foreach dir,$(LOADER_SRC_DIR),$(wildcard $(dir)/*.c))
LOADER_OBJ_FILES := $(patsubst $(LOADER_SRC_DIR)/%.c, $(LOADER_OBJ_DIR)/%.o,$(LOADER_SRC_FILES))


EXELOADER = $(BIN_DIR)/mdk_loader.elf
EXEOS = $(BIN_DIR)/mdk_os.elf
LOADER_LDSCRIPT = -Tloader.lds
OS_LDSCRIPT = -Tmdkos.lds

TOOLCHAIN_PREFIX=arm-linux-gnueabi-
CC = $(TOOLCHAIN_PREFIX)gcc
AS = $(TOOLCHAIN_PREFIX)as
LD = $(TOOLCHAIN_PREFIX)ld
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy

ASFLAGS = -mcpu=arm9tdmi  -gstabs
CFLAGS = -mcpu=arm9tdmi -Wall -g -nostdlib -nodefaultlibs -O0 -ffreestanding -I$(COMMON_INC_DIR)
LDFLAGS =  -Wl,--build-id=none -nostartfiles -Lgcc -nostdlib -nodefaultlibs -L.


#all: mdkloader mdkos
all: cscope_create mdkloader mdkos $(UPLOADER)
#all:  $(UPLOADER)

mdkloader: $(OBJ_DIR) $(COMMON_OBJ_DIR) $(LOADER_OBJ_DIR) $(BIN_DIR) $(EXELOADER)

mdkos: $(OBJ_DIR) $(COMMON_OBJ_DIR) $(OS_OBJ_DIR) $(BIN_DIR) $(EXEOS) 

$(UPLOADER):
	$(MAKE) --directory=$@
	

$(EXELOADER):  $(LOADER_AS_OBJ_FILES) $(LOADER_OBJ_FILES) $(COMMON_OBJS)
	$(CC) -Wall -o $(EXELOADER) $(LOADER_AS_OBJ_FILES) $(LOADER_OBJ_FILES) $(COMMON_OBJS) $(LOADER_LDSCRIPT) $(LDFLAGS) 
	$(OBJCOPY) -O binary $(EXELOADER) $(BIN_DIR)/mdk_loader.bin
	ls -al $(BIN_DIR)/mdk_loader.bin

$(EXEOS): $(OS_AS_OBJ_FILES) $(OS_OBJ_FILES) $(COMMON_OBJS) 
	$(CC) -Wall -o $(EXEOS) $(OS_AS_OBJ_FILES) $(OS_OBJ_FILES) $(COMMON_OBJS) $(OS_LDSCRIPT) $(LDFLAGS)
	$(OBJCOPY) -O binary $(EXEOS) $(BIN_DIR)/mdk_os.bin
	ls -al $(BIN_DIR)/mdk_os.bin

$(COMMON_OBJ_DIR)/%.o: $(COMMON_SRC_DIR)/%.c 
	$(CC) -c $(CFLAGS) $< -o $@

$(OS_OBJ_DIR)/%.o: $(OS_SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(OS_OBJ_DIR)/%.o: $(OS_SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(LOADER_OBJ_DIR)/%.o: $(LOADER_SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(LOADER_OBJ_DIR)/%.o: $(LOADER_SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(COMMON_OBJ_DIR):
	mkdir -p $(COMMON_OBJ_DIR)
	
$(LOADER_OBJ_DIR):
	mkdir -p $(LOADER_OBJ_DIR)

$(OS_OBJ_DIR):
	mkdir -p $(OS_OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean cleandir cleanall cscope_create test_uploader_clean $(UPLOADER)


cscope_create:
	cscope -R -q -k -b


cleanall: clean cleandir cscope_clean test_uploader_clean

clean:
	rm -fv $(BIN_DIR)/*
	rm -fv $(COMMON_OBJ_DIR)/*.o
	rm -fv $(LOADER_OBJ_DIR)/*.o
	rm -fv $(OS_OBJ_DIR)/*.o


cleandir:
	rm -df $(OS_OBJ_DIR)
	rm -df $(LOADER_OBJ_DIR)
	rm -df $(COMMON_OBJ_DIR)
	rm -df $(OBJ_DIR)
	rm -df $(BIN_DIR)

cscope_clean:
	rm -fv *.out

test_uploader_clean:
	make --directory=$(UPLOADER_DIR) clean
