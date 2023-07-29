/*
 * led.h
 *
 * Created: 9/30/2021 7:32:15 PM
 *  Author: MSI
 */ 


#ifndef LED_H_
#define LED_H_
void LED_init(unsigned char port,unsigned char pin);
void LED_TURN_ON(unsigned char port,unsigned char pin);
void LED_TURN_OFF(unsigned char port,unsigned char pin);
void LED_TOGG(unsigned char port,unsigned char pin);
unsigned char LED_READ_Stat (unsigned char port,unsigned char pin);





#endif /* LED_H_ */