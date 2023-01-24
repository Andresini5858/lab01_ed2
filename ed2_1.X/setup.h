#ifndef setup
#define	setup

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void osc4MHz(void);
void initiateports(void);
void digital_low(void);
void digital_high(void);
void analog_12(void);
void portA_digout(void);
void portB_digout(void);
void portC_digout(void);
void portD_digout(void);
void pinRB7_digin(void);
void pinRB6_digin(void);
void pinRB0_digin(void);
void portB_pullups(void);
void global_interruptions_on(void);
void global_interruptions_off(void);
void peripheral_interruptions_on(void);
void portB_interruptions_on(void);
void ADC_interruptions_on(void);
void Timer0_interruption_on(void);
void Timer0_source(void);
void Timer0_prescaler256(void);
void pullup_RB7(void);
void pullup_RB6(void);
void interrupt_onchange_RB7(void);
void interrupt_onchange_RB6(void);


#endif	/* XC_HEADER_TEMPLATE_H */

