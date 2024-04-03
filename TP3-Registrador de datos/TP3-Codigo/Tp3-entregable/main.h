/*
 * IncFile1.h
 *
 * Created: 26/6/2022 17:59:19
 *  Author: PALA
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DHT11.h"
#include "serialPort.h"
#include "Tareas_Main.h"
#define BR9600 (0x67)    // 0x67=103 configura BAUDRATE=9600@16MHz


#endif /* INCFILE1_H_ */