/*
 * delta_time.h
 *
 * Created: 26.11.2020 23:17:00
 *  Author: ffili
 */ 


#ifndef DELTA_TIME_H_
#define DELTA_TIME_H_


// libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PCINT16_interrupt_enable()		PCMSK2 |= (1 << PCINT16);	
#define PCINT16_interrupt_disable()		PCMSK2 &= ~(1 << PCINT16);
#define PCINT16_change_level_enable()	EICRA |= (1 << ISC00); PCICR |= (1 << PCIE2);


#define PCINT9_interrupt_enable()		PCMSK1 |= (1 << PCINT9);
#define PCINT9_interrupt_disable()		PCMSK1 &= ~(1 << PCINT9);
#define PCINT9_change_level_enable()	EICRA |= (1 << ISC00); PCICR |= (1 << PCIE1);


#define echo			PD0			// input port for echo pin

// function for initialization
void deltatime_init(void);

// stopwatch function
uint16_t count_deltatime(volatile uint8_t *reg_name, uint8_t pin_num);

#endif /* DELTA_TIME_H_ */