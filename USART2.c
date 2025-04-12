#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

// creating volatile variables so we can change its value in ISR 
volatile char msg[20];
volatile bool msg_ready = false;
volatile int i = 0;

int main(void)
{	
	DDRB = 0x20;            
	UCSR0A = 0x00;          // Normal mode
	UCSR0B = 0x98;          // Enable RXEN0, TXEN0, RX interrupt
	UCSR0C = 0x06;          // 8-bit data
	UBRR0 = 0x67;           // 9600 baud for 16MHz
	sei();                  
	
	while (1) {
		if(msg_ready) {
			if(msg[0] == 'o' && msg[1] == 'n' && msg[2] == '\0') {
				PORTB = 0x20;
			} else {
				PORTB = 0x00;
			}
			msg_ready = false;
		}
	}
}

ISR(USART_RX_vect)
{
	char received_char = UDR0;

	if(received_char != '/') {
		msg[i] = received_char;
		i++;
	} else {
		msg[i] = '\0';
		i = 0;
		msg_ready = true;
	}
}
