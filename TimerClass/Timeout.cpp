/*
 * Timeout.cpp
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#include "Timeout.h"

Timeout::Timeout() {
	// TODO Auto-generated constructor stub

}

Timeout::~Timeout() {
	// TODO Auto-generated destructor stub
}

void Timeout::config(uint32_t interval, CALLBACK_t callback)
{
	_event = false;
	_enable = true;
	_counter = 0;

	_callback = callback;
	_interval = interval;
}

void Timeout::checkTimeout()
{
	_counter++;
	if (_counter == _interval) {
		_event = true;
		_counter = 0;
	}
}

void Timeout::callback()
{
	_callback();
	_event = 0;
}

bool Timeout::event()
{
	return _event;
}
