/*
Considerando pulsadores normalmente abiertos conectados en un extremo a masa y en el otro directamente
a las entradas P0.0 y p0.1. 
Realizar un programa que identifique en una variable cual o cuales pulsadores han sido presionados. 
Las identificaciones posibles a implementar en esta variable van a ser "ninguno", "pulsador 1", "pulsador 2",
 "pulsador 1 y 2".
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"

void configGPIO(void);
void presionado(int aux);



int main(){
    int aux0=0; //auxiliar para pulsador p0.0
    int aux1=0; //auxiliar para pulsador p0.1
    configGPIO();
    detectar();
    presionado(aux0,aux1);
    return 0;
}

void configGPIO(){
    //P0.0 y P0.1 como gpio

    //P0.0 y P0.1 como gpio entradas

    //P0.0 y P0.1 en estado alto (cuando los presion se produce un flanco descendente)

}
void detectar(){

}

void presionado(){}