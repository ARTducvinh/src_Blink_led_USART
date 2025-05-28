TARGET = test_led
BUILD_DIR = build
SRC = src/main.c src/system_stm32f401xx.c
STARTUP = startup_stm32f401xc.s
LDSCRIPT = STM32F401XX_FLASH.ld

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS = $(MCU) -Wall -O0 -g -Iinc
LDFLAGS = -T$(LDSCRIPT) -nostartfiles -Wl,--gc-sections
ASFLAGS = $(MCU)
BINFLAGS = -O binary

OBJ = $(SRC:src/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/startup.o
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).bin

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/startup.o: $(STARTUP) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(ELF): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SZ) $@

$(BIN): $(ELF)
	$(CP) $(BINFLAGS) $< $@

clean:
	rm -rf $(BUILD_DIR)

flash: $(BIN)
	JLink.exe -device STM32F401CC -if SWD -speed 4000 -autoconnect 1 -CommanderScript flash.jlink
