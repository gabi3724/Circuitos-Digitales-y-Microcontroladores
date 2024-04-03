/*
 * terminal.c
 *
 * Created: 13/7/2022 11:29:50
 *  Author: PALA
 */ 

#include "terminal.h"

uint8_t color=0;
uint8_t RX_Buffer;
uint8_t bufferRX[10];
uint8_t cant=0;
extern uint8_t nuevoComando;
static uint8_t menu[]="Ingrese R para modificar rojo, V para verde, A para azul, S para para confirmar cambios \r\n";

void Terminal_iniciarPuertoSerie(void){
	SerialPort_Init(BR9600);           // Configuro tramas 8N1 a 9600bps
	SerialPort_TX_Enable();			   // Activo el transmisor del puerto serie
	SerialPort_RX_Enable();            // Activo el Receptor del puerto serie
	SerialPort_RX_Interrupt_Enable();  // Activo Interrupción de recepcion.
	sei();                             // Activo la mascara global de interrupciones
	
}

void Terminal_configurarRegs(void){
	TCCR0A = (1<<WGM01);            //Modo CTC timer 0
	TCCR0B = (1<<CS02) | (1<<CS00); //prescaler 1024
	
	DDRB = (1<<PORTB1) | (1<<PORTB2)| (1<<PORTB5);                               //se configura PB1, PB2 y PB5 como salida
	TCCR1A = (1<<COM1A0) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1B1) | (1<<WGM10); //PWM invertido en PB1 y PB2
	TCCR1B = (1<<CS10)| (1<<CS12) | (1<<WGM12);                                  //Modos fast pwm 8-bits con prescaler 1024
	
	DIDR0 = (1<<ADC3D);                              //se configura el pin del ADC3 como entrada analogica
	ADCSRA= 0x87;                                    //habilitamos el adc y seleccionamos ck/128
	ADMUX= (1 << ADLAR) | (1 << MUX1) | (1 << MUX0); //se elige Vref=AVCC, justificado a la izquierda	
}

void Terminal_imprimirMenu(){
	SerialPort_Send_String(menu);
}

uint8_t Terminal_leerPotenciometro(){
	ADCSRA |= (1<<ADSC);           //Empezar conversion
	while((ADCSRA&(1<<ADIF))==0);  //Esperar a que termine la conversion
	ADCSRA |= (1<<ADIF);           //Limpiar flag
	return ADCH;
}

void Terminal_imprimirValor(uint8_t num){
	static uint8_t c, aux;
	aux=0;
	
	c = num/100;
	if(c!=0){
		aux=1;
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('0'+c);
	}
	
	c = (num%100)/10;
	if(c!=0){
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('0'+c);
		}else if(aux==1){
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('0'+c);
		aux=0;
	}
	
	c = num%100%10;
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+c);
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("\r\n");
}

uint8_t Terminal_leerComando(){
	if((bufferRX[0]=='R') && (bufferRX[1]=='\n'))
		return 1;
	else if((bufferRX[0]=='V') && (bufferRX[1]=='\n'))
		return 2;
	else if((bufferRX[0]=='A') && (bufferRX[1]=='\n'))
		return 3;
	else if((bufferRX[0]=='S') && (bufferRX[1]=='\n'))
		return 4;
	else
		return 0;
}

uint8_t Terminal_getColor(void){
	return color;
}

ISR(USART_RX_vect){
	RX_Buffer = SerialPort_Recive_Data();
	if(RX_Buffer!='\r'){
		bufferRX[cant]=RX_Buffer;
		cant++;
		}else{
		bufferRX[cant]='\n';
		color = Terminal_leerComando();
		if(color!=0){
			nuevoComando=1;
		}
		cant=0;
	}
}