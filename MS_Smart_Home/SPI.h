/*
 * SPI.h
 *
 * Created: 8/15/2022 9:48:15 PM
 *  Author: MSI
 */ 


#ifndef SPI_H_
#define SPI_H_
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#define SPI_SCK  7
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SS   4
#include "STD_macros.h"
void SPI_init_Master(void);
void SPI_init_Slave(void);
unsigned char SPI_Send_recieve(unsigned char data);

unsigned char SPI_send_string(unsigned char *ptr);



#endif /* SPI_H_ */