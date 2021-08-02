#include "system_MK66F18.h"
#include <stdint.h>

extern uint32_t _stack_top;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

// Prototype of main function
void main(void);

void Default_Handler(void)
{
    while(1);
}

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

uint32_t * vector_table[256] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)    &_stack_top,      // stack pointer
    (uint32_t *)    &Reset_Handler,
    (uint32_t *)    &HardFault_Handler,
    (uint32_t *)    &MemManage_Handler,
    (uint32_t *)    &BusFault_Handler,
    (uint32_t *)    &UsageFault_Handler,
    (uint32_t *)    0,
    (uint32_t *)    0,
    (uint32_t *)    0,
    (uint32_t *)    0,
    (uint32_t *)    &SVCall_Handler,
    (uint32_t *)    &DebugMonitor_Handler,
    (uint32_t *)    0,
    (uint32_t *)    &PendableSrvReq_Handler,
    (uint32_t *)    &SysTick_Handler
};

uint32_t flash_config[4] __attribute__((section(".flash_config"))) = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFE
};

void Reset_Handler(void)
{
    /* Disable Watchdog */
    SystemInit();

    /* Copy data from FLASH to SRAM */
    uint32_t *data_flash_start = &_etext;
    uint32_t *data_ram_start_p = &_sdata;
    uint32_t *data_ram_end_p = &_edata;

    while (data_ram_start_p < data_ram_end_p) {
        *data_ram_start_p++ = *data_flash_start++;
    }

    /* Initialize data in the `.bss` section to zeros. */
    uint32_t *bss_start_p = &_sbss;
    uint32_t *bss_end_p = &_ebss;

    while (bss_start_p < bss_end_p) {
        *bss_start_p++ = 0;
    }

    main();
}

