//when INT0 enabled factorial of 6 should be find
#include <REG51.H> 
int fact;
int i;

main() {
	IE = 0x81; //EA,EX0 enabled
	TCON = 0x01; //IT0 enabled
	
	while(1) {
		P0 = 0x00;
	}
}

void interrupt0_ISR(void) interrupt 0 using 3 {
	fact = 1;
	
	for(i = 6;i > 0 ; i--) {
		fact *= i;
	}
}