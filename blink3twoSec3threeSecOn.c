#include <avr/io.h>
#include <avr/interrupt.h>

int i = 0x00;
int counter = 0;

int main(void)
{
    DDRB = 0x20;          
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCCR1C = 0x00;

    TCCR1B = 0x05;      // Set prescaler = 1024   
    TIMSK1 = 0x01;         // Enable Timer1 overflow interrupt
    TCNT1 = 0x85ED;        // ~2 sec delay
    sei();                 // Enable global interrupts

    while (1) {}
}

ISR(TIMER1_OVF_vect)
{
    if (counter < 3) {
        // First 3 blinks with 2 sec delay
        TCNT1 = 0x85ED;    // 2 sec delay

    } else if (counter < 5) {
        // Next 2 blinks with 3 sec delay
        TCNT1 = 0x48E4;    // 3 sec delay

    } else {
        // After 5 total blinks, turn on LED and stop further interrupts
        PORTB = 0x20;
        TIMSK1 = 0x00;     // Disable Timer1 overflow interrupt
        return;
    }

    // Toggle LED state
    if (i == 0x00) {
        PORTB = 0x20;   // LED ON
        i = 0x01;
    } else {
        PORTB = 0x00;   // LED OFF
        i = 0x00;
        counter++;      // Count full on-off blink
    }
}
