/*
 * Mircrocontrollers week 2 B3.c
 *
 * Created: 24-2-2021 13:49:06
 * Author : Pascal
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const unsigned char NUMBERS[16] =
{
	//hexidecimal
	0b00111111, // 0
	0b00000101, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100101, // 4
	0b01101110, // 5
	0b01111110, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111010, // C
	0b01011101, // d
	0b01111010, // E
	0b01110010, // F
};int number = 0;


ISR(INT0_vect)
{
	number++;
	if (PIND & 0x02)
	{
		number = 0;
	}
}

ISR(INT1_vect)
{
		number--;
		if(PIND & 0x01)
		{
			number = 0;
		}
}

void wait (int ms)
{
		for (int i=0; i<ms; i++)
		{
			_delay_ms(1);	//library function(max 30ms at 8Mhz)
		}
}


int main(void)
{
    DDRB = 0xFF;	//set all output pins to port B
	
	DDRD = 0x00;	//set all input pins to port D
	EICRA |= 0x0F;	//pin 0-1 are rising edge
	EIMSK |= 0x03;	//enable pin 0-1
	sei();
	
	PORTB = NUMBERS[0];
	
	
    while (1) 
    {
		if(number >= 0 && number <= 15)
		{
		PORTB = NUMBERS[number];
		}else{
			PORTB = NUMBERS[14];		//Sets number to E
		}
		wait(10);
    }
}

