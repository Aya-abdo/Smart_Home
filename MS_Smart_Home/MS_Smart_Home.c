/*
 * MS_Smart_Home.c
 *
 * Created: 8/29/2022 3:43:06 PM
 *  Author: MSI
 */ 


#include "LCD.h"
#include "KEY_PAD.h"
#include "Timer.h"
#include "LED.h"
#include "E2PROM.h"
#include "UART.h"

#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include <util/delay.h>
volatile unsigned char BLcounter=25,sccounter=0;
int main(void)
{
	unsigned char i=0;
	unsigned char value=0xff;
	key_pad_init();
	
	LCD_init();
	LED_init('B',4);
	LED_init('B',5);
	LED_init('B',6);
	UART_init(9600);
	_delay_ms(500);
    while(1)
    {
		LCD_send_string("Welcome to Smart");
		LCD_move_cursor(2,1);
		LCD_send_string("Home!");
		_delay_ms(350);
        if (EEPROM_read(0x002)!=0xff)
        {
			goto l3;
        }
		else
		{
			if (EEPROM_read(0x000)==0xff||EEPROM_read(0x001)==0xff)
			{	
				LCD_clear();
				LCD_send_string("Set Admin Pass: ");
				LCD_move_cursor(2,1);
				
				
				for (i=0;i<4;i++)
				{
					value=0xff;
					do
					{
						value=key_pad_check_press();
					} while (value==0xff);
					LCD_send_char(value);
					_delay_ms(250);
					LCD_move_cursor(2,1+i);
					LCD_send_char('*');
					EEPROM_write(0x003+i,value);
					
				}
				
				EEPROM_write(0x000,0);	
				_delay_ms(350);
				
				LCD_clear();
				LCD_send_string("Set Guest Pass: ");
				LCD_move_cursor(2,1);
				
				for (i=0;i<4;i++)
				{
					value=0xff;
					do
					{
						value=key_pad_check_press();
					} while (value==0xff);
					LCD_send_char(value);
					_delay_ms(250);
					LCD_move_cursor(2,1+i);
					EEPROM_write(0x007+i,value);
					LCD_send_char('*');
				}
				EEPROM_write(0x001,0);
				goto l1;
				}
		
				
				
						
			else
			{
			l1:	LCD_clear();
				LCD_send_string("0:Admin  1:Guest");
				value=0xff;
				do 
				{
					value=key_pad_check_press();
				} while (value==0xff);
				if (value!='0'&&value!='1')
				{
					LCD_clear();
					LCD_send_string("wrong choice");
					_delay_ms(100);
					goto l1;
					
				}
				else if (value=='0')
				{
					_delay_ms(500);
					unsigned char tries=3;
					sccounter=0;
					BLcounter=25;
					
					while(tries>0)
					{
							LCD_clear();
							LCD_send_string("Check A. Pass: ");
							LCD_move_cursor(2,1);
							unsigned char arr1[4];
							for (i=0;i<4;i++)
							{
								value=0xff;
								do
								{
									value=key_pad_check_press();
								} while (value==0xff);
								arr1[i]=value;
								
								LCD_send_char(value);
								_delay_ms(250);
								LCD_move_cursor(2,1+i);
								LCD_send_char('*');
							}
							if (arr1[0]!=EEPROM_read(0x003)||arr1[1]!=EEPROM_read(0x004)||arr1[2]!=EEPROM_read(0x005)||arr1[3]!=EEPROM_read(0x006))
							{
								LCD_clear();
								LCD_send_string("Wrong Pass");
								tries--;
								_delay_ms(350);
								LCD_clear();
								if(tries==0)
								{
									
									LCD_clear();
									LCD_send_string("You entered");
									LCD_move_cursor(2,1);
									LCD_send_string("block mode");
									
									_delay_ms(350);
									LCD_clear();
									EEPROM_write(0x002,0);
									
									LED_TURN_ON('B',4);
									LCD_send_string("wait for 25 sec");
									Timer0_CTC_mode_init();
									while(BLcounter>0)
									{
										if (sccounter>=100)
										{
											sccounter=0;
											BLcounter--;
											LCD_move_cursor(2,1);
											LCD_send_char((BLcounter/10)+'0');
											LCD_send_char((BLcounter%10)+'0');
											LCD_send_string(" remaining");
										}
									}
								
									EEPROM_write(0x002,0xff);
									LED_TURN_OFF('B',4);
									goto l1;
								}
								LCD_send_char(tries+'0');
								LCD_move_cursor(1,3);
								LCD_send_string("Tries Left");
								_delay_ms(350);
								continue;
							}
							else
							{
								unsigned char state5,state6,state7,state8,state9,state10;
								LCD_clear();
								LCD_send_string("right pass");
								_delay_ms(300);
								LED_TURN_ON('B',5);
								l8:LCD_clear();
								LCD_send_string("1:ROOM1  2:ROOM2");
								LCD_move_cursor(2,1);
								LCD_send_string("3:ROOM3  4:OTHER");
								value=0xff;
								do 
								{
									value=key_pad_check_press();
								} while (value==0xff);
								if (value!='1'&&value!='2'&&value!='3'&&value!='4')
								{
									LCD_clear();
									LCD_send_string("wrong choice");
									_delay_ms(300);
									goto l8;
								}
								else if (value=='1')
								{
									l9:UART_Send_data(0x10);
									state5=UART_recieve_data();
									if (state5==1)
									{
										  LCD_clear();
										  LCD_send_string("state:ON");
										  LCD_move_cursor(2,1);
										  LCD_send_string("0:OFF 1:ON 2:ret");
									}
									else if (state5==0)
									{
										  LCD_clear();
										  LCD_send_string("state:OFF");
										  LCD_move_cursor(2,1);
										  LCD_send_string("0:OFF 1:ON 2:ret");
									}
									value=0xff;
									do 
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='0'&&value!='1'&&value!='2')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										UART_Send_data(0x60);
										LCD_clear();
										goto l9;
										
									}
									else if (value=='0')
									{
										UART_Send_data(0x20);
										goto l9;
									}
									else if (value=='1')
									{
										UART_Send_data(0x21);
										goto l9;
									}
									else if (value=='2')
									{
										UART_Send_data(0x60);
										goto l8;
									}
								}
								else if (value=='2')
								{
									l10:UART_Send_data(0x11);
									state6=UART_recieve_data();
									if (state6==1)
									{
										LCD_clear();
										LCD_send_string("state:ON");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									else if (state6==0)
									{
										LCD_clear();
										LCD_send_string("state:OFF");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									value=0xff;
									do
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='0'&&value!='1'&&value!='2')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										UART_Send_data(0x60);
										LCD_clear();
										goto l9;
										
									}
									else if (value=='0')
									{
										UART_Send_data(0x30);
										goto l10;
									}
									else if (value=='1')
									{
										UART_Send_data(0x31);
										goto l10;
									}
									else if (value=='2')
									{
										UART_Send_data(0x60);
										goto l8;
									}
								}
								else if (value=='3')
								{
									l11:UART_Send_data(0x12);
									state7=UART_recieve_data();
									if (state7==1)
									{
										LCD_clear();
										LCD_send_string("state:ON");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									else if (state7==0)
									{
										LCD_clear();
										LCD_send_string("state:OFF");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									value=0xff;
									do
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='0'&&value!='1'&&value!='2')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										UART_Send_data(0x60);
										LCD_clear();
										goto l11;
										
									}
									else if (value=='0')
									{
										UART_Send_data(0x40);
										goto l11;
									}
									else if (value=='1')
									{
										UART_Send_data(0x41);
										goto l11;
									}
									else if (value=='2')
									{
										UART_Send_data(0x60);
										goto l8;
									}
								}
								else if (value=='4')
								{
									l12:LCD_clear();
									LCD_send_string("5:ROOM4  6:TV");
									LCD_move_cursor(2,1);
									LCD_send_string("7:AIR_CO.  8:RET");
								}
								value=0xff;
								do 
								{
									value=key_pad_check_press();
								} while (value==0xff);
								if (value!='5'&&value!='6'&&value!='7'&&value!='8')
								{
									LCD_clear();
									LCD_send_string("wrong choice");
									_delay_ms(300);
									goto l12;
								}
								else if (value=='5')
								{
									l13:UART_Send_data(0x13);
									state8=UART_recieve_data();
									
									if (state8==0)
									{
										
										  LCD_clear();
										  LCD_send_string("state:OFF");
										  LCD_move_cursor(2,1);
										  LCD_send_string("0:OFF 1:ON 2:ret");
									}
									else if (state8==1)
									{
										  LCD_clear();
										  LCD_send_string("state:ON");
										  LCD_move_cursor(2,1);
										  LCD_send_string("0:OFF 1:ON 2:ret");
									}
									value=0xff;
									do 
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='0'&&value!='1'&&value!='2')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										UART_Send_data(0x60);
										goto l13;
									}
									else if (value=='0')
									{
										UART_Send_data(0x50);
										goto l13;
									}
									else if (value=='1')
									{
										UART_Send_data(0x51);
										goto l13;
									}
									else if (value=='2')
									{
										UART_Send_data(0x60);
										goto l12;
									}
									
								}
								else if (value=='6')
								{
									l14:UART_Send_data(0x14);
									state9=UART_recieve_data();
									
									if (state9==0)
									{
										
										LCD_clear();
										LCD_send_string("state:OFF");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									else if (state9==1)
									{
										LCD_clear();
										LCD_send_string("state:ON");
										LCD_move_cursor(2,1);
										LCD_send_string("0:OFF 1:ON 2:ret");
									}
									value=0xff;
									do
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='0'&&value!='1'&&value!='2')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										UART_Send_data(0x60);
										goto l14;
									}
									else if (value=='0')
									{
										UART_Send_data(0x70);
										goto l14;
									}
									else if (value=='1')
									{
										UART_Send_data(0x71);
										goto l14;
									}
									else if (value=='2')
									{
										UART_Send_data(0x60);
										goto l12;
									}
									
								}
								else if (value=='7')
								{
									l15:LCD_clear();
									LCD_send_string("1:Set Temp.");
									LCD_move_cursor(2,1);
									LCD_send_string("2:Control  3:RET");
									value=0xff;
									do 
									{
										value=key_pad_check_press();
									} while (value==0xff);
									if (value!='1'&&value!='2'&&value!='3')
									{
										LCD_clear();
										LCD_send_string("wrong choice");
										_delay_ms(300);
										goto l15;
										
									}
									else if (value=='1')
									{
										UART_Send_data(0x16);
										unsigned char degree_con=0;
										LCD_clear();
										LCD_send_string("Set Temp.=__");
										LCD_move_cursor(1,14);
										LCD_send_char(0xDF);
										LCD_send_char('C');
										_delay_ms(300);
										value=0xff;
										LCD_move_cursor(1,11);
										do
										{
											value=key_pad_check_press();
										} while (value==0xff);
										degree_con=(value-'0')*10;
										LCD_send_char(value);
										_delay_ms(300);
										value=0xff;
										LCD_move_cursor(1,12);
											do
											{
												value=key_pad_check_press();
											} while (value==0xff);
												degree_con=degree_con+(value-'0');
												
												LCD_send_char(value);
												UART_Send_data(degree_con);
												_delay_ms(300);
												
												goto l15;	
											
										
											
											
									
										
										
									}
									else if (value=='2')
									{
										l16:UART_Send_data(0x15);
										state10=UART_recieve_data();
										LCD_clear();
										if (state10==0)
										{
											  LCD_clear();
											  LCD_send_string("state:OFF");
											  LCD_move_cursor(2,1);
											  LCD_send_string("0:OFF 1:ON 2:ret");
										}
										else if (state10==1)
										{
											  LCD_clear();
											  LCD_send_string("state:ON");
											  LCD_move_cursor(2,1);
											  LCD_send_string("0:OFF 1:ON 2:ret");
										}
										value=0xff;
										do 
										{
											value=key_pad_check_press();
										} while (value==0xff);
										if (value!='0'&&value!='1'&&value!='2')
										{
											LCD_clear();
											LCD_send_string("wrong choice");
											_delay_ms(300);
											UART_Send_data(0x60);
											goto l16;
											
											
										}
										else if (value=='0')
										{
											UART_Send_data(0x80);
											goto l15;
										}
										else if (value=='1')
										{
											UART_Send_data(0x81);
											goto l15;
										}
										else if (value=='2')
										{
											goto l15;
										}
																				
										
									}
									
									else if (value=='3')
									{
										goto l12;
									}
							
								}
								else if (value=='8')
								{
									UART_Send_data(0x60);
									goto l8;
								}
							}
					}
				
				
				}
					else if (value=='1')
					{
						
						_delay_ms(500);
						unsigned char tries=3;
						sccounter=0;
						BLcounter=25;
						while(tries>0)
						{
							LCD_clear();
							LCD_send_string("Check G. Pass: ");
							LCD_move_cursor(2,1);
							unsigned char arr2[4];
							for (i=0;i<4;i++)
							{
								value=0xff;
								do
								{
									value=key_pad_check_press();
								} while (value==0xff);
								arr2[i]=value;
								
								LCD_send_char(value);
								_delay_ms(350);
								LCD_move_cursor(2,1+i);
								LCD_send_char('*');
								}								
							
							if (arr2[0]!=EEPROM_read(0x007)||arr2[1]!=EEPROM_read(0x008)||arr2[2]!=EEPROM_read(0x009)||arr2[3]!=EEPROM_read(0x00A))
							{
								LCD_clear();
								LCD_send_string("Wrong Pass");
								tries--;
								_delay_ms(350);
								LCD_clear();
								if(tries==0)
								{
									
									LCD_clear();
									LCD_send_string("You entered");
									LCD_move_cursor(2,1);
									LCD_send_string("block mode");
									
									_delay_ms(350);
									LCD_clear();
									EEPROM_write(0x002,0);
									l3:LCD_clear();
									LED_TURN_ON('B',4);
									LCD_send_string("wait for 25 sec");
									Timer0_CTC_mode_init();
									while(BLcounter>0)
									{
										if (sccounter>=100)
										{
											sccounter=0;
											BLcounter--;
											LCD_move_cursor(2,1);
											LCD_send_char((BLcounter/10)+'0');
											LCD_send_char((BLcounter%10)+'0');
											LCD_send_string(" remaining");
										}
									}
									
									EEPROM_write(0x002,0xff);
									LED_TURN_OFF('B',4);
									goto l1;
								}
								LCD_send_char(tries+'0');
								LCD_move_cursor(1,3);
								LCD_send_string("Tries Left");
								_delay_ms(350);
								continue;
								
							}
							else
							{
								
								LCD_clear();
								LCD_send_string("right pass");
								
								_delay_ms(300);
								LED_TURN_ON('B',6);
								unsigned char state1,state2,state3,state4;
									  value=0xff;
									 
									l2:  LCD_clear();
									  LCD_send_string("1:ROOM1  2:ROOM2");
									  LCD_move_cursor(2,1);
									  LCD_send_string("3:ROOM3  4:ROOM4");
									  
									  do
									  {
										  value=key_pad_check_press();
									  } while (value==0xff);
									  	if (value!='1'&&value!='2'&&value!='3'&&value!='4')
									  	{
										  	
										  	LCD_clear();
										  	LCD_send_string("wrong choice");
										  	_delay_ms(500);
										  	goto l2;
									  	}
										  else if (value=='1')
										  {
											 l4: UART_Send_data(0x10);
											  state1=UART_recieve_data();
												if (state1==1)
												{
													LCD_clear();
													LCD_send_string("state:ON");
													LCD_move_cursor(2,1);
													LCD_send_string("0:OFF 1:ON 2:ret");
												}
												else if (state1==0)
												{
													LCD_clear();
													LCD_send_string("state:OFF");
													LCD_move_cursor(2,1);
													LCD_send_string("0:OFF 1:ON 2:ret");
												}
												value=0xff;
												  do
												  {
													  value=key_pad_check_press();
												  } while (value==0xff);
												  if (value!='0'&&value!='1'&&value!='2')
												  {
													  LCD_clear();
													  LCD_send_string("wrong choice");
													  _delay_ms(500);
													  
													 UART_Send_data(0x60);
													  
													  goto l4;
												  }
												  else if (value=='0')
												  {
													  UART_Send_data(0x20);
													  goto l4;
												  }
												  	  else if (value=='1')
												  	  {
													  	  UART_Send_data(0x21);
													  	   goto l4;
													  	 
													  	  
												  	  }
												  	  else if (value=='2')
												  	  {
													  	  
													  	  UART_Send_data(0x60);
															_delay_ms(500);
															goto l2;
													  	  
													  	  
													  	  
												  	  }
										  }
										   else if (value=='2')
										   {
											   l5: UART_Send_data(0x11);
											   state2=UART_recieve_data();
											   if (state2==1)
											   {
												   LCD_clear();
												   LCD_send_string("state:ON");
												   LCD_move_cursor(2,1);
												   LCD_send_string("0:OFF 1:ON 2:ret");
											   }
											   else if (state2==0)
											   {
												   LCD_clear();
												   LCD_send_string("state:OFF");
												   LCD_move_cursor(2,1);
												   LCD_send_string("0:OFF 1:ON 2:ret");
											   }
											   value=0xff;
											   do
											   {
												   value=key_pad_check_press();
											   } while (value==0xff);
											   if (value!='0'&&value!='1'&&value!='2')
											   {
												   LCD_clear();
												   LCD_send_string("wrong choice");
												   _delay_ms(500);
												   
												   UART_Send_data(0x60);
												   
												   goto l5;
											   }
											   else if (value=='0')
											   {
												   UART_Send_data(0x30);
												   goto l5;
											   }
											   else if (value=='1')
											   {
												   UART_Send_data(0x31);
												   goto l5;
												   
												   
											   }
											   else if (value=='2')
											   {
												   
												   UART_Send_data(0x60);
												   _delay_ms(500);
												   goto l2;
												   
												   
												   
											   }
										   }
										    else if (value=='3')
										    {
											    l6: UART_Send_data(0x12);
											    state3=UART_recieve_data();
											    if (state3==1)
											    {
												    LCD_clear();
												    LCD_send_string("state:ON");
												    LCD_move_cursor(2,1);
												    LCD_send_string("0:OFF 1:ON 2:ret");
											    }
											    else if (state3==0)
											    {
												    LCD_clear();
												    LCD_send_string("state:OFF");
												    LCD_move_cursor(2,1);
												    LCD_send_string("0:OFF 1:ON 2:ret");
											    }
											    value=0xff;
											    do
											    {
												    value=key_pad_check_press();
											    } while (value==0xff);
											    if (value!='0'&&value!='1'&&value!='2')
											    {
												    LCD_clear();
												    LCD_send_string("wrong choice");
												    _delay_ms(500);
												    
												    UART_Send_data(0x60);
												    
												    goto l6;
											    }
											    else if (value=='0')
											    {
												    UART_Send_data(0x40);
												    goto l6;
											    }
											    else if (value=='1')
											    {
												    UART_Send_data(0x41);
												    goto l6;
												    
												    
											    }
											    else if (value=='2')
											    {
												    
												    UART_Send_data(0x60);
												    _delay_ms(500);
												    goto l2;
												    
												    
												    
											    }
										    }
											 else if (value=='4')
											 {
												 l7: UART_Send_data(0x13);
												 state4=UART_recieve_data();
												 if (state4==1)
												 {
													 LCD_clear();
													 LCD_send_string("state:ON");
													 LCD_move_cursor(2,1);
													 LCD_send_string("0:OFF 1:ON 2:ret");
												 }
												 else if (state4==0)
												 {
													 LCD_clear();
													 LCD_send_string("state:OFF");
													 LCD_move_cursor(2,1);
													 LCD_send_string("0:OFF 1:ON 2:ret");
												 }
												 value=0xff;
												 do
												 {
													 value=key_pad_check_press();
												 } while (value==0xff);
												 if (value!='0'&&value!='1'&&value!='2')
												 {
													 LCD_clear();
													 LCD_send_string("wrong choice");
													 _delay_ms(500);
													 
													 UART_Send_data(0x60);
													 
													 goto l7;
												 }
												 else if (value=='0')
												 {
													 UART_Send_data(0x50);
													 goto l7;
												 }
												 else if (value=='1')
												 {
													 UART_Send_data(0x51);
													 goto l7;
													 
													 
												 }
												 else if (value=='2')
												 {
													 
													 UART_Send_data(0x60);
													 _delay_ms(500);
													 goto l2;
													 
													 
													 
												 }
											 }
								
											
													   
														    
									  }					
												    }
											    }
								}									
						      
							
							
																							
									
									
									
								}
								
							}
							}
ISR(TIMER0_COMP_vect)
						
	{
		sccounter++;

	}							
																	
						
							
