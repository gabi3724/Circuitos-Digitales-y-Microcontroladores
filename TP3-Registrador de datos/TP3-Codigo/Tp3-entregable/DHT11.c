/*
 * DHT11.c
 *
 * Created: 17/6/2022 17:29:54
 *  Author: valen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int i;
int h=0;
int hd=0;
int t=0;
int td=0;
int sumcheck=0;

void dht11_iniciaryleerdato(int *temp , int *tempD, int *hum){
	int cant;
	h=0;
	hd=0;
	t=0;
	td=0;
	sumcheck=0;
	
	//configuro el pin C0 como salida y lo pongo en alto;
	DDRC |= (1<<PORTC0);
	PORTC |=(1<<PORTC0);
	_delay_ms(20);
	
	//Hago 0 la señal por al menos 18 ms (start signal)
	PORTC &= ~(1<<PORTC0);
	_delay_ms(18);
	
	//configura como entrada pull up c0 y pongo en alto la señal y en un lapso de 20 a 40us el sensor deberia responder
	DDRC &=~(1<<PORTC0);
	PORTC |=(1<<PORTC0);

	//espero a que el sensor responda bajando la señal por 80us y despues subiendola por 80us
	while(PINC & (1<<PORTC0));//mientras siga en alto espero a que el sensor la haga cero
	while((PINC & (1<<PORTC0))==0);//mientras este en cero espero a que el sensor la haga uno
	
	//Empieza la transmision de datos
	
	//huemdad entero
	for(i=0; i<8; i++){
		cant=0;
		while(PINC & (1<<PORTC0)); //Espero los 50us que tarda en enviar un bit
		while((PINC & (1<<PORTC0))==0);//Una vez que esta en alto esta trasmitiendo el bit de informacion
		while(PINC & (1<<PORTC0)){
			_delay_us(1);
			cant++;
		}
		if(cant < 29)
			h = (h<<1);
		else
			h = (h<<1)|(0x01);
	}
	
	//humedad decimal
	for(i=0; i<8; i++){
		cant=0;
		while(PINC & (1<<PORTC0));
		while((PINC & (1<<PORTC0))==0);
		while(PINC & (1<<PORTC0)){
			_delay_us(1);
			cant++;
		}
		if(cant < 29)
			hd = (hd<<1);
		else
			hd = (hd<<1)|(0x01);
	}

	//temperatura entero
	for(i=0; i<8; i++){
		cant=0;
		while(PINC & (1<<PORTC0));
		while((PINC & (1<<PORTC0))==0);
		while(PINC & (1<<PORTC0)){
			_delay_us(1);
			cant++;
		}
		if(cant < 29)
			t = (t<<1);
		else
			t = (t<<1)|(0x01);
	}
	
	//temperatura decimal
	for(i=0; i<8; i++){
		cant=0;
		while(PINC & (1<<PORTC0));
		while((PINC & (1<<PORTC0))==0);
		while(PINC & (1<<PORTC0)){
			_delay_us(1);
			cant++;
		}
		if(cant < 29)
			td = (td<<1);
		else
			td = (td<<1)|(0x01);
	}
	
	//sumcheck
	for(i=0; i<8; i++){
		cant=0;
		while(PINC & (1<<PORTC0));
		while((PINC & (1<<PORTC0))==0);
		while(PINC & (1<<PORTC0)){
			_delay_us(1);
			cant++;
		}
		if(cant < 29)
			sumcheck = (sumcheck<<1);
		else
			sumcheck = (sumcheck<<1)|(0x01);
	}
	
	*temp = t; 
	*tempD = td; 
	*hum = h;
	
};