/*
 * File:   main.c
 * Author: Andrés Lemus
 * Laboratorio 1
 * Created on January 19, 2023, 12:47 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
#include "setup.h"
#include "ADC_setup.h"
#define _XTAL_FREQ 4000000

int bandera=0; // variable para el antirrebote del botón de incrementar
int num_adc;

void contador(void); //función del contador
void displays(void); //función de multiplexeo de displays y alarma

void main(void){
    osc4MHz();
    initiateports();
    digital_low();
    analog_12();
    portA_digout();
    portC_digout();
    portD_digout();
    pinRB7_digin();
    pinRB6_digin();
    pinRB0_digin();
    global_interruptions_on();
    peripheral_interruptions_on();
    portB_interruptions_on();
    ADC_interruptions_on();
    pullup_RB7();
    pullup_RB6();
    interrupt_onchange_RB7();
    interrupt_onchange_RB6();
    ADC_clock_fosc8();
    ADC_reference_default();
    ADC_8bits();
    ADC_AN12();
    ADC_on();
    while(1){ //loop principal
        ADCON0bits.GO = 1; //iniciar conversión ADC
        display_hex(); //función de displays      
    }
}

void __interrupt() isr(void){ //interrupciones
    if (INTCONbits.RBIF == 1){ //revisar bandera de interrupcion del puerto B
        contador(); // llamar al contador
        INTCONbits.RBIF = 0; //limpiar bandera  
    }
    if (PIR1bits.ADIF == 1){ //revisar bandera de interrupcion del conversor ADC
        PIR1bits.ADIF = 0; //limpiar bandera del conversor ADC
        num_adc = ADC_conversion();
    }
}
   

void contador(void){ 
    if (PORTBbits.RB6 == 0){ //revisar si se presiono el botón de incrementar
        bandera = 1;} //activar bandera
    if (PORTBbits.RB6 == 1 && bandera == 1){ //revisar si se dejo de presionar el botón y la bandera está en 1
        __delay_ms(10);
        PORTD++; //incrementar
        bandera = 0; // limpiar bandera
    }
    if (PORTBbits.RB7 == 0){ //revisar si se presiono el botón de decrementar
        bandera = 2;} //activar bandera
    if (PORTBbits.RB7 == 1 && bandera == 2){ //revisar si se dejo de presionar el botón y la bandera está en 1
        __delay_ms(10);
        PORTD--; //decrementar el puerto
        bandera = 0; // limpiar bandera
    }
}
