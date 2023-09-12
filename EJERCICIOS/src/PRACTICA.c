/*
Algoritmo de antirrebote de un pulsador: 
Escribir un programa en C que ante la interrupción por flanco de subida del pin P0.1, configurado como entrada digital
con pull-down interno, se incremente un contador de un dígito, se deshabilite esta interrupción y se permita 
la interrupción por systick cada 20 milisegundos. 

En cada interrupción del systick se testeará una vez el pin P0.1. 

Solo para el caso de haber testeado 3 estados altos seguidos se sacará por los pines del puerto P2.0 al P2.7 
el equivalente en ascii del valor del contador, se desactivará las interrupción por systick y se habilitará 
nuevamente la interrupción por P0.1. 

Por especificación de diseño se pide que los pines del puerto 2 que no sean utilizados deben estar enmascarados 
por hardware. Considerar que el CPU se encuentra funcionando con el oscilador interno RC (4Mhz). 
*/


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

//variables globales
int set=0;
int unset=0;
int contador=0;

//funciones
void configGPIO(void);
void configINT(void);
void rectificar(int num);
void mostrar(int numero);

//programa principal
int main(){
    configGPIO();
    configINT();

    while(1){
        rectificar(contador);
        mostrar(contador);
    };
    return 0;
}

//funciones
    //Configuro Puerto de entrada y puertos de salida
void configGPIO(){
//P0.1 entrada
    //PINESL//
        //p0.22 gpio
        LPC_PINCON -> PINSEL0 &= ~(0x3<<2);

    //PINMODE//
        //p0.1 sin pull-up
        LPC_PINCON -> PINMODE0 |=(3<<2);

    //FIODIR//
        //p0.22 entrada
        LPC_GPIO0 -> FIODIR &=~(1<<1);

//P2.0 al P2.7 salida
    //PINESL//
        //P2<7:0> GPIO
        LPC_PINCON -> PINSEL4 &= ~(0xFFFF<<0);

    //PINMODE//
        //P2<7:0> sin pull-up
        LPC_PINCON -> PINMODE4 |=(0xAAAA<<0);

    //FIODIR//
        //P2<7:0> como salida
        LPC_GPIO2 -> FIODIR |=(0xFF<<0);

    //FIOMASK//
        //P2<13:8> (1) no deja modificar (0) deja modificar por fio
        LPC_GPIO2 -> FIOMASK &=~(0xFF<<0);   //Permite editar P2<7:0>
        LPC_GPIO2 -> FIOMASK |=(0x3F<<8);    //No permite editar P2<13:8>
}

    //Configuro las interrupciones por P0.1 y seteo la configuracion del systick
void configINT(){
//habilito interrupcion de P0.1 por flanco de subida
    LPC_GPIOINT -> IO0IntEnR |= (1<<1); //P0.1 interrumpe x rising edge
}
    //Handler Interrupciones por GPIO0 que comparte handler con EINT3
void EINT3_IRQHandler(void){
    // deshabilito P0.1 interrumpe x rising edge
    LPC_GPIOINT -> IO0IntEnR &=~(1<<1); 
    //configuro y activ0 la interrupcion del systick
        SysTick->LOAD = 0x13498;  //Nos da una interrupcion cada 20ms
	    SysTick->VAL = 0;
        SysTick->CTRL = ((1<<0)|(1<<1)|(0<<2)|(0<<16));  //contador deshabilitado, interrupciones deshab, clock externo, sin bandera
        NVIC_SetPriority(SysTick_IRQn,0);
}

    //Handler Interrupcion por systick
void SysTick_Handler(void){
    //contar 3 veces revisando p0.1
    //si la cuenta da 3, deshabilito el systick, incremento el contador y lo muestro
    int pinState = (LPC_GPIO1->FIOPIN & (0x2)) ? 1 : 0;
            if(pinState==1){
                set++;
            }
            else{
                unset++
            }

    if(set==3){
        set=0;
        contador++;
        SysTick -> CTRL &= ~((1<<0)|(1<<1));    //deshabilito deshabilito el systick y las interrup
        LPC_GPIOINT -> IO0IntEnR |= (1<<1);     //Habilito interrupciones del P0.1
    }
    if(unset==1){
        unset=0;
        SysTick -> CTRL &= ~((1<<0)|(1<<1));    //deshabilito deshabilito el systick y las interrup
        LPC_GPIOINT -> IO0IntEnR |= (1<<1);     //Habilito interrupciones del P0.1
    }
    SysTick->CTRL &= SysTick->CTRL; //Clear flag
}

    //codigo de Gray va de 0 a 15 en 
void rectificar(int num){
    if(num>255){
        contador=0;
    }
}

    //mostramso el asqui de 8bits
void mostrar(int numero){
    unsigned char digito = numero; // Tu número de 8 bits

    // Convertir el número en su representación ASCII
    char ascii = (char)numero;

    printf("Número en ASCII: %c\n", ascii);
}