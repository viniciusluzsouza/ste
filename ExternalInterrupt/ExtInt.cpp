/*
 * ExtInt.cpp
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#include "ExtInt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

namespace EXT_INT {

CALLBACK_t  ExtInt::_pcallback[8];

ExtInt::ExtInt(uint8_t id, uint8_t int_config, CALLBACK_t pcallback) {
	_id = id;
	_pcallback[_id] = pcallback;

	EIMSK &= ~(1 << _id);	// disable to config

	// Set config
	if (id < INT_4) {
		EICRA |= (int_config << (_id*2));
	} else {
		EICRB |= (int_config << ((_id-4)*2));
	}

	EIFR |= (1 << _id);
}

ExtInt::~ExtInt() {
	// TODO Auto-generated destructor stub
}

void ExtInt::enable() {
	EIMSK |= (1 << _id);
}

void ExtInt::disable() {
	EIMSK &= ~(1 << _id);
}

void ExtInt::callback(){
	(*_pcallback)();
}

ISR(INT0_vect) {
	ExtInt::vect_handler(0);
}

ISR(INT1_vect) {
	ExtInt::vect_handler(1);
}

ISR(INT2_vect) {
	ExtInt::vect_handler(2);
}

ISR(INT3_vect) {
	ExtInt::vect_handler(3);
}

ISR(INT4_vect) {
	ExtInt::vect_handler(4);
}

ISR(INT5_vect) {
	ExtInt::vect_handler(5);
}

ISR(INT6_vect) {
	ExtInt::vect_handler(6);
}

ISR(INT7_vect) {
	ExtInt::vect_handler(7);
}

}
