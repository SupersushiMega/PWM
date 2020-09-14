#include <stdlib.h>
#include <avr/io.h>
#include <math.h>



int main(void)
{
	//Init SPI		CLK/2
	//==================================================================
	SPCR |= (1<<DDB3);
	//==================================================================
	
	DDRB |= (1 << DDB3);	//Set PB3 as Output
	OCR2 = 0; 	//Duty cycle PB3
	TCCR2 |= (1 << COM21) | (1<<COM20);	//Set mode to inverting
	TCCR2 |= (1 << WGM21) | (1 << WGM20);	//Set fast mode
	TCCR2 |= (1 << CS21);	//Set prescaler to 8 and start PWM
	
	DDRB |= (1 << DDB2);	//Set PB2
	DDRB |= (1 << DDB1);	//Set PB1
	OCR1A = 0; 	//Duty cycle PB2
	OCR1B = 0; 	//Duty cycle PB1
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);	//Set mode to none-inverting
	TCCR1A |= (1 << WGM12) | (1 << WGM10);	//Set fast mode
	TCCR1B |= (1 << CS11);	//Set prescaler to 8 and start PWM
	
	DDRB |= (1 << DDB2);	//Set PB2 as Output
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);	//Set mode to none-inverting
	TCCR1A |= (1 << WGM12) | (1 << WGM10);	//Set fast mode
	TCCR1B |= (1 << CS11);	//Set prescaler to 8 and start PWM
	
	double red = 0;
	double green = 0;
	double blue = 0;
	uint16_t angle = 0;
	uint8_t frame;
	while(1)
	{ 
		frame++;
		if (frame == 0)
		{
			angle++;
			if (angle >= 360)
			{
				angle = 0;
			}
			red = (1 + sin((angle * (M_PI / 180)))) / 2;
			blue = (1 + cos((angle * (M_PI / 180)))) / 2;
			green = 1 - blue;
			OCR2 = 255 - (blue * 255);
			OCR1B = red * 255;
			OCR1A = green * 255;
		}
		
	} //end while
}//end of main




