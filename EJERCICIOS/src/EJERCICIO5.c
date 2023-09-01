/*
Escribir un programa en C que permita realizar un promedio movil con los últimos 8 datos ingresados por el puerto 1.
Considerar que cada dato es un entero signado y está formado por los 16 bits menos significativos de dicho puerto.
El resultado, también de 16 bits, debe ser sacado por los pines P0.0 al P0.11 y P0.15 al P0.18.
Recordar que en un promedio movil primero se descarta el dato mas viejo de los 8 datos guardados, se ingresa un
nuevo dato proveniente del puerto y se realiza la nueva operación de promedio con esos 8 datos disponibles,
así sucesivamente. Considerar el uso de un retardo antes de tomar una nueva muestra por el puerto.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"






