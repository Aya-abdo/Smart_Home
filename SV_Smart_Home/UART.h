/*
 * UART.h
 *
 * Created: 8/13/2022 8:59:51 PM
 *  Author: MSI
 */ 


#ifndef UART_H_
#define UART_H_
#define F_CPU 8000000UL
#include "STD_macros.h"
#include <util/delay.h>
#include <avr/io.h>
void UART_init( unsigned long int baud);
void UART_Send_data(unsigned short data);
unsigned short UART_recieve_data(void);
void UART_send_String(unsigned char *ptr);




#endif /* UART_H_ */