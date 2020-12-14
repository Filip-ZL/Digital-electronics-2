/*
 * project.c
 *
 * Created: 25.11.2020 15:18:40
 * Author : ffili
 */ 
#define front_view	0
#define back_view	1
#define trigger_back PB2
#define trigger_front PB3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>


#include "timer.h"
#include "lcd.h"
#include "lcd_definitions.h"
#include "gpio.h"
#include "delta_time.h"
#include "bar_driver.h"

// global variables 
uint16_t delta_time1 = 0;
uint16_t delta_time2 = 0;
float front_distance = 0;
float back_distance = 0;
uint16_t velocity = 340;

int main(void)
{
	// initialization of display and deltatime ports
	deltatime_init();
	GPIO_config_output(&DDRB, trigger_front);
	GPIO_config_output(&DDRB, trigger_back);
	GPIO_config_output(&DDRB, PB7);
	BAR_init();
	lcd_init(LCD_DISP_ON);
	// Default text displayed on LCD
	lcd_gotoxy(0,0);
	lcd_puts("Front:");
	lcd_gotoxy(10,0);
	lcd_puts(">4");
	lcd_gotoxy(12,0);
	lcd_putc('m');
	
	lcd_gotoxy(0,1);
	lcd_puts("Back:");
	lcd_gotoxy(10,1);
	lcd_puts(">4");
	lcd_gotoxy(12,1);
	lcd_putc('m');
	
	// TIMER 2 enabled
	TIM1_overflow_4ms();
	TIM1_overflow_interrupt_enable();
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
	return 0;
}

ISR(TIMER1_OVF_vect)
{

	 //variables used in interruption
	static uint8_t counter = 0;
	static uint8_t k = 0;
	char lcd_string[] = "";
	counter++;
	// cycle repeat once for 60 cycles
	if (counter > 10)
	{
		if(k == 0)
		{
			GPIO_write_high(&PORTB, PB7);
			delta_time1 = count_deltatime(&PORTB, trigger_front);
			front_distance = round((velocity*(delta_time1/(float)10000))/(float)2);
			BAR_update_shift_regs(200, front_distance, front_view);
			k = 1;
		}
		else
		{
			GPIO_write_low(&PORTB, PB7);
			delta_time2 = count_deltatime(&PORTB, trigger_back);
			back_distance = round((velocity*(delta_time2/(float)10000))/(float)2);
			BAR_update_shift_regs(200, back_distance, back_view);
			k = 0;
		}
		// count_deltatime function counts width of echo pulse

		counter = 0;
		// sensor accurency is guaranted from 4cm to 4m - this condition is up limitation
		if(back_distance > 400)
		{
			lcd_gotoxy(10,0);
			lcd_puts("      ");
			lcd_gotoxy(10,0);
			lcd_puts(">4m");
		}
		
		else if (back_distance <= 2)
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
			itoa(back_distance, lcd_string, 10);
			lcd_gotoxy(10,0);
			lcd_puts(lcd_string);
			lcd_gotoxy(13,0);
			lcd_puts("cm");
		}
		
		if(front_distance > 400)
		{
			lcd_gotoxy(10,1);
			lcd_puts("      ");
			lcd_gotoxy(10,1);
			lcd_puts(">4m");
		}
		
		else if (front_distance <= 2)
		{
			lcd_gotoxy(10,1);
			lcd_puts("   ");
			itoa(0, lcd_string, 10);
			lcd_gotoxy(10,1);
			lcd_puts(lcd_string);
		}
		else
		{
			lcd_gotoxy(10,1);
			lcd_puts("   ");
			itoa(front_distance, lcd_string, 10);
			lcd_gotoxy(10,1);
			lcd_puts(lcd_string);
			lcd_gotoxy(13,1);
			lcd_puts("cm");
		}
		
	}
	
}

