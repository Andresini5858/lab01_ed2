
#ifndef ADC_setup
#define	ADC_setup

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

int digital_value;

void ADC_clock_fosc8(void);
void ADC_reference_default(void);
void ADC_8bits(void);
void ADC_AN12(void);
void ADC_on(void);
int ADC_conversion(void);

#endif	/* XC_HEADER_TEMPLATE_H */

