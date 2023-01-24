/*
 * File:   ADC_setup.c
 * Author: Andres
 *
 * Created on January 23, 2023, 6:49 PM
 */


#include <xc.h>
#include <stdint.h>
#include "ADC_setup.h"
#define _XTAL_FREQ 4000000

void ADC_clock_fosc8(void){
    ADCON0bits.ADCS1 = 0; // Fosc/ 8        
    ADCON0bits.ADCS0 = 1; //  
}

void ADC_reference_default(void){
    ADCON1bits.VCFG1 = 0; // Referencia VSS (0 Volts)
    ADCON1bits.VCFG0 = 0; // Referencia VDD (5 Volts)
}

void ADC_8bits(void){
      ADCON1bits.ADFM = 0;  // Justificado hacia izquierda
}

void ADC_AN12(void){
    ADCON0bits.CHS3 = 1; // Canal AN12
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0; 
}

void ADC_on(void){
    ADCON0bits.ADON = 1; // Habilitamos el ADC
    __delay_us(100); //delay de 100 us
}

int ADC_conversion(void){
    digital_value = ADRESH;
    return digital_value;
}