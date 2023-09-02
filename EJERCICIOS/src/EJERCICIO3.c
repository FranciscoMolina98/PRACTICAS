/*
Configurar el pin P0.4 como entrada digital con resistencia de pull down y utilizarlo para decidir si
el valor representado por los pines P0.0 al P0.3 van a ser sumados o restados al valor guardado en la
variable "acumulador".El valor inicial de "acumulador" es 0.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include <stdbool.h>

// Definición de pines
#define PIN_P04 (4)
#define PIN_P00 (0)
#define PIN_P01 (1)
#define PIN_P02 (2)
#define PIN_P03 (3)

// Declaro funciones
void configurarPuerto(void);

// Variables globales
int acumulador = 0;


int main() {
    void configurarPuertos();

    while (1) {
        // Leer el estado del pin P0.4
        bool valorP04 = ((LPC_GPIO0->FIOPIN>>PIN_P04) & (1 << PIN_P04)) ? true : false;

        // Leer el valor en los pines P0.0 al P0.3
        int valorLeido = ((LPC_GPIO0->FIOPIN>>PIN_P00) & 0x0F);

        // Realizar la suma o resta basada en el estado de P0.4
        if (valorP04) //Si p0:4 esta en 1, se suma
        {
            acumulador += valorLeido;
        }
        else //Si p0:4 esta en 0, se suma
        {
            acumulador -= valorLeido;
        }
    }

    return 0;
}

void configurarPuertos() {
    LPC_PINCON->PINSEL0 &= ~(0x3FF<<0);
    //P0.4, P0.0 as GPIO  (Es necesario que <P0.3:P0.4> sean declarados como gpio?)

    LPC_PINCON -> PINMODE0 |= (2 << (2 * PIN_P04));
    // Habilita la resistencia de pull-down en P0.4

    LPC_GPIO0->FIODIR &= ~(1 << PIN_P04);
    // Configura P0.4 como entrada
}
