# Makefile for STM32F373 using cmsis and GNU toolchain.

# Files to include
C_SRC  = $(wildcard *.c)
C_SRC += $(wildcard usb/*.c)
C_SRC += $(wildcard fatfs/*.c)
C_SRC += $(wildcard protocols/*.c)
C_SRC += $(wildcard lib/STM32F0xx_StdPeriph_Driver/src/*.c)
C_SRC += $(wildcard lib/usb-fs/src/*.c)
C_SRC += $(wildcard lib/usb-device/src/*.c)

OBJECTS = $(patsubst %.c,%.o,$(C_SRC)) startup.o

PROJECT = rfid

LIBRARIES = 

INC  = -I. -Iusb -Iprotocols -Ifatfs
INC += -Ilib/CMSIS/Include -Ilib/CMSIS/Device/ST/STM32F0xx/Include
INC += -Ilib/STM32F0xx_StdPeriph_Driver/inc
INC += -Ilib/usb-fs/inc
INC += -Ilib/usb-device/inc

# Assembler, compiler, and linker flags
AFLAGS  = -mlittle-endian -mthumb -mcpu=cortex-m0 -g
CFLAGS  = $(AFLAGS) -O2 $(INC) -std=c99 -DUSE_STDPERIPH_DRIVER -Wall
CFLAGS += -DSTM32F042
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -fdata-sections -ffunction-sections
LFLAGS  = $(CFLAGS) -nostartfiles -Wl,--gc-sections

# Targets
all: $(PROJECT).elf
clean:
	-rm -f $(OBJECTS) *.elf *.bin *.map *.hex
$(PROJECT).hex: $(PROJECT).elf
	arm-none-eabi-objcopy -R .config $(PROJECT).elf -O ihex $(PROJECT).hex
$(PROJECT).bin: $(PROJECT).elf
	arm-none-eabi-objcopy -R .config -O binary $(PROJECT).elf $(PROJECT).bin
$(PROJECT).elf: $(OBJECTS)
	arm-none-eabi-gcc $(LFLAGS) -Tflash.ld -Wl,-Map=$(PROJECT).map -o $(PROJECT).elf $(OBJECTS) $(LIBRARIES)
startup.o: startup.s
	arm-none-eabi-as $(AFLAGS) startup.s -o startup.o
lib/%.o: lib/%.c
	arm-none-eabi-gcc $(CFLAGS) -c -o $@ $<
%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c -o $@ $<
gdb: $(PROJECT).elf
	arm-none-eabi-gdb $(PROJECT).elf -x init.gdb
load: $(PROJECT).elf
	arm-none-eabi-gdb $(PROJECT).elf -x init.gdb -ex load
loadquit: $(PROJECT).elf
	arm-none-eabi-gdb $(PROJECT).elf -batch -x init.gdb -ex load -ex kill -ex quit
stlink:
	st-util -p 4244
stload: $(PROJECT).bin
	st-flash write $(PROJECT).bin 0x8000000
sterase:
	st-flash erase
dfuload: $(PROJECT).bin
	dfu-util -d 0483:df11 -a 0 -s 0x8000000 -D $(PROJECT).bin
