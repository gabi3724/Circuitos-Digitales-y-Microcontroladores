/*
 * main.h
 *
 * Created: 15/5/2022 20:30:10
 *  Author: PALA
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000ul
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr\interrupt.h>
#include <time.h>
#include "lcd.h"
#include "MEF.h"
#include "Teclado.h"

static char not_leap(void);
void Actualizar_datos(void);
void Iniciar_puertos(void);
void actualizar_lcd(void);


#endif /* MAIN_H_ */