// Startup.c
// ENG. Nouran

#include <stadint.h>

extern int main(void);

void Reset_Handler(void);
void Default_Handler(void) { Reset_Handler(); }

void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)     __attribute__((weak, alias("Default_Handler")));

// Stack size: booking 1024 bytes
static unsigned long stack_top[256];

// Vector Table
__attribute__((section(".vectors")))
void (* const g_pfnVectors[])() = { 
    (void (*)()) ((unsigned long) stack_top + sizeof(stack_top)),
    &Reset_Handler,
    &NMI_Handler,
    &HardFault_Handler,
    &MemManage_Handler,
    &BusFault_Handler,
    &UsageFault_Handler,
    0,
    0,
    0,
    0,
    &SVC_Handler,
    &DebugMon_Handler,
    0,
    &PendSV_Handler,
    &SysTick_Handler,
};

extern unsigned int _E_text;
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(void) {
    unsigned int i;

    // Copy data section from FLASH to SRAM
    unsigned int data_size = (unsigned char *)&_E_data - (unsigned char *)&_S_data;
    unsigned char *P_src = (unsigned char *)&_E_text;
    unsigned char *P_dst = (unsigned char *)&_S_data;

    for (i = 0; i < data_size; i++) 
        *((unsigned char *)P_dst++) = *((unsigned char *)P_src++);

    // Initialize BSS section to 0
    unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
    P_dst = (unsigned char *)&_S_bss;
    for (i = 0; i < bss_size; i++) 
        *((unsigned char *)P_dst++) = 0;

    // Jump to main
    main();
}
