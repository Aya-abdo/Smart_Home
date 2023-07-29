/*
 * Timer.h
 *
 * Created: 8/6/2022 8:18:48 PM
 *  Author: MSI
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_macros.h"

void Timer0_CTC_mode_init();
void Timer0_CTC_mode_stop();
void Timer0_generate_signal_non_PWM();
void Timer0_generate_signal_FAST_PWM();
void Timer0_generate_signal_phase_correct_PWM();
void Timer2_RTC_interrupt();
void watch_dog_enable();
void watch_dog_disable();
void Timer2_fastPWM_generate(double degree);
#endif /* TIMER_H_ */