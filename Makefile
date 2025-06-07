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

# Source and object files (tự động lấy tất cả file .c trong src)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

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

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/startup.o: $(STARTUP)
	$(CC) -x assembler-with-cpp -c $< -o $@

$(TARGET).elf: $(OBJS) $(BUILDDIR)/startup.o
	$(CC) $(CFLAGS) $(OBJS) $(BUILDDIR)/startup.o -o $@ $(LDFLAGS)
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILDDIR) *.elf *.bin

flash: $(TARGET).bin
	JLink.exe -CommanderScript flash.jlink

.PHONY: all clean flash