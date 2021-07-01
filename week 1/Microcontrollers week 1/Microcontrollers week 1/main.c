/*
 * Microcontrollers week 1.c
 *
 * Created: 3-2-2021 13:39:14
 * Author : Pascal de Bruijn
 */ 
#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

void blinkingstrip(void);
void blinkingseperate(void);
void OnClickButton(void);
void WalkingLight(void);
void LedPatterns(void);
void displaySequence(short arr[], int arraySize);
void frequencyState(void);

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
		//blinkingstrip();
		//blinkingseperate();
		//OnClickButton();
		//WalkingLight();
		LedPatterns();
		//frequencyState()
}

void blinkingstrip()
{
	DDRD = 0b11111111;	//ALL pins PORTD are set to output
	
	while (1)
	{
		PORTD = 0xAA;
		wait( 250 );
		PORTD = 0x55;
		wait( 250 );
	}
}

void blinkingseperate()
{
		
	DDRD = 0b11111111;
	
	while (1)
	{
		PORTD = 0x80;
		wait( 500 );
		PORTD = 0x40;
		wait( 500 );
	}
}

void OnClickButton()
{
	DDRD = 0b11111111;	//ALL pins PORTD are set to output
	
	while (1)
	{
		while (PINC & 0x01)
		{
			PORTD = 0x80;
			wait( 250 );
			PORTD = 0x00;
			wait( 250 );
		}
	}
}

void WalkingLight()
{
	DDRD = 0b11111111;
	int i = 0;
	
	while (1)
	{
		PORTD = 1 << i%8;
		i++;
		wait(50);
	}
}

void LedPatterns(void)
{
	short toCenterFromCenter[7] = {0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81};
	short ledsWalking[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	DDRD = 0b11111111;	//ALL pins PORTD are set to output

	while(1)
	{
		displaySequence(toCenterFromCenter, 7);
		displaySequence(ledsWalking, 8);

	}
}

void displaySequence(short arr[], int arraySize)
{
	for(int i = 0; i < arraySize; i++)
	{
		PORTD = arr[i];
		wait( 200 );
	}
}

void frequencyState()
{
	DDRD = 0b11111111;
	int interval = 1000;
	int elapsedTime = 0;
	int ledOn = 0;
	
	while (1)
	{
		if (elapsedTime - interval >= 0)	//checks if elapsed time reached interval
		{
				if (ledOn == 0)
				{
					PORTD = 0x80;
					ledOn = 1;
				}else{
				PORTD = 0x00;
				ledOn =0
				}
				elapsedTime -= interval; //reset elapsedTime
		}
		
		if ((PINC & 0x01) && (interval == 250))		//checks for button presses and change in interval
		{
			interval = 1000;
		}else if(PINC & 0x01 & interval == 1000){
			interval = 250;
		}
		wait(1);
		elapsedTime++;
	}
}