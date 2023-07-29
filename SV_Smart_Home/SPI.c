#include "SPI.h"
#include "DIO.h"
void SPI_init_Master(void)
{
	DDRB |=(1<<SPI_MOSI) |(1<<SPI_SS)|(1<<SPI_SCK);
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	
	
}
void SPI_init_Slave(void)
{
	DDRB |= (1<<SPI_MISO) ;//Set the port B miso(master in slave out ) pin as output
	SPCR |= (1<<SPE);//Enable the SPI
	
}
unsigned char SPI_Send_recieve(unsigned char data)
{
	
	SPDR=data;
	while(((SPSR&(1<<SPIF))>>SPIF)==0);
	return SPDR;
	
}
unsigned char SPI_send_string(unsigned char *ptr)
{
	
	while((*ptr)!='/0')
	{
		SPI_Send_recieve(*ptr);
		_delay_ms(300);
		ptr++;
		
		
	}
}
