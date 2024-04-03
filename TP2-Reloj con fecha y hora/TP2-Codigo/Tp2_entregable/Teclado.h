/*
 * Teclado.h
 *
 * Created: 14/5/2022 16:37:01
 *  Author: valen
 */ 

#ifndef TECLADO_H_
#define TECLADO_H_
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000ul
#include <util/delay.h>
uint8_t Teclado_KEYPAD_Scan(uint8_t *);
void Teclado_Chequear_Car(uint8_t *);



#endif /* TECLADO_H_ */