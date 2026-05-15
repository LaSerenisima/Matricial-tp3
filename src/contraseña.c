#include <string.h>
#include "keypad.h"
#include "display7.h"

#define largoclave 6

// Variables globales
char contradef[largoclave + 1] = "1234"; //contra ya puesta
char contra[largoclave + 1];
int index_contra = 0;

typedef enum {
    entrar,
    aprobar,
    pass,
    cambiarclave
} estado;

estado estado_actual = entrar;


void leds(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    GPIOB->CRL &= ~(0x000000FF); 
    GPIOB->CRL |=  (0x00000022); 
}
//macros
#define ledVon  (GPIOB->BSRR = GPIO_BSRR_BS0)
#define ledVoff (GPIOB->BSRR = GPIO_BSRR_BR0)
#define ledRon   (GPIOB->BSRR = GPIO_BSRR_BS1)
#define ledRoff  (GPIOB->BSRR = GPIO_BSRR_BR1)

int main(void) {
    //cotroladores
    iniciotecla(); // matri
    segs7();  // display)
    leds();

    char tecla;

    while (1) {
        tecla = teclas();

        if (tecla != '\0') {
            
            switch (estado_actual) {
                
                case entrar:
                    ledRoff;
                    ledVoff;
                    
                    if (tecla >= '0' && tecla <= '9') {
                        contra[index_contra] = tecla;
                        mostrar7seg(tecla); // devuelve resultado en display
                        index_contra++;
                    }

                    if (index_contra == largoclave) {
                        contra[largoclave] = '\0'; 
                        estado_actual = aprobar;
                    }
                    break;

                case aprobar:
                //coimparacion
                    if (strcmp(contra, contradef) == 0) {
                        ledVon;
                        ledRoff;
                        mostrar7seg('OK'); //bien
                        estado_actual = pass;
                    } else {
                        ledRon
                    ;
                        ledVoff;
                        mostrar7seg('XX'); // mal
                        index_contra = 0;
                        estado_actual = entrar;
                    }
                    break;

                case pass:
                    //cambio clave
                    if (tecla == '#') {
                        mostrar7seg('mod'); //entrto en modificacion
                        index_contra = 0;
                        estado_actual = cambiarclave;
                        ledVoff;
                    } 

                    else if (tecla == '*') {
                        index_contra = 0;
                        estado_actual = entrar;
                    }
                    break;

                case cambiarclave:
                    if (tecla >= '0' && tecla <= '9') {
                        contra[index_contra] = tecla;
                        mostrar7seg(tecla);
                        index_contra++;
                    }

                    if (index_contra == largoclave) {
                        contra[largoclave] = '\0';
                        copiacontra(contradef, contra);
                        
                        // Confirmacion
                        ledVon;
                        for(volatile int d=0; d<500000; d++);
                        ledVoff;
                        
                        index_contra = 0;
                        estado_actual = entrar;
                    }
                    break;
            }
        }
        
        for (volatile int delay = 0; delay < 100000; delay++);
    }
}