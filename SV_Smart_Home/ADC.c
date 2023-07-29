
#include "STD_macros.h"
#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void ADC_init()
{
	SET_BIT(ADCSRA,ADEN);
	//SET_BIT(ADMUX,MUX4);
	//Set reference voltge to internal reference voltage
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	// set clock to be 125kHz
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	//ENABLE interrupt
	sei();
	SET_BIT(ADCSRA,ADIE);
	
}
unsigned short ADC_read()
{
	unsigned short value;
	//SET_BIT(ADCSRA,ADSC);
	SET_BIT(ADCSRA,ADATE);
	//while(IS_BIT_SET(ADCSRA,ADSC));
	
	value=ADCL;
	value|=(ADCH<<8);
	return value;
	
}
void ADC_SU_conversion()
{
	SET_BIT(ADCSRA,ADSC);
}