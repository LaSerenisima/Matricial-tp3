#include "keypad.h"

// Mapa caracteres
const char tec_matri[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void iniciotecla(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRL &= 0x00000000; 

    GPIOA->CRL |= 0x88882222;

    GPIOA->ODR |= 0x00FF; //pin 0 a 7
}

char teclas(void) {
    int i, y;

    for (i = 0; i < 4; i++) {
        
        GPIOA->BSRR = 0x000F; 

        GPIOA->BRR = (1 << i); 

        for (volatile int i = 0; i < 100; i++);

        uint16_t idr = GPIOA->IDR;

        for (y = 0; y < 4; y++) {
            
            if (!(idr & (1 << (y + 4)))) {
              
                return tec_matri[i][y];
            }
        }
    }

    return '-';
}