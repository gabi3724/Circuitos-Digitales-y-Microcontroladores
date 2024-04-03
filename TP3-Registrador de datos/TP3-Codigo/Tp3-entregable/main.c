
#include "main.h"

volatile char RX_Buffer=0;
char comando[10];
volatile char nuevoComando=0;

volatile char Buffer[] = "Temperatura: XX,XX C -- Humedad: XX %\n\r\0";//13 14 16 17 33 34
static char msg1[]="Registrador de temperatura y humedad \n\r Ingrese ON: para encender, OFF para apagar, RST para reiniciar\n\r\0";//tamaño 105
static char msg2[]="Comando no valido\n\r\0";
volatile int haydato=0;
volatile char cant=0;
volatile char transmitiendo=0;

volatile int modoAnt;
volatile int modo=0;

int main(void){
	//modo 1(ON): muestra temperatura y humedad cada un segundo
	//modo 2(OFF): frena la transmision de humedad y temperatura
	//modo 3(RST): transmite el menu y frena la transmision de datos
	//modo 4: indica comando no valido 
	
	SerialPort_Init(BR9600);
	SerialPort_TX_Enable();            // Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();            // Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();    // Activo Interrupción de recepcion.
	sei();                                // Activo la mascara global de interrupciones (Bit I del SREG en 1)
	
	//Configuramos por defecto en modo 3
	modo=3;
	haydato=1;
	SerialPort_TX_Interrupt_Enable();
	
	while (1){
		if (nuevoComando){
			Tareas_Main_leercomando(comando);
			if(modo==3){
				haydato=1;
				SerialPort_TX_Interrupt_Enable();
			}
			else if(modo==4){
				haydato=1;
				SerialPort_TX_Interrupt_Enable();		
			}
			nuevoComando=0;
			cant=0;
		}
		if(modo==1){
			_delay_ms(1100);
			Tareas_Main_Tarea1();
			haydato=1;
			SerialPort_TX_Interrupt_Enable();
		}
	}
}

ISR(USART_RX_vect){
	SerialPort_TX_Interrupt_Disable();
	if(cant==0){
		modoAnt=modo;
		modo=2;
	}
	RX_Buffer=SerialPort_Recive_Data();
	if(RX_Buffer!='\r'){
		comando[cant]=RX_Buffer;
		cant++;
	}else{
		comando[cant]='\n';
		nuevoComando=1;
		modo=modoAnt;
	}
}

ISR(USART_UDRE_vect){
	if(haydato){
		if(modo==1){
			static int i=0;
			SerialPort_Send_Data(Buffer[i]);
			i++;
			if(Buffer[i]=='\0'){
				i=0;
				haydato=0;
				SerialPort_TX_Interrupt_Disable();
			}
		}else if(modo==3){
			static int j=0;
			SerialPort_Send_Data(msg1[j]);
			j++;
			if(msg1[j]=='\0'){
				j=0;
				haydato=0;
				SerialPort_TX_Interrupt_Disable();
			}				
		}else if(modo==4){
			static int z=0;
			SerialPort_Send_Data(msg2[z]);
			z++;
			if(msg2[z]=='\0'){
				z=0;
				haydato=0;
				SerialPort_TX_Interrupt_Disable();
				modo=modoAnt;
			}			
		}
	}
}

