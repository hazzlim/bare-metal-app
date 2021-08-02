/* Specify the Entry Point Address (For debug) */
ENTRY(Reset_Handler)

/* Specify the Memory Areas */
MEMORY
{
    flash   (RX)  : ORIGIN = 0x00000000, LENGTH = 2048K
    sram    (RWX) : ORIGIN = 0x1FFF0000, LENGTH = 256K
}

/* Define Output Sections */
SECTIONS
{
    /* Add the .text section to the flash */
    .text :
    {
        KEEP(*(.isr_vector))  /* Vector table */
        KEEP(*(.flash_config))
        *(.text)
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

    _stack_top = ORIGIN(sram) + LENGTH(sram);

}

