/*
 * project.c
 *
 * Created: 25.11.2020 15:18:40
 * Author : ffili
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>

#include "timer.h"
#include "lcd.h"
#include "lcd_definitions.h"
#include <string.h>
#include <math.h>

// global variables 
uint16_t delta_time = 0;
float distance = 0;
uint16_t velocity = 340;

int main(void)
{
	// initialization of display and deltatime ports
	deltatime_init();
	lcd_init(LCD_DISP_ON);
	// Default text displayed on LCD
	lcd_gotoxy(0,0);
	lcd_puts("Distance:");
	lcd_gotoxy(10,0);
	lcd_puts(">4");
	lcd_gotoxy(12,0);
	lcd_putc('m');
	
	// TIMER 2 enabled
	TIM2_overflow_1ms();
	TIM2_overflow_interrupt_enable();
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
	return 0;
}

ISR(TIMER2_OVF_vect)
{
	// variables used in interruption
	static uint8_t counter = 0;
	char lcd_string[10] = "";
	counter++;
	
	// cycle repeat once for 60 cycles
	if (counter > 60)
	{
		//count_deltatime function counts width of echo pulse
		delta_time = count_deltatime();
		distance = round((velocity*(delta_time/(float)10000))/(float)2);
		counter = 0;
		// sensor accurency is guaranted from 4cm to 4m - this condition is up limitation
		if(distance > 400)
		{
			lcd_gotoxy(10,0);
			lcd_puts("     ");
			lcd_gotoxy(10,0);
			lcd_puts(">4m");
			lcd_gotoxy(12,0);
		}
		// down limitation
		else if (distance <= 2)
		{
			lcd_gotoxy(10,0);
			lcd_puts("   ");
			itoa(0, lcd_string, 10);
			lcd_gotoxy(10,0);
			lcd_puts(lcd_string);
		}
		else
		{
			lcd_gotoxy(10,0);
			lcd_puts("   ");
			itoa(distance, lcd_string, 10);
			lcd_gotoxy(10,0);
			lcd_puts(lcd_string);
			lcd_gotoxy(13,0);
			lcd_puts("cm");
		}


	}
}

