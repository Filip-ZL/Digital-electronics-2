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

uint16_t delta_time = 0;
float distance = 0;
uint16_t velocity = 340;

int main(void)
{
	deltatime_init();
	lcd_init(LCD_DISP_ON);
	lcd_gotoxy(0,0);
	lcd_puts("Distance:");
	lcd_gotoxy(10,0);
	lcd_puts(">4");
	lcd_gotoxy(12,0);
	lcd_putc('m');
		
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
	static uint8_t counter = 0;
	char lcd_string[10] = "";
	counter++;
	
	if (counter > 60)
	{
		delta_time = count_deltatime();
		distance = round((velocity*(delta_time/(float)10000))/(float)2);
		counter = 0;
		lcd_gotoxy(10,0);
		lcd_puts("   ");
		itoa(distance, lcd_string, 10);
		lcd_gotoxy(10,0);
		lcd_puts(lcd_string);
		lcd_gotoxy(12,0);

	}
}

