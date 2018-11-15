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

uint8_t PCInt::histories[3];
uint8_t PCInt::pcint_events[3];

PCInt::PCInt() {
	memset(_enabled_interrupts, 0, 24 * sizeof(bool));
	memset(_pcint_counter, 0, 3 * sizeof(uint8_t));

	for(int i=0;i<3;i++) {
		histories[i] = 0xFF;
		pcint_events[i] = 0x00;
	}
}

PCInt::~PCInt() {
}

void PCInt::enable(uint8_t id, CALLBACK_t callback) {
	_enabled_interrupts[id] = true;
	_callbacks[id] = callback;

	uint8_t reg_id = id/8;
	if (_pcint_counter[reg_id] == 0)
		PCICR |= (1 << reg_id);

	if (id < 8) PCMSK0 |= (1 << id);
	else if (id < 16) PCMSK1 |= (1 << (id-8));
	else if (id < 24) PCMSK2 |= (1 << (id-16));
}

void PCInt::disable(uint8_t id) {
	_enabled_interrupts[id] = false;

	uint8_t reg_id = id/8;
	if (_pcint_counter[reg_id] == 0)
		PCICR &= ~(1 << reg_id);

	if (id < 8) PCMSK0 &= ~(1 << id);
	else if (id < 16) PCMSK1 &= ~(1 << (id-8));
	else if (id < 24) PCMSK2 &= ~(1 << (id-16));
}

void PCInt::check_interrupts() {
	for(int i=0;i<24;i++) {
		if ( (_enabled_interrupts[i]) and (pcint_events[i/8] & (1 << (i%8))) ) {
			(*_callbacks[i])();
			pcint_events[i/8] &= ~(1 << (i%8));
		}
	}
}

ISR(PCINT0_vect) { PCInt::interrupt_handler(0); }
ISR(PCINT1_vect) { PCInt::interrupt_handler(1); }
ISR(PCINT2_vect) { PCInt::interrupt_handler(2); }
void PCInt::interrupt_handler(uint8_t id) {
	if (id == 0){
		pcint_events[0] = PINB ^ histories[0];
		histories[0] = PINB;
	} else if (id == 1) {
		pcint_events[1] = PINJ ^ histories[1];
		histories[1] = (PINJ << 1);
	} else if (id == 2) {
		pcint_events[2] = PINK ^ histories[2];
		histories[2] = PINK;
	}
}

}

