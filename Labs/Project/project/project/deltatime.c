/*
 * count_distance.c
 *
 * Created: 25.11.2020 15:35:25
 *  Author: ffili
 //*/ 
#define F_CPU		16000000	//@warning CPU frequency 

 
#include "gpio.h"
#include "timer.h"
#include "delta_time.h"


// global variables for returned value and current time
uint16_t currentTime = 0;
uint16_t us_deltatime = 0;


void deltatime_init(void)
{
	PCINT16_change_level_enable();
}

uint16_t count_deltatime(volatile uint8_t *reg_name, uint8_t pin_num)
{
	// sends 10 us pulse to trigger
	GPIO_write_high(&*reg_name, pin_num);
	_delay_us(10);
	GPIO_write_low(&*reg_name, pin_num);
	// Interruption start when state is changed
	PCINT16_interrupt_enable();
	sei();
	
	
	return us_deltatime;
	// change state interrupt disabled
	PCINT16_interrupt_disable();
		
}

ISR(PCINT2_vect)
{
	// condition for "rising edge"
	if(PIND & (1 << echo))
	{
		//stopwatch start
		currentTime = 0;
		TIM0_overflow_16u();
		TIM0_overflow_interrupt_enable();
	}
	// condition for "falling edge"
	else
	{
		// stopwatch disabled and deltatime is counted
		TIM0_overflow_interrupt_disable();
		us_deltatime = currentTime*16;
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
