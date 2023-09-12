/*
 P1.16 - P1.23 -> equivalente ascii "a" si la interrupcion es por EINT1 y no hay interrupcion por EINT0
 P1.16 - P1.23 -> equivalente ascii "A" si la interrupcion es por EINT1 y hay una interrupcion pendiente EINT0

 flanco de subida EINT1 -> tecla TECLAaA: "a/A"
 flanco de subida EINT0 -> tecla MAYUS: "Activacion de mayuscula"

 interrupciones por nivel alto
*/


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

// Definiciones
#define TECLAaA (1 << 11)
#define MAYUS (1 << 10)

// Prototipos de funciones
void configGPIO(void);
void configINT(void);
void delay(int tiempo);

// Programa principal
int main(void) {
    configGPIO();  // Configuro las salidas
    configINT();   // Configuro las interrupciones

    while (1) {
        // Tu código principal aquí
    }

    return 0;
}

// Funciones

void configGPIO(void) {
    // P1.16 - P1.23 (8 pines)
    // PINSEL
    LPC_PINCON->PINSEL3 &= ~(0xFFFF);   // GPIO
    // FIODIR
    LPC_GPIO1->FIODIR |= (0xFF<<16);    // Salidas
}

void configINT(void) {
    LPC_PINCON->PINSEL4 |= MAYUS;      // EINT0
    LPC_PINCON->PINSEL4 |= TECLAaA;    // EINT1

    LPC_PINCON->PINMODE4 &= ~(0xF << 20);   // Pull-Down EINT0 e INT1

    LPC_SC->EXTMODE |= MAYUS;      // EINT0 edge sensitive
    LPC_SC->EXTMODE |= TECLAaA;    // EINT1 edge sensitive

    LPC_SC->EXTPOLAR |= MAYUS;     // EINT0 rising edge
    LPC_SC->EXTPOLAR |= TECLAaA;   // EINT1 rising edge

    LPC_SC->EXTINT |= MAYUS;       // EINT0 clear flag
    LPC_SC->EXTINT |= TECLAaA;     // EINT1 clear flag

    //Seteamos prioridades
    NVIC_SetPriority(EINT0_IRQn,7);
    NVIC_SetPriority(EINT1_IRQn,6);
    //habilitamos las interrupciones
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
}

// Handler Interrupción EINT0
void EINT0_IRQHandler(void) {
    NVIC_SetPendingIRQ(EINT0_IRQn);
    delay(200);
    LPC_SC->EXTINT |= MAYUS;
}

// Handler Interrupción EINT1
void EINT1_IRQHandler(void) {
    if (NVIC_GetPendingIRQ(EINT0_IRQn)) {
        // Imprimo "A" en ASCII
    } else {
        // Imprimo "a" en ASCII
    }
    NVIC_ClearPendingIRQ (EINT1_IRQn);
    NVIC_ClearPendingIRQ (EINT0_IRQn);
    LPC_SC->EXTINT |= TECLAaA;
}

void delay(int tiempo) {
    SysTick->LOAD = 0xF423F;  // CARGO (999.999,0)
    SysTick->VAL = 0;
    SysTick->CTRL = (0 << 1) | (1 << 2) | (1 << 0);
    // (deshabilito las interrupciones)|
    // (selecciono cpu clock)
    // (habilito el contador)

    for (int i = 0; i < tiempo; i++) {
        while (!(SysTick->CTRL & (1 << 16)));
    }
    SysTick->CTRL = 0;
}
