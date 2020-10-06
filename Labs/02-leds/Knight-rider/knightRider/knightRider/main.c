/*
 * knightRider.c
 *
 * Created: 06.10.2020 18:47:03
 * Author : ffili
 */ 
#define LED_0	PB0
#define LED_1	PB1
#define LED_2	PB2
#define LED_3	PB3
#define LED_4	PB4
#define BTN		PD0
#define BLINK_DELAY 250
#ifndef F_CPU
#define F_CPU 16000000
#endif	

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Set DDRB pins as output for led's
	// Set output to low
	DDRB |= (1<<LED_0);
	PORTB &= ~(1<<LED_0);
	DDRB |= (1<<LED_1);
	PORTB &= ~(1<<LED_1);
	DDRB |= (1<<LED_2);
	PORTB &= ~(1<<LED_2);
	DDRB |= (1<<LED_3);
	PORTB &= ~(1<<LED_3);
	DDRB |= (1<<LED_4);
	PORTB &= ~(1<<LED_4);
	//button	
	DDRD = DDRD & ~(1<<BTN);
	PORTD = PORTD | (1<<BTN);
	int state;
	int Pressed = 0;
	int Pressed_Confidence_Level = 0;
	int Released_Confidence_Level = 0;
    /* Replace with your application code */
    while (1) 
    {
		if (bit_is_clear(PINB, BTN))
		{
			Pressed_Confidence_Level ++;
			Released_Confidence_Level = 0;
			if (Pressed_Confidence_Level >500)
			{
				if (Pressed == 0)
				{
				// one way
				_delay_ms(BLINK_DELAY);
				PORTB ^= (1<<LED_0);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_0);
				PORTB ^= (1<<LED_1);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_1);
				PORTB ^= (1<<LED_2);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_2);
				PORTB ^= (1<<LED_3);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_3);
				PORTB ^= (1<<LED_4);
				// other way
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_4);
				PORTB ^= (1<<LED_3);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_3);
				PORTB ^= (1<<LED_2);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_2);
				PORTB ^= (1<<LED_1);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_1);
				PORTB ^= (1<<LED_0);
				_delay_ms(BLINK_DELAY);
				PORTB &= ~(1<<LED_0);
					Pressed = 1;
				}
				Pressed_Confidence_Level = 0;
			}
		}
		else
		{
			Released_Confidence_Level ++;
			Pressed_Confidence_Level = 0;
			if (Released_Confidence_Level >500)
			{
				//Pressed = 1;
				Released_Confidence_Level = 0;
			}
		}
		loop_until_bit_is_clear(PIND, Pressed);
		
    }
	return 0;
}

