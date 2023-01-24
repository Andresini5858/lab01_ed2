 
#ifndef displays
#define	displays

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

unsigned int H1=0; // variable para guardar las "unidades" del valor hexadecimal
unsigned int H2=0; // variable para guardar las "decenas" del valor hexadecimal
int dis=0; // variable para guardar el valor del ADRESH

unsigned char nums[] = { //arreglo para valores del display de 7 segementos
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5 
    0b01111101, //6
    0b00000111, //7
    0b01111111, //8
    0b01100111, //9
    0b01110111, //A
    0b01111100, //B
    0b00111001, //C
    0b01011110, //D
    0b01111001, //E
    0b01110001, //F
};

void display_hex(void);

#endif	/* XC_HEADER_TEMPLATE_H */

