# Compiler and flags
CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -mthumb -g -gdwarf-2
LDFLAGS = -T STM32F103C6TX_FLASH.ld -nostartfiles

# Include directories
INCS = -I .

# Source files
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
AsOBJ = $(AS:.s=.o)

# Project name
ProjectName = High_Pressure_Detection

# Targets
all: $(ProjectName).hex
	@echo "**************************"
	@echo "***   Build Complete   ***"
	@echo "**************************"

# Assembly files to object files
$(AsOBJ): $(AS)
	$(CC)as $(CFLAGS) $< -o $@
	@echo "*** Finished building assembly: $@ ***"
	@echo " "

# C files to object files
%.o: %.c
	$(CC)gcc -c $(CFLAGS) $(INCS) $< -o $@
	@echo "*** Finished building object: $@ ***"
	@echo " "

# Linker stage
$(ProjectName).elf: $(AsOBJ) $(OBJ)
	$(CC)ld $(LDFLAGS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	@echo "*** Finished linking: $@ ***"
	@echo " "

# Create binary and hex files
$(ProjectName).bin: $(ProjectName).elf
	$(CC)objcopy -O binary $< $@
	@echo "*** Finished creating binary: $@ ***"
	@echo " "

$(ProjectName).hex: $(ProjectName).elf
	$(CC)objcopy -O ihex $< $@
	@echo "*** Finished creating hex: $@ ***"
	@echo " "

# Clean all generated files
clean_all:
	rm -f *.o *.bin *.elf *.hex *.map *.asm
	@echo "*** Cleaned all generated files ***"
	@echo " "

clean_o:
	rm -f *.o
	@echo "*** Cleaned object files ***"
	@echo " "
