/*
 * delta_time.h
 *
 * Created: 26.11.2020 23:17:00
 *  Author: ffili
 */ 


#ifndef DELTA_TIME_H_
#define DELTA_TIME_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>

#define trigger		PB2			// output port for trigger pin
#define echo		PD0			// input port for echo pin


void deltatime_init(void);
uint16_t count_deltatime();

#endif /* DELTA_TIME_H_ */