/*
 * Teclado.c
 *
 * Created: 14/5/2022 16:36:50
 *  Author: valen
 */ 
#include "Teclado.h"
uint8_t Teclado_KEYPAD_Scan(uint8_t *key){
	int c, f;
	
	for (f=0;f<4;f++){
		PORTB|=(1<<PORTB0) | (1<<PORTB3) | (1<<PORTB4);
		PORTD|=(1<<PORTD7);
		PORTD |= (1<<PORTD3) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD2);
		switch(f)
		{
			case 0:
			PORTB &= ~(1<<PORTB4);
			break;

			case 1:
			PORTB &= ~(1<<PORTB3);
			break;

			case 2:
			PORTB &= ~(1<<PORTB0);
			break;

			case 3:
			PORTD &= ~(1<<PORTD7);
			break;
		}
		
		_delay_ms(5);
		
		for(c=0;c<4;c++){
			switch(c)
			{
				case 0:
				if (!(PIND & (1<<PIND3))){
					*key=(f*4+c);
					return 1;
				}
				break;

				case 1:
				if (!(PIND & (1<<PIND5))){
					*key=(f*4+c);
					return 1;
				}
				break;

				case 2:
				if (!(PIND & (1<<PIND4))){
					*key=(f*4+c);
					return 1;
				}
				break;

				case 3:
				if (!(PIND & (1<<PIND2))){
					*key=(f*4+c);
					return 1;
				}
				break;
			}
		}
	}
	return 0;
};

void Teclado_Chequear_Car(uint8_t *c){
	switch(*c)
	{
		case 0:
		*c=(int)'1';
		break;
		case 1:
		*c=(int)'2';
		break;
		case 2:
		*c=(int)'3';
		break;
		case 3:
		*c=(int)'A';
		break;
		case 4:
		*c=(int)'4';
		break;
		case 5:
		*c=(int)'5';
		break;
		case 6:
		*c=(int)'6';
		break;
		case 7:
		*c=(int)'B';
		break;
		case 8:
		*c=(int)'7';
		break;
		case 9:
		*c=(int)'8';
		break;
		case 10:
		*c=(int)'9';
		break;
		case 11:
		*c=(int)'C';
		break;
		case 12:
		*c=(int)'*';
		break;
		case 13:
		*c=(int)'0';
		break;
		case 14:
		*c=(int)'#';
		break;
		case 15:
		*c=(int)'D';
		break;
	}
};