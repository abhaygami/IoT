#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char recive = 0;

int main(void)
{	
	DDRB = 0x20;            // Set PB5 as output (LED)
	UCSR0A = 0x00;          // Normal mode
	UCSR0B = 0x98;          // Enable RXEN0, TXEN0, RX interrupt
	UCSR0C = 0x06;          // 8-bit data
	UBRR0 = 0x67;           // 9600 baud for 16MHz
	sei();                  // Enable global interrupts
	
	while (1) 
	{
		if (recive == 'A') {
			PORTB = 0x20;      // Turn ON LED
			_delay_ms(2000);   // Wait 2 seconds
			PORTB = 0x00;      // Turn OFF LED
            _delay_ms(2000);   //2 sec delay
        } else if (recive == 'B') {
			PORTB = 0x20;      // Turn ON LED
			_delay_ms(1000);   // Wait 1 seconds
			PORTB = 0x00;      // Turn OFF LED
            _delay_ms(1000);   //1 sec delay {
        	PORTB = 0x00;
        }
	}
}

ISR(USART_RX_vect)
{
	recive = UDR0;          // Read received character
	UDR0 = recive;          // Echo it back
}
