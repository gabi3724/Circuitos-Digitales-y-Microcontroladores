/*
 * MEF.c
 *
 * Created: 14/5/2022 16:25:36
 *  Author: valen
 */ 
#include "MEF.h"
#include "lcd.h"
static estados Modificar;
static uint8_t posx;
static uint8_t posy;
static time1 taux={56,58,23,19,4,21};
void MEF_Inciar_modificar ( estados m)
{
	Modificar = m; // poner un estado inicial
}

void MEF_Actualizar_Modificar(uint8_t tecla,volatile time1 *t)
{
	switch (Modificar)
	{
		case Mostrar_Hora:
		if(tecla == 'A')
		{
			taux=*t;
			Modificar = Modificar_Anio;
		}
		break;
		case Modificar_Anio:
		posx=10;
		posy=1;
		if(tecla == 'A')
		{
			Modificar = Modificar_Mes;
			MEF_prender();
		}
		else{
			if (tecla == 'B'){
				taux.year++;
				if (taux.year==100)
				{
					taux.year=00;
				}
			}
			else{
				if (tecla == 'C'){
					taux.year--;
					if (taux.year==255)
					{
						taux.year=99;
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
		case Modificar_Mes:
		posx=7;
		posy=1;
		if(tecla == 'A')
		{
			Modificar = Modificar_Dia;
			MEF_prender();
		}
		else{
			if (tecla == 'B'){
				taux.month++;
				if (taux.month==13)
				{
					taux.month=1;
				}
			}
			else{
				if (tecla == 'C'){
					taux.month--;
					if (taux.month==0)
					{
						taux.month=12;
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
		case Modificar_Dia:
		posx=4;
		posy=1;
		if(tecla == 'A')
		{
			Modificar = Modificar_Hora;
			MEF_prender();
		}
		else{
			if (tecla == 'B'){
				taux.date++;
				if (taux.month==1 || taux.month==3 || taux.month==5 || taux.month==7 || taux.month==8 || taux.month==10 || taux.month==12){
					if (taux.date==32)
					{
						taux.date=1;
					}
				}
				else{
					if (taux.month==2){
						if (taux.date==29)
						{
							taux.date=1;
						}
					}
					else{
						if (taux.date==31)
						{
							taux.date=1;
						}
					}
				}
				
			}
			else{
				if (tecla == 'C'){
					taux.date--;
					if (taux.date==0)
					{
						if (taux.month==1 || taux.month==3 || taux.month==5 || taux.month==7 || taux.month==8 || taux.month==10 || taux.month==12){
							taux.date=31;
						}
						else{
							if (taux.month==2){
								taux.date=28;
							}
							else{
								taux.date=30;
								
							}
						}
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
		case Modificar_Hora:
		posx=4;
		posy=0;
		if(tecla == 'A')
		{
			Modificar = Modificar_Minutos;
			MEF_prender();
		}
		else{
			if (tecla == 'B'){
				taux.hour++;
				if (taux.hour==24)
				{
					taux.hour=0;
				}
			}
			else{
				if (tecla == 'C'){
					taux.hour--;
					if (taux.hour==255)
					{
						taux.hour=23;
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
		case Modificar_Minutos:
		posx=7;
		posy=0;
		if(tecla == 'A')
		{
			Modificar = Modificar_Segundos;
			MEF_prender();
		}
		else{
			if (tecla == 'B'){
				taux.minute++;
				if (taux.minute==60)
				{
					taux.minute=0;
				}
			}
			else{
				if (tecla == 'C'){
					taux.minute--;
					if (taux.minute==255)
					{
						taux.minute=59;
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
		case Modificar_Segundos:
		posx=10;
		posy=0;
		if(tecla == 'A')
		{
			Modificar = Mostrar_Hora;
			MEF_prender();
			*t=taux;
		}
		else{
			if (tecla == 'B'){
				taux.second++;
				if (taux.second==60)
				{
					taux.second=0;
				}
				
			}
			else{
				if (tecla == 'C'){
					taux.second--;
					if (taux.second==255)
					{
						taux.second=59;
					}
				}
				else{
					if (tecla == 'D'){
						Modificar = Mostrar_Hora;
					}
				}
			}
		}
		break;
	}
}

void MEF_Parpadear(void){
	static uint8_t encoap=0;
	LCDGotoXY(posx, posy);
	if (encoap==0){
		encoap=1;
		LCDstring("  ",2);
	}
	else{
		encoap=0;
		switch(Modificar){
			case Modificar_Dia:
			LCDescribeDato(taux.date,2);
			break;
			case Modificar_Mes:
			LCDescribeDato(taux.month,2);
			break;
			case Modificar_Anio:
			LCDescribeDato(taux.year,2);
			break;
			case Modificar_Hora:
			LCDescribeDato(taux.hour,2);
			break;
			case Modificar_Minutos:
			LCDescribeDato(taux.minute,2);
			break;
			case Modificar_Segundos:
			LCDescribeDato(taux.second,2);
			break;
			default: break;
		}
	}
};

void MEF_inter(time1 t){
	if(Modificar!=Mostrar_Hora){
		MEF_Parpadear();
	}
	else{
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
}

void MEF_prender(){
	LCDGotoXY(4,1);
	LCDescribeDato(taux.date,2);
	LCDsendChar('/');
	LCDescribeDato(taux.month,2);
	LCDsendChar('/');
	LCDescribeDato(taux.year,2);
	LCDGotoXY(4,0);
	LCDescribeDato(taux.hour,2);
	LCDsendChar(':');
	LCDescribeDato(taux.minute,2);
	LCDsendChar(':');
	LCDescribeDato(taux.second,2);
}