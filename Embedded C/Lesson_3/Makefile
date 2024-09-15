#@ Nouran
# Make Script

CC= arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS= -I .
LIBS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
As= $(wildcard *.s)
AsOBJ= $(As:.s=.o)
ProjectName= learn-in-depth

all: $(ProjectName).bin
	@echo "*************************"
	@echo "*** Build is Done ..! ***"
	@echo "*************************"

# Assembly.s ---> file.o 
$(AsOBJ): $(As)
	$(CC)as.exe $(CFLAGS) $< -o $@
	@echo "*** Finished building: $@ ***"
	@echo ' '

# code.c ---> obj.o 
%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@
	@echo "*** Finished building: $@ ***"
	@echo ' '
	
# Linker Stage
$(ProjectName).elf: $(AsOBJ) $(OBJ)
	$(CC)ld.exe -T linkerScript.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	@echo "*** Finished building: $@ ***"
	@echo ' '
	
$(ProjectName).bin: $(ProjectName).elf
	$(CC)objcopy.exe -O binary $< $@
	@echo "*** Finished building: $@ ***"
	@echo ' '

# Clean/Remove Stage
clean_all:
	rm *.o *.bin *.elf
	@echo "*** Finished remove (.o) (.elf) (.bin) ***"
	@echo ' '
	
clean_o:
	rm *.o 
	@echo "*** Finished remove (.o) ***"
	@echo ' '
	
clean:
	rm *.bin *.elf
	@echo "*** Finished remove (.elf) (.bin) ***"
	@echo ' '
