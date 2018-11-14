#include <avr/interrupt.h>
#include "PCInt.h"
#include "UART.h"
#include <util/delay.h>

using namespace PCINT;

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);

void int0_handler(void){
	uart.put('1');
	return;
}

void int23_handler(void){
	uart.put('2');
	return;
}

int main(void){

	PCInt pcint;
	pcint.enable(PCInt::PCINT_0, &int0_handler);
	pcint.enable(PCInt::PCINT_23, &int23_handler);

	sei();
	while(1){
		if (uart.has_data()){
			uart.put(uart.get());
			uart.put((PCICR));
			uart.put((PCMSK0));
		}

		_delay_ms(1000);
		pcint.check_interrupts();
	}

	return 0;

}
