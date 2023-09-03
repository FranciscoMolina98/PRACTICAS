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

#define SEC_1 0b11001100
#define SEC_2 0b01010101
#define SEC_3 0b10101010

#define P22 (1<<22)

uint8_t currentState;
short int secuencia_actual = SEC_1;

int aux=0;

void config_GPIO();
void leer_cambio();
void mostrarSecuencia(short int secuencia_actual);
void delay(unsigned int count);
void rotar();
void reset();



int main(void){
	config_GPIO();

	while(1){
		for(int cont=0; cont<8; cont++){
			leer_cambio();
			mostrarSecuencia(secuencia_actual);
			delay(10);
			rotar();
		}
		reset();
	}
    return 0 ;
}

//Configuro los pines
void config_GPIO(){
	//P0.22: GPIO
	LPC_PINCON -> PINSEL1 &= ~(3<<12);
	//P0.22: output
	LPC_GPIO0  -> FIODIR |= P22;

	//P1.0: GPIO
	LPC_PINCON -> PINSEL2 &= ~(3<<0);
	//P1.0: Pull down
	LPC_PINCON->PINMODE1 &= ~(3 << 0);
	//P1.0: input
	LPC_GPIO1  -> FIODIR &= ~(1<<0);

}

//Leo el pin P1.0 para ver si fue pulsado, si fue pulsado reconfiguro sino continuo
void leer_cambio()
{
	currentState = (LPC_GPIO1 -> FIOPIN1 >> 0)  & 1;
	if(currentState==1){
		aux++;
		if(aux>=3){
			aux=0;
		}
		reset();
	}
	else{}
}

//miro el ultimo bit y lo mando al puerto P0.22
void mostrarSecuencia (short int secuencia){
	// -> (0001 and secuencia == 1) bit lsb
	if( (1 & secuencia) == 1 )  // viendo el ultimo bit de la secuencia
	{
		LPC_GPIO0->FIOCLR |= P22;      //encendemos el led si es 1
	}else{
		LPC_GPIO0->FIOSET |= P22;      //apagamos el led si es 0
	}
}

//Delaymodificable
void delay (unsigned int count){
	for(int i=0;i<count;i++){
		for(int j=0;j<1000;j++);
	}
}

void rotar (){
	secuencia_actual = secuencia_actual >> 1;
}

//Cambio la secuencia actualpara ingresar a un nuevo ciclo
void reset(){
	if(aux==0){
			secuencia_actual = SEC_1;
	}
	else if (aux==1){
			secuencia_actual = SEC_2;
	}
	else{
			secuencia_actual= SEC_3;
	}
}



