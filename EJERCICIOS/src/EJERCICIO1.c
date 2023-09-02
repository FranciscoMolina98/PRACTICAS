/*
Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds comandadas por un microcontrolador LPC1769
y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan intercalando
(secuencia A - secuencia B- secuencia A- ... ). Como todavía no se ha definido la frecuencia a la cual va a funcionar
el CPU del microcontrolador, las funciones de retardos que se incorporen deben tener como parametros de entrada variables
que permitan modificar el tiempo de retardo que se vaya a utilizar finalmente.
Se pide escribir el código que resuelva este pedido, considerando que los leds se encuentran conectados en los puertos
P0,0 al P0.9. 
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"

#define APAGADO 0x3FF  		// 11 1111 1111
#define IMPAR 0x155 		// 01 0101 0101  
#define PAR 0x2AA   		// 10 1010 1010

void config_GPIO();
void delay (unsigned int count);
void mostrarPar();
void mostrarImpar();


int main(void) {
	config_GPIO();

	while(1)
    {
        int cant=10;        //Si cambio cant puedo cambiar la duracion de la secuencia
		for(int i=0; i<cant; cont++)
        {
            mostrarPar();   //secuencia par = secuencia A
		}
        for(int i=0; i<cant; i++)
        {
			mostrarImpar(); ////secuencia impar = secuencia B
		}
	}
    return 0 ;
}


void config_GPIO(){

	LPC_PINCON -> PINSEL0 &= ~(0b3FF<<0);       
    //configuramos los pin <P0.9:P0.0> como GPIO
	LPC_GPIO0  -> FIODIR |= 0b3FF;  
    // P0.0 al P0.9 como salidas;
}

void mostrarPar () //La secuencia dura aprox 2 delays
{
    int count=20;                    	//con este valor puedo modificar los tiempos del delay   
	LPC_GPIO0 -> FIOCLR |= APAGADO; //Apagamos todos los led
    delay(count);
	LPC_GPIO0 -> FIOSET |= PAR;     //Prendemos la configuracion de led de los puertos pares
    delay(count);
}

void mostrarImpar (const short int secuencia) //La secuencia dura aprox 2 delays
{
    int count=20;                   	//con este valor puedo modificar los tiempos del delay
	LPC_GPIO0->FIOCLR |= APAGADO;   //Apagamos todos los leds
	delay(count);
    LPC_GPIO0->FIOSET |= IMPAR;    	//Prendemos la configuracion impar de leds
    delay(count);
}

void delay (unsigned int count)     	//cant*(2 delay)=duracion de cada secuencia
{
	for(int i=0;i<count;i++){
		for(int j=0;j<1000;j++);
	}
}
