# Smart_Home
I used 2 MCUs atmega32 and modules(Timers,Interrupt,DIO,ADC,EEPROM,UART
communication protocol),LCD, Keypad, LEDS,LM35
I used the first MCU to set the admin and guest passwords and check them after
setting them and used EEPROM for saving these passwords
2022
also the first MCU is connected with keypad and lcd to get instructions and send it to
the other MCU by UART to do these instructions like turning on or off rooms or tv
which are represented by LEDS that are connected to the second MCU
LCD is used to show the status of each room and to give instructions by.
Timer is used for the Block mode when you enter the password wrong many times it
let you wait few seconds till you can enter password again.
ADC is used with LM35 sensor to measure the temperature and turn on or off the air
conditioner according to the temperature I used it with interrupt so the air
conditioner turned on or off automatically.
