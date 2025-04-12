//when timer0 is enabled sum and sub calculated and timer1 is enabled then mul and div calculated

#include <REG51.H>

int a = 5 , b = 10 , sum = 0 , sub = 0 , mul = 0 , div = 0;

main() {
	IE = 0x8b; // EA,ET1,ET0 enabled
	TCON = 0x50; // TR0,TR1 enabled
	TMOD = 0x11;
	
	while(1) {
		
		P0 = 0x00;	// Port0 Low (It is normally used for flag)
	}
}

void Timer0_ISR(void) interrupt 1 using 1 {
	sum = a+b;
	sub = b-a;
	P0 = 0xff; // Port0 high (It shows ISR performed)
}

void Timer1_ISR(void) interrupt 3 using 2 {
	mul = a*b;
	div = b/a;
	P0 = 0xff; // Port0 high (It shows ISR performed)
}