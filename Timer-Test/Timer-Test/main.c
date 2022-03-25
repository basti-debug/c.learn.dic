/*
 * Timer-Test.c
 *
 * Created: 24.03.2022 13:05:27
 * Author : joelr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define COUNT_MAX 366				//Software-Vorteiler
static unsigned int count = 0;		//Zählvariable

ISR(TIMER0_OVF_vect){				//Interrupt bei Timer-Überlauf
	count++;
	if (count == COUNT_MAX)
	{
		count=0;
		PORTC = ~PORTC;
	}
}

int main(void)
{
	TCCR0 |= (1<<CS00) | (1<<CS01); //Timer auf Systemtakt/64 setzen
	TIMSK |= (1<<TOIE0);			//Timer-Überlauf-Interrupt freigeben
	DDRC = 0xFF;					//Data-Directory-Register auf Ausgang setzen
	sei();							//Interrupt global freigeben
	
    while (1) 
    {
    }
}

