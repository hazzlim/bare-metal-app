#include "MK66F18.h"

#define RED_LED_SHIFT    (9)
#define ALT1_MUX         (1)
#define MASK(x)          (1UL << x)

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

    while(1) {
        /* toggle LED */
        GPIOC->PTOR |= MASK(RED_LED_SHIFT);

        /* wait */
        for (int i=0; i<1000000;++i) {}
    }
}

