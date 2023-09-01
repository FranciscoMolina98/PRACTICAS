/*
En este archivo, se implementan las funciones declaradas en gpioHandler.h.
Se utilizan registros y operaciones bitwise para interactuar directamente con el hardware del microcontrolador.
Las funciones realizan las siguientes tareas:
	- gpioConfig: Configura los registros de configuración de pines (PINSEL y PINMODE) para establecer la función
	y el modo del pin, y configura el registro de dirección de puerto (FIODIR) para establecer la dirección del pin.
	- gpioWrite: Cambia el estado de un pin mediante operaciones bitwise en el registro de valores de pin (FIOPIN).
	- gpioRead: Lee el estado de un pin específico mediante operaciones bitwise en el registro de valores de pin (FIOPIN).
 */

#include <stdio.h>
#include <stdint.h>
#include <LPC17xx.h>
#include "gpioHandler.h"

/*
Los punteros se utilizan para acceder a los registros de configuración y estado de los pines GPIO y permiten interactuar
directamente con el hardware.
Cada puntero está asignado a un registro específico en la estructura de registros del microcontrolador.
 */

volatile uint32_t* pinselBase = &LPC_PINCON->PINSEL0;
// Puntero volátil a un registro que controla la selección de función de los pines GPIO
volatile uint32_t* pinmodeBase = &LPC_PINCON->PINMODE0;
// Puntero volátil a un registro que controla los modos de resistencia de los pines GPIO
volatile uint32_t* fiodirBase = &LPC_GPIO0->FIODIR;
// Puntero volátil a un registro que controla la dirección (entrada/salida) de los pines GPIO
volatile uint32_t* fiopinBase = &LPC_GPIO0->FIOPIN;
// Puntero volátil a un registro que almacena los valores actuales de los pines GPIO


void gpioConfig(int portNumber, int pin, int pinMode, int direction) {
				//(3,25,2,1)
	// Estas dos variables calculan el número de columna, discrimiando si son <15:0> 0 <31:16>
	int column = (pin<=15) ? 0:1; 			//Si es verdadero (column=0), si es falso (column=1)
	int pinAux = (pin>=16) ? pin-16:pin; 	//si es verdadero (pinaux=pin-16), si es falso (pinAux=pin)
	//column=1
	//pinAux=9

	//3 en binario=0011
	*(pinselBase + portNumber*2 + column) &= ~(3<<2*pinAux);

	*(pinmodeBase + portNumber*2 + column) &= ~(3<<2*pinAux);

	*(fiodirBase + portNumber*8) &= ~(1<<pin);

	if(pinMode!=0)
		*(pinmodeBase + portNumber*2 + column) |= (pinMode<<2*pinAux);

	*(fiodirBase + portNumber*8) |= (direction<<pin);
}


void gpioWrite(int portNumber, int pin, int state) {
	if (state==LOW)
		*(fiopinBase + portNumber*8) &= ~(1<<pin);
	else
		*(fiopinBase + portNumber*8) |= (1<<pin);
}

int gpioRead(int portNumber, int pin) {
	return (*(fiopinBase + portNumber*8)>>pin) & 0x01;
}

