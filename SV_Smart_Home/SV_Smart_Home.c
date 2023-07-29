/*
 * SV_Smart_Home.c
 *
 * Created: 8/29/2022 10:15:06 PM
 *  Author: MSI
 */ 

#include "ADC.h"
#include "UART.h"
#include "LED.h"
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
volatile unsigned char degree_room=0,degree_con=0,f=0,n=0,con_state=0;
int main(void)
{
	ADC_init();
	UART_init(9600);
	
	LED_init('C',0);
	LED_init('C',1);
	LED_init('C',2);
	LED_init('C',3);
	LED_init('C',6);
	LED_init('C',7);
		unsigned char request=0xff,response=0xff;
		
		
		
		while(1)
		{
			
			
			
			request=UART_recieve_data();
			switch(request)
			{
				case 0x10:
				
				
				response=LED_READ_Stat('C',0);
				UART_Send_data(response);
				break;
				case 0x11:
				response=LED_READ_Stat('C',1);
				UART_Send_data(response);
				break;
				case 0x12:
				response=LED_READ_Stat('C',2);
				UART_Send_data(response);
				break;
				case 0x13:
				response=LED_READ_Stat('C',3);
				UART_Send_data(response);
				break;
				case 0x14:
				response=LED_READ_Stat('C',7);
				UART_Send_data(response);
				break;
				case 0x16:
				
				//degree_room=0.25*ADC_read();
				
				degree_con=UART_recieve_data();
				n=1;
				ADC_SU_conversion();
				
				/*if (f==1&&degree_room>=degree_con)
				{
					
					LED_TURN_ON('C',6);
				}
				else if (f==1&&degree_room<degree_con)
				{
					LED_TURN_OFF('C',6);
				}
				*/
				break;
				
				case 0x15:
				response=LED_READ_Stat('C',6);
				UART_Send_data(response);
				break;
				case 0x20:
				LED_TURN_OFF('C',0);
				
				
				
				
				break;
				case 0x21:
				LED_TURN_ON('C',0);
				
				
				break;
				case 0x30:
				LED_TURN_OFF('C',1);
				break;
				case 0x31:
				LED_TURN_ON('C',1);
				break;
				case 0x40:
				LED_TURN_OFF('C',2);
				break;
				case 0x41:
				LED_TURN_ON('C',2);
				break;
				case 0x50:
				LED_TURN_OFF('C',3);
				break;
				case 0x51:
				LED_TURN_ON('C',3);
				break;
				case 0x70:
				LED_TURN_OFF('C',7);
				break;
				case 0x71:
				LED_TURN_ON('C',7);
				break;
				case 0x80:
				LED_TURN_OFF('C',6);
				f=0;
				
				
				break;
				case 0x81:
				f=1;
			
				ADC_SU_conversion();
				
				
				/*if (degree_room<degree_con)
				{
					LED_TURN_OFF('C',6);
				}
				else if (degree_room>degree_con&&degree_con!=0)
				{
					LED_TURN_ON('C',6);
				}
				*/
				break;
				
				
				case 0x60:
				continue;
				
			
			}
				
			

	
	
				
		
      
		
    }
}	
ISR(ADC_vect)
{
	
	degree_room=0.25*ADC_read();
	if (f==1)
	{
		if (n==1)
				{
					if (degree_room>degree_con)
					{
						LED_TURN_ON('C',6);
					
					}
					else if (degree_room<=degree_con)
					{
						LED_TURN_OFF('C',6);
					}
					n=0;
					//_delay_ms(500);
				}
				else{
					if (degree_room<=degree_con)
					{
						LED_TURN_OFF('C',6);
					}
					else if (degree_room>degree_con&&degree_con!=0)
					{
						LED_TURN_ON('C',6);
					}
				
				
		}
	
		
			
			ADC_SU_conversion();
	}

}