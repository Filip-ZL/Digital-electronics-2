/*
 * count_distance.c
 *
 * Created: 25.11.2020 15:35:25
 *  Author: ffili
 //*/ 
#define F_CPU		16000000	// CPU frequency

 
#include "gpio.h"
#include "timer.h"
#include "delta_time.h"


// global variables for returned value and current time
uint16_t currentTime = 0;
uint16_t us_deltatime = 0;


void deltatime_init(void)
{
	GPIO_config_output(&DDRB, trigger);
}

uint16_t count_deltatime()
{
	// sends 10 us pulse to trigger
	GPIO_write_high(&PORTB, trigger);
	_delay_us(10);
	GPIO_write_low(&PORTB, trigger);
	TIM0_overflow_16u();
	
	// Interruption start when state is changed
	EICRA |= (1 << ISC00);
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT16);
	sei();
	
	
	return us_deltatime;
}

ISR(PCINT2_vect)
{
	// condition for "rising edge"
	if(PIND & (1 << echo))
	{
		//stopwatch start
		TIM0_overflow_interrupt_enable();
	}
	// condition for "falling edge"
	else
	{
		// stopwatch disabled and currentTime is set to 0
		TIM0_overflow_interrupt_disable();
		us_deltatime = currentTime*16;
		currentTime = 0;
	}
}

// timer/counter - stopwatch
ISR(TIMER0_OVF_vect)
{
	currentTime++;
	// resets when time is over 25ms - max. sensitivity
	if(currentTime > 1563)
	{
		currentTime = 1563;
		
	}	
}