/*
 * UART.c
 *
 * Created: 8/13/2022 8:59:36 PM
 *  Author: MSI
 */ 
#include "UART.h"
void UART_init( unsigned long int baud)
{
	unsigned short ubrr;
	ubrr=((F_CPU/(16*baud))-1);
	UBRRH=ubrr>>8;
	UBRRL=ubrr;
	//enable UART
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	//SIZE OF TRANSMITTED OR RECIEVED DATA
    UCSRC=(1<<7)|(1<<2)|(1<<1);
	
}
void UART_Send_data(unsigned short data)
{
	while(IS_BIT_CLR(UCSRA,UDRE));
	UDR=data;
}
unsigned short UART_recieve_data(void)
{
	while(IS_BIT_CLR(UCSRA,RXC));
	return UDR;
}
void UART_send_String(unsigned char *ptr)
{
	while (*ptr!='/0')
	{
		UART_Send_data(*ptr);
		ptr++;
		_delay_ms(100);
	}
}