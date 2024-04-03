/*
 * MEF.h
 *
 * Created: 14/5/2022 16:27:39
 *  Author: valen
 */ 


#ifndef MEF_H_
#define MEF_H_
typedef enum {Mostrar_Hora, Modificar_Anio,Modificar_Mes,Modificar_Dia,Modificar_Hora,Modificar_Minutos,Modificar_Segundos} estados;
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000ul
typedef struct{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char date;
	unsigned char month;
	unsigned char year;
}time1;

void MEF_Inciar_modificar ( estados );
void MEF_Actualizar_Modificar(uint8_t ,volatile time1 *);
void MEF_Parpadear(void);
void MEF_inter(time1 );
void MEF_prender(void);
#endif /* MEF_H_ */