/* Linker Script for STM32F103C6 (Cortex-M3) */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x8000000, LENGTH = 32K   
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 10K  
}

SECTIONS
{
    /* Interrupt Vector Table */
    .isr_vector :
    {
		. = ALIGN(4);
        KEEP(*(.isr_vector))   /* Keep the vector table in the binary */
		. = ALIGN(4);
	} > FLASH

    /* Code section */
    .text :
    {
		. = ALIGN(4);
        *(.text)      
		*(.text*) 
        *(.rodata*)   
		. = ALIGN(4);
        _E_text = .;   
    } > FLASH

    /* Initialized data section */
    .data : 
    {
		. = ALIGN(4);
        _S_data = .;   
        *(.data)       
		*(.data*) 
		. = ALIGN(4);
        _E_data = .;    
    } > SRAM AT > FLASH
	
	. = ALIGN(4);

    /* Uninitialized data (BSS) */
    .bss :
    {
        _S_bss = .;     
        *(.bss) 
		*(.bss*) 
		. = ALIGN(4);
        _E_bss = .;    
    } > SRAM
}
