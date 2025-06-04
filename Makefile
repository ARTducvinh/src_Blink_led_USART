# Project name
TARGET = main

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Paths
SRCDIR = src
INCDIR = inc
BUILDDIR = build

# Source and object files
SRCS = $(SRCDIR)/main.c $(SRCDIR)/system_stm32f4xx.c
OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/system_stm32f4xx.o $(BUILDDIR)/startup.o

# Startup and linker script
STARTUP = startup_stm32f401xc.s
LDSCRIPT = STM32F401XX_FLASH.ld

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O2 -I$(INCDIR) -ffreestanding
LDFLAGS = -T$(LDSCRIPT) -nostartfiles -nostdlib

# Build rules
all: $(BUILDDIR) $(TARGET).elf $(TARGET).bin

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/system_stm32f4xx.o: $(SRCDIR)/system_stm32f4xx.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/startup.o: $(STARTUP)
	$(CC) -x assembler-with-cpp -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILDDIR) *.elf *.bin

flash: $(TARGET).bin
	JLink.exe -CommanderScript flash.jlink

.PHONY: all clean flash