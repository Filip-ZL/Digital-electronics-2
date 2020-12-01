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

#define trigger		PB2			// output port for trigger pin
#define echo		PD0			// input port for echo pin

// function for initialization
void deltatime_init(void);

// stopwatch function
uint16_t count_deltatime();

#endif /* DELTA_TIME_H_ */