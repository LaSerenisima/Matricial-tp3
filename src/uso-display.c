#include "keypad.h"
#include "display7.h"
#include "stm32f103xb.h"

int main(void) {
    iniciotecla(); 
    segs7();   

    char tecla;

    while (1) {
        tecla = teclas();

        if (tecla != '\0') {
            mostra(tecla);
        }

        for (volatile int delay = 0; delay < 50000; delay++);
    }
}