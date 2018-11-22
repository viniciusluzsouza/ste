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
#include <string.h>
#include <stdlib.h>

namespace PCINT {

uint8_t PCInt::histories[3];
uint8_t PCInt::pcint_events[3];

PCInt::PCInt() {
	memset(pcint_events, 0, 3 * sizeof(uint8_t));

	histories[0] = PINB;
	histories[1] = ((PINJ << 1)|(1 << 0)) & (0xFE | PINE);
	histories[2] = PINK;
}

PCInt::~PCInt() {
}

void PCInt::enable(uint8_t id, CALLBACK_t callback) {
	_callbacks[id] = callback;

	if (id < 8) {
		if ( !(PCMSK0) )
			PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << id);
	} else if (id < 16) {
		if ( !(PCMSK1) )
			PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << (id-8));
	}
	else if (id < 24) {
		if ( !(PCMSK2) )
			PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << (id-16));
	}
}

void PCInt::disable(uint8_t id) {
	if (id < 8) {
		PCMSK0 &= ~(1 << id);
		if ( !(PCMSK0) )
			PCICR &= ~(1 << PCIE0);
	} else if (id < 16) {
		PCMSK1 &= ~(1 << (id-8));
		if ( !(PCMSK1) )
			PCICR &= ~(1 << PCIE1);
	}
	else if (id < 24) {
		PCMSK2 &= ~(1 << (id-16));
		if ( !(PCMSK2) )
			PCICR &= ~(1 << PCIE2);
	}
}

void PCInt::check_interrupts() {
	div_t res;
	for(int i=0;i<24;i++) {
		res = div(i, 8);
		if (pcint_events[res.quot] & (1 << (res.rem)) ) {
			pcint_events[res.quot] &= ~(1 << (res.rem));
			(*_callbacks[i])();
		}
	}
}

ISR(PCINT0_vect) { PCInt::interrupt_handler(0); }
ISR(PCINT1_vect) { PCInt::interrupt_handler(1); }
ISR(PCINT2_vect) { PCInt::interrupt_handler(2); }
void PCInt::interrupt_handler(uint8_t id) {
	uint8_t temp;
	if (id == 0){
		temp = PINB;
		pcint_events[0] |= (temp ^ histories[0]) & PCMSK0;
		histories[0] = temp;
	} else if (id == 1) {
		temp = ((PINJ << 1)|(1 << 0)) & (0xFE | PINE);
		pcint_events[1] |= (temp ^ histories[1]) & PCMSK1;
		histories[1] = temp;
	} else if (id == 2) {
		temp = PINK;
		pcint_events[2] |= (PINK ^ histories[2]) & PCMSK2;
		histories[2] = temp;
	}
}

}

