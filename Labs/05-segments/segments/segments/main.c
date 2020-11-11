/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#include "gpio.h"


uint8_t singles = 0;
uint8_t minutes = 0;
uint8_t tens_min = 0;
uint8_t decimals = 0;
uint8_t position = 0;

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();
	
    // Test of SSD: display number '3' at position 0
	
	TIM0_overflow_1ms();
	TIM0_overflow_interrupt_enable();
	
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_enable();
	
    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */

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
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter
 * value and display it on SSD.
 */
ISR(TIMER0_OVF_vect)
{
	static uint8_t position = 0;
	if (position == 0)
	{
		//SEG_update_shift_regs(singles, 0);
		SEG_update_shift_regs(singles,0,0);
		position = 1;	
	}
	else if(position == 1)
	{
		SEG_update_shift_regs(decimals,1,0);
		position = 2;
	}
	else if(position == 2)
	{
		SEG_update_shift_regs(minutes,2,1);
		position = 3;
	}
	else
	{
		SEG_update_shift_regs(tens_min,3,0);
		position = 0;
	}
}

ISR(TIMER1_OVF_vect)
{
	singles++;
	if(singles > 9)
	{
		singles = 0;
		decimals++;
		if (decimals > 5)
		{
			decimals = 0;
			minutes++;
			if(minutes > 9)
			{
				minutes = 0;
				tens_min++;
				if(tens_min > 5)
				{
					tens_min = 0;
				}
			}
		}
	}
}