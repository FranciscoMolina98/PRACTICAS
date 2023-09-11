/*
1.- Configure el Systick Timer de modo que genere una forma de onda llamada PWM tal como la que se 
muestra en la figura adjunta. Esta señal debe ser sacada por el pin P0.22 para que controle la intensidad de 
brillo del led. El periodo de la señal debe ser de 10 mseg con un duty cycle de 10%. 

Configure la interrupción externa EINT0 de modo que cada vez que se entre en una rutina de interrupción 
externa el duty cycle incremente en un 10% (1 mseg). 
Esto se repite hasta llegar al 100%, luego, si se entra nuevamente a la interrupción externa, el duty cycle 
volverá al 10%.

2.- Modificar los niveles de prioridad para que la interrupción por systick tenga mayor prioridad que la 
interrupción externa.

3. Adjuntar el .C  del código generado.
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

uint32_t waveForm = 0xFFFFE00; //1111 1111 1111 1111 1111 1110 0000 0000
int aux=0;

void configGPIO(void);
void config_INT(void);



int main(){
    configGPIO();
    configINT();

    while(1){

    };
    return 0;
}

void configGPIO(){
//P0.22
    //PINESL//
        //p0.22 gpio
        LPC_PINCON -> PINSEL1 &= ~(0x3<<12);

    //PINMODE//
        //p0.22 sin pull-up
        LPC_PINCON -> PINMODE1 &=~(1<<13);
        LPC_PINCON -> PINMODE1 |=(1<<12);

    //FIODIR//
        //p0.22 salida
        LPC_GPIO0 -> FIODIR |=(1<<22);

}


void configINT(){
//EINT0

    //PINESEL//
        //P2.10 como EINT
        LPC_PINCON -> PINSEL4 |= (1<<20);
        LPC_PINCON -> PINSEL4 &= ~(1<<21);
    //PINMODE//
        //EINT0 pull-down
        LPC_PINCON -> PINMODE4 |=(3<<20);

    //SYSTEM CONTROL
        LPC_SC -> EXTMODE |=(1<<0);     //edge sensitive
        LPC_SC -> EXTPOLAR |=(1<<0);    //nivel alto
        LPC_SC -> EXTINT |= (1<<0); 	//Clear flags
    //PRIORIDAD
        NVIC_SetPriority(EINT0_IRQn,1);
        NVIC_EnableIRQ(EINT0_IRQn);

//SysTick
        //CONFIGURACION//
        SysTick->LOAD = ((SystemCoreClock/1000)-1);  //Nos da una interrupcion cada 1ms
	    SysTick->VAL = 0;
        SysTick->CTRL = (1<<2)|(1<<1)|(1<<0);
	    NVIC_SetPriority(SysTick_IRQn,0);
}


void EINT0_IRQHandler(void){
    aux = aux+1;
    //waveForm_actual = (waveForm>>aux);
    if(aux>9){
        //waveForm_actual=waveForm;
        aux=0;
    }
	LPC_SC->EXTINT |= (1<<0); 			//Clear EINT0 flag
}

void SysTick_Handler(void){
	static uint8_t count = 0; // de 0 a 9 -> muestra 10 numeros de la secuecnia
    static uint8_t SysCycle = 0;  // cuenta si hubo 10 secuencias para repetir el ciclo

    //aux=9;
    //syscicle=0;
    //cont=0;

    if(SysCycle<=aux){
        if(count<=aux){
	    LPC_GPIO0 -> FIOPIN = ((((waveForm >> count) & 0x200))<<12); //sale por p0.22
	    count = (count==9) ? 0:count+1;
        }
    }
    SysCycle++;

    if(SysCycle==10){
        SysCycle=0;
    }

    SysTick->CTRL &= SysTick->CTRL; //Clear flag

}
/*
    wave               COUNTER      sys
    10 0000 0000        0           0
    11 0000 0000        1           1
    11 1000 0000        2           2
    11 1100 0000        3           3
    11 1110 0000        4           4
    11 1111 0000        5           5
    11 1111 1000        6           6
    11 1111 1100        7           7
    11 1111 1110        8           8
    11 1111 1111        9           9
*/