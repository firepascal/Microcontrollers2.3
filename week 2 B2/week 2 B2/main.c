/*
 * week 2 B2.c
 *
 * Created: 10-2-2021 13:53:25
 * Author : Pascal
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t counter = 0;

#define MAXCOUNTER 5

ISR0(INT0_vect)
{
	counter++;
	if (counter > MAXCOUNTER)
	{
			counter = 0;
			PORTD = 0x02;
	}
}

ISR1(INT1_vect)
{
	counter++;
	if (counter > MAXCOUNTER)
	{
		counter = 0;
		PORTD = 0x04;
	}
}

ISR2(INT2_vect)
{
	counter++;
	if (counter > MAXCOUNTER)
	{
		counter = 0;
		PORTD = 0x08;
	}
}

ISR3(INT3_vect)
{
	counter++;
	if (counter > MAXCOUNTER)
	{
		counter = 0;
		PORTD = 0x01;
	}
}

int main(void)
{
	DDRD = 0x0F;	//Set 4-7 to input, set 0-3 to output 
	
	EICRA |= 0xFF;	//pin 0-3 are rising edge
	EIMSK |= 0x0F;	//Enable pin0-3
	
	sei();
	PORTD = 0x01;
	
	
    while (1) 
    {
    }
}