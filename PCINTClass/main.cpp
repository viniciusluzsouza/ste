#include <avr/interrupt.h>
#include "PCInt.h"
#include "UART.h"
#include <util/delay.h>

using namespace PCINT;

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);

void int0_handler(){
	uart.put('0');
	return;
}

void int1_handler(){
	uart.put('1');
	return;
}

void int2_handler(){
	uart.put('2');
	return;
}

int main(void){

	cli();
	PCInt pcint;
	pcint.enable(PCInt::PCINT_4, &int0_handler);
	pcint.enable(PCInt::PCINT_5, &int0_handler);
	pcint.enable(PCInt::PCINT_9, &int1_handler);
	pcint.enable(PCInt::PCINT_10, &int1_handler);
	pcint.enable(PCInt::PCINT_16, &int2_handler);
	pcint.enable(PCInt::PCINT_17, &int2_handler);

	sei();
	bool active = 0;
	while(1){
		if (uart.has_data()){
			uart.get();
//			uart.put(PCICR);
//			uart.put(PCMSK1);
//			uart.put(PCMSK2);
		}

		_delay_ms(2000);
		pcint.check_interrupts();
		if (active) {
			pcint.enable(PCInt::PCINT_4, &int0_handler);
			pcint.enable(PCInt::PCINT_5, &int0_handler);
			pcint.enable(PCInt::PCINT_9, &int1_handler);
			pcint.enable(PCInt::PCINT_10, &int1_handler);
			pcint.enable(PCInt::PCINT_16, &int2_handler);
			pcint.enable(PCInt::PCINT_17, &int2_handler);
			active = 0;
		} else {
//			pcint.disable(PCInt::PCINT_4);
			pcint.disable(PCInt::PCINT_5);
//			pcint.disable(PCInt::PCINT_9);
			pcint.disable(PCInt::PCINT_10);
//			pcint.disable(PCInt::PCINT_16);
			pcint.disable(PCInt::PCINT_17);
			active = 1;
		}

	}

	return 0;

}
