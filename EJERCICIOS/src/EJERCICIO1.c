/*
Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds comandadas por un microcontrolador LPC1769
y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan intercalando
(secuencia A - secuencia B- secuencia A- ... ). Como todavía no se ha definido la frecuencia a la cual va a funcionar
el CPU del microcontrolador, las funciones de retardos que se incorporen deben tener como parametros de entrada variables
que permitan modificar el tiempo de retardo que se vaya a utilizar finalmente.
Se pide escribir el código que resuelva este pedido, considerando que los leds se encuentran conectados en los puertos
P0,0 al P0.9. Adjuntar el archivo .c bajo el nombre "eje1ApellidoDelEstudiante.c"
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"

// Definición de macros para los puertos y pines de los LEDs
#define LED_PORT LPC_GPIO0
#define LED_MASK 0x03FF  // Máscara para los pines P0.0 al P0.9
	//bits: 0000 0011 1111 1111
#endif




int main() {
    // Inicialización de puertos y pines para los LEDs
    LED_PORT->FIODIR |= LED_MASK;  // Configurar como entrada/salidas (FIODIR=0: entrada, FIODIR=1: salida)
    LED_PORT->FIOCLR = LED_MASK;   // Apagar todos los LEDs al inicio

    int delayTime = 500;  // (Se puede igualar a una funcion que devuelva un tiempo?)

    while (1) {
        encenderSecuenciaA(delayTime);  // Encender secuencia A
        encenderSecuenciaB(delayTime);  // Encender secuencia B
    }

    return 0;
}

// Función para generar un retardo aproximado (dependiente de la frecuencia del CPU)
void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 100000; ++i) {
        __NOP();  // No-operation para generar un retardo
    }
}

// Función para encender los LEDs de la secuencia A
void encenderSecuenciaA(int delayTime) {
    for (int i = 0; i < 10; ++i) {
        LED_PORT->FIOSET = (1 << i);  // Encender el LED correspondiente
        delay(delayTime);             // Retardo
        LED_PORT->FIOCLR = (1 << i);  // Apagar el LED correspondiente
    }
}

// Función para encender los LEDs de la secuencia B
void encenderSecuenciaB(int delayTime) {
    for (int i = 9; i >= 0; --i) {
        LED_PORT->FIOSET = (1 << i);  // Encender el LED correspondiente
        delay(delayTime);             // Retardo
        LED_PORT->FIOCLR = (1 << i);  // Apagar el LED correspondiente
    }
}
