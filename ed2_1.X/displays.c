/*
 * File:   displays.c
 * Author: Andres
 *
 * Created on January 23, 2023, 8:04 PM
 */


#include <xc.h>
#include <stdint.h>
#include "displays.h"
#define _XTAL_FREQ 4000000

void mux(int selector){
        if (selector == 0){
            PORTA = nums[H1]; //mostrar unidades en el puerto A (display)
            PORTCbits.RC0 = 1; //multiplexeo
            PORTCbits.RC1 = 0;
        }
        if (selector == 1){
            PORTA = nums[H2]; //mostrar decenas en el puerto A (display)
            PORTCbits.RC0 = 0; //multiplexeo
            PORTCbits.RC1 = 1;
        }
}

void display_hex(int value){
    if (ADRESH >= PORTD){ //revisar si el valor del ADRESH es mayor al Puerto D
        PORTCbits.RC2 = 1; //encender alarma
    }
    else { //revisar si el valor del ADRESH es mayor al Puerto D
        PORTCbits.RC2 = 0;    } // apagar alarma
    
    H1 = (value%16); //convertir el valor de ADRESH a hexadecimal
    H2 = (value/16); //convertir el valor de ADRESH a hexadecimal
    
    //PORTA = nums[H1]; //mostrar unidades en el puerto A (display)
    //PORTCbits.RC0 = 1; //multiplexeo
    //PORTCbits.RC1 = 0;
    
   // __delay_ms(5); //delay de 5 ms
    
    //PORTA = nums[H2]; //mostrar decenas en el puerto A (display)
    //PORTCbits.RC0 = 0; //multiplexeo
    //PORTCbits.RC1 = 1;
    
    //__delay_ms(5); //delay de 5 ms    
}
