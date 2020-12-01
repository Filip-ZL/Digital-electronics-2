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

uint16_t currentTime = 0;
uint16_t us_deltatime = 0;


void deltatime_init(void)
{
	GPIO_config_output(&DDRB, trigger);
}

uint16_t count_deltatime()
{
	GPIO_write_high(&PORTB, trigger);
	_delay_us(10);
	GPIO_write_low(&PORTB, trigger);
	TIM0_overflow_16u();
	
	EICRA |= (1 << ISC00);
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT16);
	sei();
	return us_deltatime;
}

ISR(PCINT2_vect)
{
	if(PIND & (1 << echo))
	{
		TIM0_overflow_interrupt_enable();
	}
	else
	{
		TIM0_overflow_interrupt_disable();
		us_deltatime = currentTime*16;
		currentTime = 0;
	}
}

ISR(TIMER0_OVF_vect)
{
	currentTime++;
	// resets when time is over 25ms
	if(currentTime > 1563)
	{
		currentTime = 1563;
		
	}	
}