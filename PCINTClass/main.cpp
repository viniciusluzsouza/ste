#include <avr/interrupt.h>
#include "PCInt.h"
#include "UART.h"
#include <util/delay.h>

using namespace PCINT;

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);

void int0_handler(uint8_t x){
	uart.put('0');
	return;
}

void int1_handler(uint8_t x){
	uart.put('1');
	return;
}

void int2_handler(uint8_t x){
	uart.put('2');
	return;
}

int main(void){

	cli();
	PCInt pcint;
	pcint.enable(PCInt::PCINT_4, &int0_handler);
	pcint.enable(PCInt::PCINT_5, &int0_handler);
	pcint.enable(PCInt::PCINT_10, &int1_handler);
	pcint.enable(PCInt::PCINT_16, &int2_handler);

	sei();
	while(1){
		if (uart.has_data()){
			uart.get();
			uart.put(PCMSK0);
			uart.put(PCMSK1);
			uart.put(PCMSK2);
		}

		//_delay_ms(1000);
		pcint.check_interrupts();
	}

	return 0;

}
