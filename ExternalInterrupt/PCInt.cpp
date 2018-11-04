/*
 * PCInt.cpp
 *
 *  Created on: 3 de nov de 2018
 *      Author: vini
 */

#include "PCInt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

namespace PCINT {

pcint_CALLBACK_t  PCInt::_pcint_callback[8];

PCInt::PCInt(uint8_t id, pcint_CALLBACK_t pcint_callback) {
	_id = id;
	_pcint_callback[_id] = pcint_callback;

	PCICR |= (1 << (_id/8));
}

PCInt::~PCInt() {
	// TODO Auto-generated destructor stub
}

void PCInt::enable() {
	if (_id < PCINT_8) {
		PCMSK0 |= (1 << _id);
	} else if (_id < PCINT_16) {
		PCMSK1 |= (1 << (_id-8));
	} else if (_id < PCINT_23) {
		PCMSK1 |= (1 << (_id-16));
	}
}

void PCInt::disable() {
	if (_id < PCINT_8) {
		PCMSK0 &= ~(1 << _id);
	} else if (_id < PCINT_16) {
		PCMSK1 &= ~(1 << (_id-8));
	} else if (_id < PCINT_23) {
		PCMSK1 &= ~(1 << (_id-16));
	}
}

void PCInt::callback(){
	(*_pcint_callback)();
}

ISR(PCINT0_vect) {
	PCInt::vect_handler(0);
}

ISR(PCINT1_vect) {
	PCInt::vect_handler(1);
}

ISR(PCINT2_vect) {
	PCInt::vect_handler(2);
}

// Ver com professor, é isso mesmo??
ISR(WDT_vect) {
	PCInt::vect_handler(3);
}

ISR(TIMER2_COMPA_vect) {
	PCInt::vect_handler(4);
}

ISR(TIMER2_COMPB_vect) {
	PCInt::vect_handler(5);
}

ISR(TIMER2_OVF_vect) {
	PCInt::vect_handler(6);
}

ISR(TIMER1_CAPT_vect) {
	PCInt::vect_handler(7);
}

ISR(TIMER1_COMPA_vect) {
	PCInt::vect_handler(8);
}

ISR(TIMER1_COMPB_vect) {
	PCInt::vect_handler(9);
}

ISR(TIMER1_COMPC_vect) {
	PCInt::vect_handler(10);
}

ISR(TIMER1_OVF_vect) {
	PCInt::vect_handler(11);
}

ISR(TIMER0_COMPA_vect) {
	PCInt::vect_handler(12);
}

ISR(TIMER0_COMPB_vect) {
	PCInt::vect_handler(13);
}

ISR(TIMER0_OVF_vect) {
	PCInt::vect_handler(14);
}

ISR(SPI_STC_vect) {
	PCInt::vect_handler(15);
}

ISR(USART0_RX_vect) {
	PCInt::vect_handler(16);
}

ISR(USART0_UDRE_vect) {
	PCInt::vect_handler(17);
}

ISR(USART0_TX_vect) {
	PCInt::vect_handler(18);
}

ISR(ANALOG_COMP_vect) {
	PCInt::vect_handler(19);
}

ISR(ADC_vect) {
	PCInt::vect_handler(20);
}

ISR(EE_READY_vect) {
	PCInt::vect_handler(21);
}

ISR(TIMER3_CAPT_vect) {
	PCInt::vect_handler(22);
}

ISR(TIMER3_COMPA_vect) {
	PCInt::vect_handler(23);
}

}

} /* namespace PCINT */
