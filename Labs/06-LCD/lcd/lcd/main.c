/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include <math.h>

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
uint8_t customChar[] = {
	0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, // 1/5
	0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, // 2/5
	0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, // 3/5
	0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, // 4/5
	0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, // 5/5
	
};

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i = 0; i < 40; i++)
	{
		// Store all new chars to memory line by line
		lcd_data(customChar[i]);
	}
	 // Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
    lcd_gotoxy(11,1);
	
	TIM0_overflow_1ms();
	TIM0_overflow_interrupt_enable();
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms


    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER0_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
	static uint8_t tens = 0;
	static uint8_t seconds = 0;
	static uint8_t t_seconds = 0;
	static uint8_t minutes = 0;
	static uint8_t t_minutes = 0;
	static uint8_t state = 0;
	static uint8_t loading = 0;	
	static uint8_t bar = 1;
	char lcd_string[2] = "";
    number_of_overflows++;
	state++;
	if (state > 24)
	{
		state = 0;
		lcd_gotoxy(bar,1);
		lcd_putc(loading);
		loading++;
		if(loading > 4)
		{
			lcd_putc(loading);
			loading = 0;
			bar++;
			if(bar > 8)
			{
				bar = 1;
				lcd_gotoxy(bar, 1);
				lcd_puts("          ");
			}
		}
	}
    if (number_of_overflows >= 100)
    {
		int power = pow(seconds + 10*t_seconds,2);
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;
		tens++;
		itoa(power, lcd_string, 10);
		lcd_gotoxy(11,0);
		lcd_puts(lcd_string);
		if(tens>9)
		{
			tens=0;
			seconds++;
			if(seconds>9)
			{
				seconds = 0;
				t_seconds++;
				if(t_seconds>5)
				{
					t_seconds = 0;
					minutes++;
					lcd_gotoxy(12,0);
					lcd_puts("   ");
					if(minutes>9)
					{
						minutes = 0;
						t_minutes++;
						if(t_minutes>5)
						{
							t_minutes = 0;
						}
					}
				}
			}
		}
		itoa(tens, lcd_string, 10);
		lcd_gotoxy(7,0);
		lcd_puts(lcd_string);
		itoa(seconds, lcd_string, 10);
		lcd_gotoxy(5,0);
		lcd_puts(lcd_string);
		itoa(t_seconds, lcd_string, 10);
		lcd_gotoxy(4,0);
		lcd_puts(lcd_string);
		itoa(minutes, lcd_string, 10);
		lcd_gotoxy(2,0);
		lcd_puts(lcd_string);
		itoa(t_minutes, lcd_string, 10);
		lcd_gotoxy(1,0);
		lcd_puts(lcd_string);	
        // WRITE YOUR CODE HERE

    }
}