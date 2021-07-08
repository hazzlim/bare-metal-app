#include "MK66F18.h"

#define RED_LED_SHIFT    (9)
#define ALT1_MUX         (1)
#define MASK(x)          (1UL << x)

/* Counter for SysTick Interrupts */
volatile uint32_t msTicks = 0U;

/* Called when SysTick Interrupt Occurs */
void SysTick_Handler(void)
{
    if (msTicks != 0U) {
        msTicks--;
    }
}

/* Wait for n SysTick Interrupts */
void wait(uint32_t n)
{
    msTicks = n;
    while (msTicks != 0U) {
        __WFI();
    }
}

/* Required initialization for RED_LED */
void init_pins(void)
{
    /* Enable PORTC Clock */
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    /* Set PORTC PIN9 MUX to ALT1 (RED LED) */
    PORTC->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(ALT1_MUX);

    /* Configure PORTC PIN9 for output */
    GPIOC->PDDR |= MASK(RED_LED_SHIFT);
}

void main(void)
{
    init_pins();

    SysTick_Config(SystemCoreClock / 1000U);

    while(1) {
        /* toggle LED */
        GPIOC->PTOR |= MASK(RED_LED_SHIFT);

        /* wait */
        wait(1000);
    }
}

