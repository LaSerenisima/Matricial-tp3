#include "display7.h"

uint16_t botones(char c) {
    switch (c) {
        case '0': return 0x3F; 
        case '1': return 0x06; 
        case '2': return 0x5B; 
        case '3': return 0x4F;
        case '4': return 0x66;
        case '5': return 0x6D;
        case '6': return 0x7D;
        case '7': return 0x07;
        case '8': return 0x7F;
        case '9': return 0x6F;
        case 'A': return 0x77;
        case 'B': return 0x7C;
        case 'C': return 0x39;
        case 'D': return 0x5E;
        case '*': return 0x40;
        case '#': return 0x00; 
        default:  return 0x00;
    }
}

void segs7(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRH &= 0xF0000000; 
    
    GPIOA->CRH |= 0x02222222; 
}

void mostra(char c) {
    uint16_t patron = botones(c);
    
    GPIOA->ODR &= ~(0x7F00); 
    
    GPIOA->ODR |= (patron << 8); 
}

