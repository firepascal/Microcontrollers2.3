#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void lcd_write_data(unsigned char byte);
void lcd_command(unsigned char dat);
void lcd_write_cmd(unsigned char byte);

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

/* Initlializes the LCD */
void lcd_init(void)
{
	// Set ALL pins on PORTC to output
	DDRC = 0xFF;
	// return home (cursor to top left)
	lcd_command( 0x02 );
	// mode: 4 bits interface data, 2 lines, 5x8 dots
	lcd_command( 0x28 );
	// display: on, cursor off, blinking off
	lcd_command( 0x0C );
	// entry mode: cursor to right, no shift
	lcd_command( 0x06 );
	// RAM adress: 0, first position, line 1
	lcd_command( 0x80 );
}

/* Write a string of text to the LCD */
void lcd_display_text(char *str)
{
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

/* Write a single character to the LCD */
void lcd_write_data(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/* Write commands to the LCD */
void lcd_command ( unsigned char dat )
{
	PORTC = dat & 0xF0;			// hoge nibble
	PORTC = PORTC | 0x08;		// data (RS=0),
	
	// start (EN=1)
	_delay_ms(1);				// wait 1 ms
	PORTC = 0x04;				// stop (EN = 0)
	PORTC = (dat & 0x0F) << 4;	// lage nibble
	PORTC = PORTC | 0x08;		// data (RS=0),
	
	// start (EN=1)
	_delay_ms(1);				// wait 1 ms
	PORTC = 0x00;				// stop
	// (EN=0 RS=0)
}
void lcd_set_cursor(int position)
{
	lcd_command(0x80 | position);
}