/*
	Linker Script Cortex-M3
	ENG. Nouran
*/

MEMORY
{
	Flash(rx) : ORIGIN = 0x08000000, LENGTH = 32K
	SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 10K
}

SECTIONS
{
	.text :
	{
		*(.vectors*)  
		*(.text*)     
		*(.rodata)   
	} > Flash
	
	.data :
	{
		*(.data)    
	} > SRAM

	.bss : 
	{
		*(.bss)      
	} > SRAM
}
