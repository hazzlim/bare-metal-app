/* Specify the Entry Point Address (For debug) */
ENTRY(Reset_Handler)

/* Specify the Memory Areas */
MEMORY
{
    flash       (RX)  : ORIGIN = 0x00000000, LENGTH = 2048K    /* 0x00200000 */
    sram      (RWX) : ORIGIN = 0x1FFF0000, LENGTH = 256K     /* 0x00040000 */
}

STACK_SIZE = 0x0400;

/* Define Output Sections */
SECTIONS
{
    /* Add the .text section to the flash */
    .text :
    {
        KEEP(*(.isr_vector))  /* Vector table */
        KEEP(*(.flash_config))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    }> flash

    .data :
    {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    }> sram AT> flash

    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    }> sram

}

