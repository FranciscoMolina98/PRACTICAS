/*
Este archivo es el programa principal que utiliza las funciones definidas en gpioHandler.h y gpioHandler.c
para controlar y hacer parpadear un LED RGB incorporado.
El programa hace lo siguiente:
	- Configura los pines GPIO para controlar los LED rojo, verde y azul, así como un botón (entrada).
	- Enciende los LED rojo y verde inicialmente.

En un bucle infinito, verifica el estado del botón:
	- Si el botón está presionado (estado alto), apaga todos los LED.
	- Si el botón no está presionado (estado bajo), alterna entre encender el LED azul durante un segundo,
	luego encender el LED rojo durante un segundo y finalmente encender el LED verde durante un segundo.
 */


#include "LPC17xx.h"
#include "gpioHandler.h"

#define REDLED 		(22)
#define GREENLED 	(25)
#define BLUELED 	(26)

void configGPIO(void);
void delay(uint32_t times);

int main(void) {

	configGPIO();

	gpioWrite(PORT0, REDLED, HIGH);
	gpioWrite(PORT3, GREENLED, HIGH);
	gpioWrite(PORT3, BLUELED, HIGH);

	while(1) {
		if(gpioRead(PORT0, 0)) {
			gpioWrite(PORT0, REDLED, LOW);
			gpioWrite(PORT3, GREENLED, LOW);
			gpioWrite(PORT3, BLUELED, LOW);
		}
		else {
			gpioWrite(PORT3, BLUELED, HIGH);
			gpioWrite(PORT0, REDLED, LOW);
			delay(1000);
			gpioWrite(PORT0, REDLED, HIGH);
			gpioWrite(PORT3, GREENLED, LOW);
			delay(1000);
			gpioWrite(PORT3, GREENLED, HIGH);
			gpioWrite(PORT3, BLUELED, LOW);
			delay(1000);
		}
	}

    return 0 ;
}

void configGPIO(void) {
	//gpioConfig(n Puerto, n pin, n modo , direccion);
	gpioConfig(PORT0, REDLED, NEITHER, OUTPUT);
			//(0,22,2,1)
	gpioConfig(PORT3, GREENLED, NEITHER, OUTPUT);
		    //(3,25,2,1)
	gpioConfig(PORT3, BLUELED, NEITHER, OUTPUT);
    		//(3,26,2,1)
	gpioConfig(PORT0, 0, PULLDOWN, INPUT);
			//(0,0,3,0)
}

void delay(uint32_t times) {
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++);
}
