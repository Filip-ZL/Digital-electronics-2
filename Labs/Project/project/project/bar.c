/*
 * bar.c
 *
 * Created: 02.12.2020 15:36:38
 *  Author: ffili
 */
#define F_CPU 16000000

#include <util/delay.h>
#include <math.h>

#include "bar_driver.h"
#include "gpio.h"

uint8_t led_state[] = {
	0b11111111,		// 0/8
	0b01111111,		// 1/8
	0b00111111,		// 2/8
	0b00011111,		// 3/8
	0b00001111,		// 4/8
	0b00000111,		// 5/8
	0b00000011,		// 6/8
	0b00000001,		// 7/8
	0b00000000,		// 8/8	
};

uint8_t BAR_position[] = {
	0b10000000, // Position 0
	0b01000000, // Position 1
};

 
void BAR_init(void)
{
	GPIO_config_output(&DDRC, SEGMENT_LATCH);
	GPIO_config_output(&DDRC, SEGMENT_CLK);
	GPIO_config_output(&DDRB, SEGMENT_DATA);
}

void BAR_update_shift_regs(uint16_t maxVal, uint16_t currentVal, uint8_t position)
{
	uint8_t bar_value;
	uint8_t bit_number;
	uint8_t percentVal;
	position = BAR_position[position];
	percentVal = round((currentVal/(float)maxVal)*100);
	if(percentVal > 100)
	{
		bar_value = led_state[0];
	}
	else if(percentVal > 88 & percentVal <= 100)
	{
		bar_value = led_state[1];
	}
	else if(percentVal > 76 & percentVal <= 88)
	{
		bar_value = led_state[2];
	}
	else if(percentVal > 64 & percentVal <= 76)
	{
		bar_value = led_state[3];
	}
	else if(percentVal > 52 & percentVal <= 64)
	{
		bar_value = led_state[4];
	}
	else if(percentVal > 40 & percentVal <= 52)
	{
		bar_value = led_state[5];
	}
	else if(percentVal > 28 & percentVal <= 40)
	{
		bar_value = led_state[6];
	}
	else if(percentVal > 16 & percentVal <= 28)
	{
		bar_value = led_state[7];
	}
	else if(percentVal <= 16)
	{
		bar_value = led_state[8];
	}
	
	GPIO_write_low(&PORTC, SEGMENT_LATCH);
	GPIO_write_low(&PORTC, SEGMENT_CLK);
	GPIO_write_low(&PORTB, SEGMENT_DATA);
	
	_delay_us(1);
	
	for(bit_number = 0; bit_number < 8; bit_number++)
	{
		if((bar_value & 1) == 0)
		{
			GPIO_write_low(&PORTB, SEGMENT_DATA);	
		}
		else
		{
			GPIO_write_high(&PORTB, SEGMENT_DATA);
		}
		_delay_us(1);
		
		GPIO_write_high(&PORTC, SEGMENT_CLK);
		
		_delay_us(1);
		
		GPIO_write_low(&PORTC, SEGMENT_CLK);
		
		bar_value = bar_value >> 1;
	}
	for (bit_number = 0; bit_number < 8; bit_number++)
	{
		// Output DATA value (bit 0 of "position")
		if ((position & 1) == 0)
		{
			GPIO_write_low(&PORTB, SEGMENT_DATA);
		}
		else
		{
			GPIO_write_high(&PORTB, SEGMENT_DATA);
		}
		// Wait 1 us
		_delay_us(1);
		// Pull CLK high
		GPIO_write_high(&PORTC, SEGMENT_CLK);
		// Wait 1 us
		_delay_us(1);
		// Pull CLK low
		GPIO_write_low(&PORTC, SEGMENT_CLK);
		    
		// Shift "position"
		position = position >> 1;
	}

	// Pull LATCH high
	GPIO_write_high(&PORTC, SEGMENT_LATCH);
	// Wait 1 us
	_delay_us(1);
		
}