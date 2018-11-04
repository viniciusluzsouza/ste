/*
 * InterruptManager.cpp
 *
 *  Created on: 3 de nov de 2018
 *      Author: vini
 */

#include "InterruptManager.h"

namespace INT_MANAGER {

InterruptManager::InterruptManager() {
}

InterruptManager::~InterruptManager() {
}

void InterruptManager::add_int(uint8_t id, callback_t callback, uint8_t config) {
	_extint_vect[id] = EXT_INT::ExtInt(id, config, callback);
}

void InterruptManager::add_pcint(uint8_t id, callback_t callback) {
	_pcint_vect[id] = PCINT::PCInt(id, callback);
}

void InterruptManager::enable_int(uint8_t id) {
	_extint_vect[id].enable();
}

void InterruptManager::disable_int(uint8_t id) {
	_extint_vect[id].disable();
}

void InterruptManager::enable_pcint(uint8_t id) {
	_pcint_vect[id].enable();
}

void InterruptManager::disable_pcint(uint8_t id) {
	_pcint_vect[id].disable();
}

}
