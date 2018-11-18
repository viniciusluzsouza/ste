#include <avr/interrupt.h>
#include "PCInt.h"
#include "UART.h"
#include <util/delay.h>

using namespace PCINT;

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);

void int0_handler(void){
	uart.put('0');
	return;
}

void int1_handler(void){
	uart.put('1');
	return;
}

void int2_handler(void){
	uart.put('2');
	return;
}

void int3_handler(void){
	uart.put('3');
	return;
}

void int4_handler(void){
	uart.put('4');
	return;
}

void int5_handler(void){
	uart.put('5');
	return;
}

void int6_handler(void){
	uart.put('6');
	return;
}

void int7_handler(void){
	uart.put('7');
	return;
}

int main(void){

	cli();
	PCInt pcint;
	pcint.enable(PCInt::PCINT_0, &int0_handler);
	pcint.enable(PCInt::PCINT_1, &int1_handler);
	pcint.enable(PCInt::PCINT_2, &int2_handler);
	pcint.enable(PCInt::PCINT_3, &int3_handler);
	pcint.enable(PCInt::PCINT_4, &int4_handler);
	pcint.enable(PCInt::PCINT_5, &int5_handler);
	pcint.enable(PCInt::PCINT_6, &int6_handler);
	pcint.enable(PCInt::PCINT_7, &int7_handler);

	sei();
	while(1){
		if (uart.has_data()){
			uart.get();
		}

		_delay_ms(1000);
		pcint.check_interrupts();
	}

	return 0;

}
