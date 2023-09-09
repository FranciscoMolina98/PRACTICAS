// Ejercicio: P0.22 salida - repetir esta secuencia 11001100 con un periodo de  x ms
// P1.0 entrada - cuando detecta un 1, la secuencia cambia a 01010101 y cuando llega otro 10101010 y se vuelve a repetir
// El sistema repite indefinidamente una secuencia hasta uqe se sensa un 1 en P1.0, y rota entre 3 secuecnias



#include "LPC17xx.h"

#define SEC_1 0b11001100
#define SEC_2 0b01010101
#define SEC_3 0b10101010

#define P22 (1<<22)

uint8_t currentState=0;
short int secuencia_actual = SEC_1;

int aux=0;

void config_GPIO();
void leer_cambio();
void mostrarSecuencia(short int secuencia_actual);
void delay(unsigned int count);




int main(void){
	config_GPIO();

	while(1){
			leer_cambio();
			reset(aux);
			mostrarSecuencia(secuencia_actual);
			delay(100); //con esto genero un retardo de 1 segundo
		}
	}
    return 0 ;
}

//Configuro los pines
void config_GPIO(){
	//P0.22: GPIO
	LPC_PINCON -> PINSEL1 &= ~(3 << 12);
	//P0.22: output
	LPC_GPIO0  -> FIODIR |= P22;

	//P1.0: GPIO
	LPC_PINCON -> PINSEL2 &= ~(3 << 0);
	//P1.0: Pull down
	LPC_PINCON->PINMODE1 &= ~(3 << 0);
	//P1.0: input
	LPC_GPIO1  -> FIODIR &= ~(1 << 0);

}

//Leo el pin P1.0 para ver si fue pulsado, si fue pulsado reconfiguro sino continuo
void leer_cambio(){
	currentState = (LPC_GPIO1 -> FIOPIN >> 0)  & 1;
	if(currentState == 1){
		aux++;
		if(aux >= 3){
			aux=0;
		}
	}
}

//miro el ultimo bit y lo mando al puerto P0.22
void mostrarSecuencia (short int secuencia){
		LPC_GPIO1->FIOPIN = ((((secuencia & 0xff) << counter) & 0x80)<<(22-8));
		counter = (counter==7) ? 0:counter+1;
}

//Delaymodificable
void delay (unsigned int tiempo){
	SysTick -> load = 0xF423F; // CARGO (999.999,0) 
    SysTick -> val = 0;
    SysTick -> ctrl = (0<<1)|(1<<2)|(1<<0) 
        //(deshabilito las interrupciones)|
        //(selecciono cpu clock)
        //(habilito el contador)
    
    for(int i=0 ; i < tiempo ; i++){
        while(!(SysTick -> CTRL & (1<<16)));
    }
    SysTick -> CTRL = 0;
}

//Cambio la secuencia actualpara ingresar a un nuevo ciclo
void reset(int auxi){
	if(auxi==0){
			secuencia_actual = SEC_1;
	}
	else if (auxi==1){
			secuencia_actual = SEC_2;
	}
	else if (auxi==3){
			secuencia_actual= SEC_3;
	}
}







