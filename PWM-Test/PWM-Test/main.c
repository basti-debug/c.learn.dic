/*
 * PWM-Test.c
 *
 * Created: 24.03.2022 13:23:52
 * Author : joelr
 */ 

#define COUNT_MAX 9
#include <avr/io.h>
#include <avr/interrupt.h>
static unsigned int count =0;

ISR(TIMER0_OVF_vect){
	count++;
	if (count==COUNT_MAX)
	{
		count=0;
		OCR0 += 10;
	}
}

int main(void)
{
	DDRB |= (1<<PB3);
	TCCR0 |= (1<<CS02);					//Hardware-Vorteiler 256
	TCCR0 |= (1<<WGM00);	//Auf Fast-PWM setzen
	TCCR0 |= (1<<COM01);				//Fast-PWM auf nicht-invertiert setzen
	OCR0 = 1;							//Tastverhältniss auf 75% setzen
	TIMSK |= (1<<TOIE0);				//Interrupt bei Überlauf freigeben
	sei();								//Interrupt global freigeben
    while (1) 
    {
    }
}

