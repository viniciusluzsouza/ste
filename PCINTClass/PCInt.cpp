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

namespace PCINT {

PCInt::PCInt() {
	memset(_event, 0, 24 * sizeof(bool));
	memset(_enabled_interrupts, 0, 24 * sizeof(bool));
	memset(_pcint_counter, 0, 3 * sizeof(uint8_t));
}

PCInt::~PCInt() {
}

void PCInt::enable(uint8_t id, CALLBACK_t callback) {
	_enabled_interrupts[id] = true;

	uint8_t reg_id = id/8;
	if (_pcint_counter[reg_id] == 0)
		PCICR |= (1 << reg_id);
}

void PCInt::disable(uint8_t id) {
	_enabled_interrupts[id] = false;

	uint8_t reg_id = id/8;
	if (_pcint_counter[reg_id] == 0)
		PCICR &= ~(1 << reg_id);
}

void PCInt::check_interrupts() {
	for(int i=0;i<24;i++) {
		if (_enabled_interrupts[i] and _event[i]) {
			(*_callbacks[i])();
			_event[i] = false;
		}
	}
}

ISR(PCINT0_vect) {
	for(int i=0;i<8;i++) {
		if (PCMSK0 & (1 << i)) {
			PCInt::vect_handler(i);
			PCMSK0 &= ~(i << i);
		}
	}
}

ISR(PCINT1_vect) {
	for(int i=8;i<16;i++) {
		if (PCMSK1 & (1 << (i-8))) {
			PCInt::vect_handler(i);
			PCMSK1 &= ~(i << (i-8));
		}
	}
}

ISR(PCINT2_vect) {
	for(int i=16;i<24;i++) {
		if (PCMSK2 & (1 << (i-16))) {
			PCInt::vect_handler(i);
			PCMSK2 &= ~(i << (i-16));
		}
	}
}

}
