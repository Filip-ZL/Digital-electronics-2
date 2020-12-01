/*
 * distance_counter.h
 *
 * Created: 25.11.2020 15:29:01
 *  Author: ffili
 */ 


#ifndef DISTANCE_COUNTER_H_
#define DISTANCE_COUNTER_H_

#include <avr/io.h>

#define F_CPU		16000000	// CPU frequency
#define trigger		PB2			// output port for trigger pin
#define echo		PD0			// input port for echo pin


void distance_init(void);
float count_distance();

#endif /* DISTANCE_COUNTER_H_ */