/*
 * week 2 B5.c
 *
 * Created: 3-3-2021 14:08:00
 * Author : Pascal
 */ 

#define F_CPU 8e6

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void);

int main( void )
{
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	lcd_init();

	// Write sample string
	lcd_display_text("Hello world");
	lcd_set_cursor(0x41);
	lcd_display_text("Bury the light");

	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}

