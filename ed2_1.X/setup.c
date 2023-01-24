/*
 * File:   setup.c
 * Author: Andres
 *
 * Created on January 23, 2023, 5:42 PM
 */


#include <xc.h>
#include <stdint.h>
#include "setup.h"
#define _XTAL_FREQ 4000000

void osc4MHz(void){
    OSCCONbits.IRCF2 = 1; //Oscilador a 4MHz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS = 1; //Oscialdor interno
}

void initiateports(void){
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
}

void digital_low(void){
    ANSEL = 0;
}

void digital_high(void){
    ANSELH = 0;
}

void analog_12(void){
    ANSELH = 0b00010000; //puertos digitales excepto el puerto ANS12 o RB0
}

void portA_digout(void){
    TRISA = 0;
}

void portB_digout(void){
    TRISB = 0;
}

void portC_digout(void){
    TRISC = 0;
}

void portD_digout(void){
    TRISD = 0;
}

void pinRB7_digin(void){
    TRISBbits.TRISB7 = 1;
}

void pinRB6_digin(void){
    TRISBbits.TRISB6 = 1;
}

void pinRB0_digin(void){
    TRISBbits.TRISB0 = 1;
}

void portB_pullups(void){
    OPTION_REGbits.nRBPU = 0;
}

void global_interruptions_on(void){
    INTCONbits.GIE = 1; //Activar interrupciones globales
}

void global_interruptions_off(void){
    INTCONbits.GIE = 0; //Desactivar interrupciones globales
}

void peripheral_interruptions_on(void){
    INTCONbits.PEIE = 1; //Activar interrupciones periféricas
}

void portB_interruptions_on(void){
    INTCONbits.RBIE = 1; //Activar interrupciones puerto B
}

void ADC_interruptions_on(void){
    PIE1bits.ADIE = 1; // Habiliar interrupcion del conversor ADC
}

void pullup_RB7(void){
    WPUBbits.WPUB7 = 1; // Activar pullup puerto b7
}

void pullup_RB6(void){
    WPUBbits.WPUB6 = 1; // Activar pullup puerto b7
}

void interrupt_onchange_RB7(void){
    IOCBbits.IOCB7 = 1; //activar interrupt on-change b7
}

void interrupt_onchange_RB6(void){
    IOCBbits.IOCB6 = 1; //activar interrupt on-change b6
}

