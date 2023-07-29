/*
 * led.c
 *
 * Created: 9/30/2021 7:32:48 PM
 *  Author: MSI
 */ 
#include "DIO.h"
void LED_init(unsigned char port,unsigned char pin)
{
	DIO_SET_DIR(port,pin,1);
}
void LED_TURN_ON(unsigned char port,unsigned char pin)
{
	DIO_WRITE(port,pin,1);
}
void LED_TURN_OFF(unsigned char port,unsigned char pin)
{
	DIO_WRITE(port,pin,0);
}
void LED_TOGG(unsigned char port,unsigned char pin)
{
	DIO_TOG(port,pin);
}
unsigned char LED_READ_Stat (unsigned char port,unsigned char pin)
{
	return DIO_READ(port,pin);
}