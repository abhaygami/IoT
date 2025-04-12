#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char recive;

int main(void)
{	
    DDRC = 0xFF;            // Whole PORTC in output mode
	DDRB = 0xA0;            // Pin 5 and 7 PORTB in output mode
    PORTB = 0x00;           // Default output is low
    PORTC = 0x00;           // Default output is low

	UCSR0A = 0x00;          // Normal Baud rate mode
	UCSR0B = 0x98;          // Trans-Receiver Mode
	UCSR0C = 0x06;          // 8-bit data transfer
	UBRR0 = 0x67;           // 9600 baud for 16MHz

    TCCR1A = TCCR1B = TCCR1C = 0X00;    // cleaning all register values

    TCNT1 = 0x3CAF;         // Delay Time : 0.2 sec
    TCCR1A = 0x03;          // Pre-scaler : 64
    TIMSK1 = 0x01;          // Enable TIMER1


	sei();                  // Enable global interrupts
	
	while (1) 
	{
		if (recive == 'C') {
			PORTB = 0x20;      // Turn ON LED
        } else if (recive == 'E') {
        	PORTB = 0x00;
        }
	}
}

ISR(USART_RX_vect)
{
	recive = UDR0;          // Read received character
	UDR0 = recive;          // Echo it back
}
