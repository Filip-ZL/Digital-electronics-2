/**
 * @mainpage
 * Collection of libraries for AVR-GCC
 * @author Filip Jasek & Vojtech Zboril
 *
 * @file
 * @defgroup stopwatch_delta Stopwatch library <delta_time.h>
 * @code #include <delta_time.h> @endcode
 *
 * @brief Function for measuring time start and stop by change state on selected pin
 *
 * Stopwatch is basicaly used to measure time between 2 points, in our case it's measuring time when the echo pin is high.
 * When the echo pin is high the echo burst is traveling in space and it gets low when the echo comes back.
 *
 * This library is offering simple delta time measurement with a deviation of 32 us.
 * The reason of the deviation is because it's the lowest prescaler Atmega 328 provides
 *
 *
 *
 * @author Filip Jasek & Vojtech Zboril
 *
 * @version   1.0
 *
 *
 */


#ifndef DELTA_TIME_H_
#define DELTA_TIME_H_
//@brief Stopwatch function

// libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// @note define change state interrupt enable or disable
#define PCINT16_interrupt_enable()		PCMSK2 |= (1 << PCINT16);	
#define PCINT16_interrupt_disable()		PCMSK2 &= ~(1 << PCINT16);
#define PCINT16_change_level_enable()	EICRA |= (1 << ISC00); PCICR |= (1 << PCIE2);


#define PCINT9_interrupt_enable()		PCMSK1 |= (1 << PCINT9);
#define PCINT9_interrupt_disable()		PCMSK1 &= ~(1 << PCINT9);
#define PCINT9_change_level_enable()	EICRA |= (1 << ISC00); PCICR |= (1 << PCIE1);


// @warning Input port for echo pin is PD0
#define echo			PD0	

// @note Function for initialization deltatime
void deltatime_init(void);

// @note Stopwatch function
uint16_t count_deltatime(volatile uint8_t *reg_name, uint8_t pin_num);

#endif /* DELTA_TIME_H_ */