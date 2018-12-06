#include <stdio.h>
#include <avr/interrupt.h>

#include "Dialer.h"
#include "Ext_Int.h"

void cancel_handler() {
	Dialer::cancel = true;
}


int main(void) {
	cli();

	Dialer dialer = Dialer();
	//EXT_INT::Ext_Int cancel_int(EXT_INT::Ext_Int::Int4, EXT_INT::Ext_Int::FALLING, &cancel_handler);
	//cancel_int.enable();

	sei();

	while (1) {
		dialer.execute();

	}


}
