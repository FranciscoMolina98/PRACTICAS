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
void delay(int times);
void mostrar(int auxiliar);
void rectificar(int aux);


int aux = 0;
int time = 50; //delay de medio segundo
uint32_t apagar = 0x3ff;

int main(){
	void configGPIO();
	
	while{
		// mostrar por puerto el valor hexa
		mostrar(aux);
		// delay configurable para que se quede un tiempo
		rectificar(aux);
		//retardo
		delay(time);

	}
return 0;
}

void configGPIO(){
//P2<7:0> GPIO
LPC_PINCON -> PINSEL4 &= ~(0xffff<<0);  
//P2<7:0> output
LPC_GPIO2 -> FIODIR |= (0xff<<0);
}

void mostrar(int auxiliar){
LPC_GPIO2 -> FIOPIN &= ~(apagar);	
delay(50);
LPC_GPIO2 -> FIOPIN |= numDysplay[auxiliar];
delay(50);
}

void delay(int times){
    SysTick -> load = 0xF423F; // CARGO (999.999,0) 
    SysTick -> val = 0;
    SysTick -> ctrl = (0<<1)|(1<<2)|(1<<0) 
        //(deshabilito las interrupciones)|
        //(selecciono cpu clock)
        //(habilito el contador)
    
    for(int i=0 ; i < times ; i++){
        while(!(SysTick -> CTRL & (1<<16)));
    }
    SysTick -> CTRL = 0;
}

void rectificar(int aux){
	aux=aux+1;
	if(aux>9){
		aux=0;
	}
}

