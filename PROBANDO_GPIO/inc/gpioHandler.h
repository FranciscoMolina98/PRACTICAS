/*
Este archivo contiene las definiciones de enumeraciones y prototipos de funciones relacionadas
con el manejo de pines GPIO.
Enumera los puertos disponibles, los estados lógicos, las direcciones de los pines y los modos de resistencia.
Además, declara tres funciones esenciales para el manejo de GPIO:
	- gpioConfig: Configura un pin GPIO específico con un modo y dirección dados.
	- gpioWrite: Escribe un estado (LOW o HIGH) en un pin GPIO específico.
	- gpioRead: Lee y devuelve el estado actual de un pin GPIO específico.
 */

#ifndef GPIOHANDLER_H_
#define GPIOHANDLER_H_

#include<stdio.h>

/*
Las enumeraciones en el código representan conjuntos de valores constantes con nombres descriptivos
enumeraciones se utilizan para proporcionar un conjunto legible de opciones para configurar y manejar los
pines GPIO de manera más comprensible
*/
enum Ports{PORT0,PORT1,PORT2,PORT3,PORT4}; //Estos valores numéricos enteros representan los diferentes puertos GPIO
enum States{LOW,HIGH}; // Estos valores indican los estados lógicos posibles de un pin GPIO
enum Dir{INPUT,OUTPUT}; // Estos valores indican las direcciones posibles para un pin GPIO
enum Mode{PULLUP,REPEATER,NEITHER,PULLDOWN}; //: Estos valores representan los diferentes modos de resistencia


void gpioConfig(int portNumber, int pin, int pinMode, int direction);
//Esta función se encarga de configurar un pin GPIO específico en un puerto determinado según los parámetros
void gpioWrite(int portNumber, int pin, int state);
//Esta función se utiliza para escribir un estado lógico (LOW o HIGH) en un pin GPIO específico en un puerto determinado
int gpioRead(int portNumber, int pin);
// Esta función se utiliza para leer y devolver el estado lógico actual de un pin GPIO específico en un puerto determinado


#endif /* GPIOHANDLER_H_ */




