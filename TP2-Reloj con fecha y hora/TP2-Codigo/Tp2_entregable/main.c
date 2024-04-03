/*
 * Tp2_entregable.c
 *
 * Created: 2/5/2022 15:00:04
 * Author : Barcala
 */ 

#include "main.h"
uint8_t tecla;
volatile time1 t={59,59,23,31,12,21};


int main(void)
{
	Iniciar_puertos();
	sei();
	
	
	LCDinit();
	_delay_ms(5);
	LCDclr();
	_delay_ms(5);
	actualizar_lcd();
	MEF_Inciar_modificar(Mostrar_Hora);	
	while (1) {
		MEF_Actualizar_Modificar(tecla,&t);
		tecla=-1;
		if (Teclado_KEYPAD_Scan(&tecla)){
			Teclado_Chequear_Car(&tecla);
			_delay_ms(500);
		}
	}
}




void actualizar_lcd(void){
	LCDGotoXY(4,1);
	LCDescribeDato(t.date,2);
	LCDsendChar('/');
	LCDescribeDato(t.month,2);
	LCDsendChar('/');
	LCDescribeDato(t.year,2);
	LCDGotoXY(4,0);
	LCDescribeDato(t.hour,2);
	LCDsendChar(':');
	LCDescribeDato(t.minute,2);
	LCDsendChar(':');
	LCDescribeDato(t.second,2);
}


void actualizar_datos(){
	if (++t.second==60)       
	{
		t.second=0;
		if (++t.minute==60)
		{
			t.minute=0;
			if (++t.hour==24)
			{
				t.hour=0;
				if (++t.date==32)
				{
					t.month++;
					t.date=1;
				}
				else if (t.date==31)
				{
					if ((t.month==4) || (t.month==6) || (t.month==9) || (t.month==11))
					{
						t.month++;
						t.date=1;
					}
				}
				else if (t.date==30)
				{
					if(t.month==2)
					{
						t.month++;
						t.date=1;
					}
				}
				else if (t.date==29)
				{
					if((t.month==2) && (not_leap()))
					{
						t.month++;
						t.date=1;
					}
				}
				if (t.month==13)
				{
					t.month=1;
					t.year++;
				}
			}
		}
	}
}

static char not_leap(void)      //check for leap year
{
	if (!(t.year%100))
	{
		return (char)(t.year%400);
	}
	else
	{
		return (char)(t.year%4);
	}
}

void Iniciar_puertos(void){
	DDRB|=(1<<PORTB0) | (1<<PORTB3) | (1<<PORTB4);
	DDRD|=(1<<PORTD7);
	DDRD &= ~(1<<PORTD3) | ~(1<<PORTD5) | ~(1<<PORTD4) | ~(1<<PORTD2);
	
	TCCR0A = 0x00;
	TCCR0B = 0x05;
	TCNT0 = 100;
	TIMSK0 |= (1<<TOIE0);
}

ISR (TIMER0_OVF_vect){
	static int pulsos=0;
	TCNT0 = 100;
	if(++pulsos == 100){
		actualizar_datos();
		MEF_inter(t);
		pulsos=0;
	}
}