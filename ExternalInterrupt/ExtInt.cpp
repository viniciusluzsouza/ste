/*
 * ExtInt.cpp
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#include "ExtInt.h"
#include "Singleton.h"
#include <avr/io.h>
#include <avr/interrupt.h>

using namespace ExtInt;

ExtInt::ExtInt(INT_ID_t id, ISC_t int_config, CALLBACK_t pcallback) {
	// Set config
	if (id < INT4) {
		EICRA |= int_config;
	} else {
		EICRB |= int_config;
	}

	_id = id;
	_pcallback = pcallback;
}

ExtInt::~ExtInt() {
	// TODO Auto-generated destructor stub
}

void ExtInt::enable() {
	EIMSK |= 1 << _id;
}

void ExtInt::disable() {
	EIMSK &= ~(1 << _id);
}

void ExtInt::callback(){
	_pcallback();
}

ISR(INT0_vect) {
	self()->ExtInt_singletons[0].callback();
}

ISR(INT1_vect) {
}

ISR(INT2_vect) {
}

ISR(INT3_vect) {
}

ISR(INT4_vect) {
}

ISR(INT5_vect) {
}

ISR(INT6_vect) {
}

ISR(INT7_vect) {
}

