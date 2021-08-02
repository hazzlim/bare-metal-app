#include "system_MK66F18.h"

extern unsigned int _etext;
extern unsigned int _sdata;
extern unsigned int _edata;
extern unsigned int _sbss;
extern unsigned int _ebss;

#define SRAM_START   0x1FFF0000
#define SRAM_SIZE    (256 * 1024U) // 256KB
#define SRAM_END     ((SRAM_START) + (SRAM_SIZE))

#define STACK_TOP SRAM_END

// Prototype of main function
void main(void);

void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVCall_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMonitor_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void PendableSrvReq_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

unsigned int * vector_table[256] __attribute__((section(".isr_vector"))) = {
    (unsigned int *)    STACK_TOP,      // stack pointer
    (unsigned int *)    &Reset_Handler,
    (unsigned int *)    &NMI_Handler,
    (unsigned int *)    &HardFault_Handler,
    (unsigned int *)    &MemManage_Handler,
    (unsigned int *)    &BusFault_Handler,
    (unsigned int *)    &UsageFault_Handler,
    (unsigned int *)    0,
    (unsigned int *)    0,
    (unsigned int *)    0,
    (unsigned int *)    0,
    (unsigned int *)    &SVCall_Handler,
    (unsigned int *)    &DebugMonitor_Handler,
    (unsigned int *)    0,
    (unsigned int *)    &PendableSrvReq_Handler,
    (unsigned int *)    &SysTick_Handler
};

unsigned int flash_config[4] __attribute__((section(".flash_config"))) = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFE
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    /* Disable Watchdog */
    SystemInit();

    /* Copy data belonging to the `.data` section from its
    * load time position on flash (ROM) to its run time position
    * in SRAM.
    */
    unsigned int *data_flash_start = &_etext;
    unsigned int *data_ram_start_p = &_sdata;
    unsigned int *data_ram_end_p = &_edata;

    while (data_ram_start_p < data_ram_end_p) {
        *data_ram_start_p++ = *data_flash_start++;
    }

    /* Initialize data in the `.bss` section to zeros.
     */
    unsigned int *bss_start_p = &_sbss;
    unsigned int *bss_end_p = &_ebss;

    while (bss_start_p < bss_end_p) {
        *bss_start_p++ = 0;
    }

    /* Call the main function. */
    main();

    /* Loop */
    while(1);
}

