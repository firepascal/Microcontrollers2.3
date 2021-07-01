#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

#define CompareValue 1;

void timer2Init(void);

int amountOfTimesPressed;

// Interrupt routine timer2 overflow
ISR( TIMER2_COMP_vect )
{
	amountOfTimesPressed++; // Increment counter
}

// Main program: Counting on T2
int main( void )
{
	DDRD &= ~(1<<7); // set PORTD.7 for input
	DDRA = 0xFF; // set PORTB for output (shows tenth value)
	timer2Init();
	lcd_init();
	
	while (1)
	{
		char buffer[10];
		lcd_set_cursor(0x0);
		lcd_display_text(itoa(amountOfTimesPressed, buffer, 10));	//Convert counter to string and send it to
		_delay_ms(10);					// every 10 ms
	}
}

// Initialize timer2
//
void timer2Init( void )
{
	OCR2 = CompareValue; // Compare value of counter 2
	TIMSK |= 1<<7;		// T2 compare match interrupt enable
	TCCR2 = 0b00011111; // Initialize T2: ext.counting, rising edge
	// compare output mode, CTC, RUN
	sei();				// turn_on intr all
}

