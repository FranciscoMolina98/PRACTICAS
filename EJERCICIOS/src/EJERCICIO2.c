/*
En los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos.
Utilizando la variable numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67} que
codifica los números del 0 a 9 para ser mostrados en el display, realizar un programa que muestre indefinidamente
la cuenta de 0 a 9 en dicho display.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"

//Usamos arreglo de la consigna
unsigned char numDysplay[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67}

void configGPIO(void);
void delay(uint32_t times);
int aux=0;

int main{
	// que valor tiene auxiliar y rectificar si es necesario
	auxiliar();
	// mostrar por puerto el valor hexa
	mostrar();
	// delay configurable para que se quede un tiempo
	delay();
	return 0;
}

void configGPIO(){

//P2<7:0> output
}

void mostrar(){
//muestro el valor esoecifico del arreglo
}


void delay(times){

}

