/*
 * Tp4.c
 *
 * Created: 11/7/2022 19:38:01
 * Author : PALA
 */ 

#include "main.h"

volatile uint8_t nuevoComando=0;

int main(void){
	
	Terminal_iniciarPuertoSerie();  //Se configura el puerto serie para poder usar la terminal
	Terminal_configurarRegs();      //Se configura timer 0, timer 1 y ADC3 
	
	uint8_t color=0;  //variable que indica el color que ese esta modificando, 1-Rojo, 2-Verde, 3-Azul, 4-Terminar
	uint8_t rojo=128; //Se configura la intensidad de los colores al iniciar el programa
	uint8_t verde=128;
	uint8_t azul=128;
	
	if(rojo==255) rojo=254;
	else if (rojo==0) rojo=1;
	OCR1A = azul;
	OCR1B = verde;
	
	Terminal_imprimirMenu();
	
    while (1){
		if(nuevoComando){				 //Se activa unicamente si se ingreso un comando valido
			color = Terminal_getColor(); //se obtiene el color a modificar
			
			//Modificacion de color rojo 
			if(color==1){
				while(color==1){
					_delay_ms(1000);
					rojo = Terminal_leerPotenciometro(); //se obtiene la posicion del potenciometro
					Terminal_imprimirValor(rojo);		 //se imprime en la terminal cada un segundo
					if(nuevoComando){
						color = Terminal_getColor();
						if(color!=4) color=1; //Si se quiere entrar a configurar otro color se debe terminar de configurar el actual
					}
				}
				if(rojo==255) rojo=254;
				else if (rojo==0) rojo=1;
				Terminal_imprimirMenu(); //una vez configurado el color volvemos a imprimir el menu
			}
			
			//Modificacion de color verde
			else if(color==2){
				while(color==2){
					_delay_ms(1000);
					verde = Terminal_leerPotenciometro();
					Terminal_imprimirValor(verde);
					if(nuevoComando){
						color = Terminal_getColor();
						if(color!=4) color=2;
					}
				}
				OCR1B = verde;
				Terminal_imprimirMenu();
			}
			
			//Modificacion de color azul 
			else if(color==3){
				while(color==3){
					_delay_ms(1000);
					azul = Terminal_leerPotenciometro();
					Terminal_imprimirValor(azul);
					if(nuevoComando){
						color = Terminal_getColor();
						if(color!=4) color=3;
					}
				}
				OCR1A = azul;
				Terminal_imprimirMenu();
			}
		}
		
		//Pongo en bajo PB5 el tiempo necesario para cumplir con el ciclo de trabajo
		PORTB &= ~(1<<PORTB5);
		OCR0A = rojo;
		TCNT0 = 0;
		while((TIFR0&(1<<OCF0A))==0);
		TIFR0 |= (1<<OCF0A);
		
		//Pongo en alto PB5 el tiempo necesario para completar el periodo
		PORTB |= (1<<PORTB5);
		OCR0A = 255-rojo;
		TCNT0 = 0;
		while((TIFR0&(1<<OCF0A))==0);
		TIFR0 |= (1<<OCF0A);	
    }
}