/*
 * morse.c
 *
 * Created: 23.09.2020 21:04:20
 * Author : ffili
 */ 
#define LED_GREEN	PB5
#define LONG_DELAY	3000
#define MESSAGE_SIZE	9
#define SHORT_DELAY	500
#define PAUSE	300
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>


int main(void)
{
	int morse[MESSAGE_SIZE] = {1,0,0,0,0,0,1,1,1};
	DDRB = DDRB | (1<<LED_GREEN);
	
	PORTB = PORTB & ~(1<<LED_GREEN);
    /* Replace with your application code */
	int i;
    while (1) 
    {
		for ( i = 0; i <= MESSAGE_SIZE; i++)
		{
			_delay_ms(PAUSE);
			if (morse[i] == 1){
				PORTB = PORTB ^ (1<<LED_GREEN);
				_delay_ms(LONG_DELAY);
				PORTB = PORTB & ~(1<<LED_GREEN);
			}else{
				PORTB = PORTB ^ (1<<LED_GREEN);
				_delay_ms(SHORT_DELAY);
				PORTB = PORTB & ~(1<<LED_GREEN);
			}
		}
		
    }
	return 0;
}

