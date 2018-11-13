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

int main(void){

	PCInt pcint;
	pcint.enable(PCInt::PCINT_4, &int0_handler);

	sei();
	while(1){
		uart.put((PCIFR));
		if (uart.has_data()){
			uart.put(uart.get());
		}

		_delay_ms(1000);
		pcint.check_interrupts();
	}

	return 0;

}
