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

	PCInt pcint;
	pcint.enable(PCInt::PCINT_0, &int0_handler);
	pcint.enable(PCInt::PCINT_1, &int0_handler);
	pcint.enable(PCInt::PCINT_2, &int0_handler);
	pcint.enable(PCInt::PCINT_3, &int0_handler);
	pcint.enable(PCInt::PCINT_4, &int0_handler);
	pcint.enable(PCInt::PCINT_5, &int0_handler);
	pcint.enable(PCInt::PCINT_6, &int0_handler);
	pcint.enable(PCInt::PCINT_7, &int0_handler);
	pcint.enable(PCInt::PCINT_8, &int1_handler);
	pcint.enable(PCInt::PCINT_9, &int1_handler);
	pcint.enable(PCInt::PCINT_10, &int1_handler);
	pcint.enable(PCInt::PCINT_11, &int1_handler);
	pcint.enable(PCInt::PCINT_12, &int1_handler);
	pcint.enable(PCInt::PCINT_13, &int1_handler);
	pcint.enable(PCInt::PCINT_14, &int1_handler);
	pcint.enable(PCInt::PCINT_15, &int1_handler);
	pcint.enable(PCInt::PCINT_16, &int2_handler);
	pcint.enable(PCInt::PCINT_17, &int2_handler);
	pcint.enable(PCInt::PCINT_18, &int2_handler);
	pcint.enable(PCInt::PCINT_19, &int2_handler);
	pcint.enable(PCInt::PCINT_20, &int2_handler);
	pcint.enable(PCInt::PCINT_21, &int2_handler);
	pcint.enable(PCInt::PCINT_22, &int2_handler);
	pcint.enable(PCInt::PCINT_23, &int2_handler);



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
