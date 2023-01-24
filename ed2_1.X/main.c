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
#include "displays.h"
#define _XTAL_FREQ 4000000

int bandera = 0; // variable para el antirrebote del botón de incrementar
int num_adc = 0; // variable para guardar valor del ADC 
int select = 0; // variable para controlar el muxeo de los displays

void contador(void); //función del contador

void main(void){
    osc4MHz(); //función que configura oscilador interno a 4MHz
    digital_low(); //coloca pines como i/o digitales
    analog_12(); //utilizar canal AN12 como entrada analógica
    portA_digout(); //Puerto A como i/o digital
    portC_digout(); //Puerto C como i/o digital
    portD_digout(); //Puerto D como i/o digital
    initiateports(); //función que limpia los puertos
    pinRB7_digin(); //PinRB7 como entrada digital
    pinRB6_digin(); //PinRB6 como entrada digital
    pinRB0_digin(); //PinRB0 como entrada digital
    portB_pullups(); //Activar pull-ups del puerto B
    global_interruptions_on(); //Activar interrupciones globales
    peripheral_interruptions_on(); //Activar interrupciones periféricas
    Timer0_interruption_on(); //Activar interrupciones del Timer0
    Timer0_source(); //Utilizar oscilador interno
    Timer0_prescaler256(); //Utilizar prescaler de 256
    portB_interruptions_on(); //Activar interrupciones del puerto B
    ADC_interruptions_on(); //Activar interrupciones del ADC
    pullup_RB7(); //Activar pull-up del pin RB7
    pullup_RB6(); //Activar pull-up del pin RB6
    interrupt_onchange_RB7(); //Activar interrupcion on-change para pin RB7
    interrupt_onchange_RB6(); //Activar interrupcion on-change para pin RB6
    ADC_clock_fosc8(); //Configurar f_osc/8 para el ADC
    ADC_reference_default(); //Configurar referencia a 0 voltios
    ADC_8bits(); //Utilizar ADC con 8 bits
    ADC_AN12(); //Utilizar canal 12 para el ADC
    ADC_on(); //Encender el ADC
    TMR0 = 255; //Valor del Timer0 para delay lo más rápido posible del multiplexeo
    while(1){ //loop principal
        ADCON0bits.GO = 1; //iniciar conversión ADC
        display_hex(num_adc); //función de display
    }
}

void __interrupt() isr(void){ //interrupciones
    if (INTCONbits.T0IF == 1){ //revisar bandera de interrupcion del Timer0
        INTCONbits.T0IF = 0; //limpiar bandera
        TMR0 = 255; //cargar valor nuevamente al timer0
        if (select == 0){ //revisar selector de muxeo
            mux(select); //estar mostrando valores en display continuamente
            select = 1;  //cambiar variable para el segundo display
        }
        if (select == 1){ //revisar selector de muxeo
            mux(select); //estar mostrando valores en display continuamente
            select = 0; //cambiar variable para el segundo display
        } 
    }
    if (INTCONbits.RBIF == 1){ //revisar bandera de interrupcion del puerto B
        INTCONbits.RBIF = 0; //limpiar bandera 
        contador(); // llamar al contador 
    }
    if (PIR1bits.ADIF == 1){ //revisar bandera de interrupcion del conversor ADC
        PIR1bits.ADIF = 0; //limpiar bandera del conversor ADC
        num_adc = ADC_conversion(); //Guardar valor ya convertido del ADC en una variable
    }
}
   

void contador(void){ 
    if (PORTBbits.RB6 == 0){ //revisar si se presiono el botón de incrementar
        bandera = 1;} //activar bandera
    if (PORTBbits.RB6 == 1 && bandera == 1){ //revisar si se dejo de presionar el botón y la bandera está en 1
        PORTD++; //incrementar
        bandera = 0; // limpiar bandera
    }
    if (PORTBbits.RB7 == 0){ //revisar si se presiono el botón de decrementar
        bandera = 2;} //activar bandera
    if (PORTBbits.RB7 == 1 && bandera == 2){ //revisar si se dejo de presionar el botón y la bandera está en 1
        PORTD--; //decrementar el puerto
        bandera = 0; // limpiar bandera
    }
}
