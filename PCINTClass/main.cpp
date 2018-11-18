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

int main(void){

	cli();
	PCInt pcint;
	pcint.enable(PCInt::PCINT_4, &int0_handler);
	pcint.enable(PCInt::PCINT_9, &int1_handler);
	pcint.enable(PCInt::PCINT_10, &int1_handler);
	pcint.enable(PCInt::PCINT_16, &int2_handler);

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
