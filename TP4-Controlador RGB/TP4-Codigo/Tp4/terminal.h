/*
 * terminal.h
 *
 * Created: 13/7/2022 11:30:06
 *  Author: PALA
 */ 

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <stdint.h>
#include <avr/io.h>
#include "serialPort.h"
#define BR9600 (0x67)    // 0x67=103 configura BAUDRATE=9600@16MHz

void Terminal_iniciarPuertoSerie(void);
void Terminal_configurarRegs(void);
void Terminal_imprimirMenu(void);
uint8_t Terminal_leerPotenciometro(void);
void Terminal_imprimirValor(uint8_t);
uint8_t Terminal_leerComando();
uint8_t Terminal_getColor(void);

#endif /* TERMINAL_H_ */