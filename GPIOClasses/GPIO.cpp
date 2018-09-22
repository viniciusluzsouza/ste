/*
 * GPIO.cpp
 *
 *  Created on: 22 de set de 2018
 *      Author: vini
 */

#include "GPIO.h"
#include <avr/io.h>

GPIO::GPIO(int id, direction_t direction) {
    this->_id = id;
    this->_direction = direction;

    switch (this->_id) {
    case 0:
        if (this->_direction == INPUT) DDRE &= ~(1 << DDE0);
        else DDRE |= (1 << DDE0);
        this->_pin = &PINE;
        this->_port = &PORTE;
        this->_pin_mask = (1 << PINE0);
        this->_port_mask = (1 << PE0);
        break;

    case 1:
        if (this->_direction == INPUT) DDRE &= ~(1 << DDE1);
        else DDRE |= (1 << DDE1);
        this->_pin = &PINE;
        this->_port = &PORTE;
        this->_pin_mask = (1 << PINE1);
        this->_port_mask = (1 << PE1);
        break;

    case 2:
        if (this->_direction == INPUT) DDRE &= ~(1 << DDE4);
        else DDRE |= (1 << DDE4);
        this->_pin = &PINE;
        this->_port = &PORTE;
        this->_pin_mask = (1 << PINE4);
        this->_port_mask = (1 << PE4);
        break;

    case 3:
        if (this->_direction == INPUT) DDRE &= ~(1 << DDE5);
        else DDRE |= (1 << DDE5);
        this->_pin = &PINE;
        this->_port = &PORTE;
        this->_pin_mask = (1 << PINE5);
        this->_port_mask = (1 << PE5);
        break;

    case 4:
        if (this->_direction == INPUT) DDRG &= ~(1 << DDG5);
        else DDRG |= (1 << DDG5);
        this->_pin = &PING;
        this->_port = &PORTG;
        this->_pin_mask = (1 << PING5);
        this->_port_mask = (1 << PG5);
        break;

    case 5:
        if (this->_direction == INPUT) DDRE &= ~(1 << DDE3);
        else DDRE |= (1 << DDE3);
        this->_pin = &PINE;
        this->_port = &PORTE;
        this->_pin_mask = (1 << PINE3);
        this->_port_mask = (1 << PE3);
        break;

    case 6:
        if (this->_direction == INPUT) DDRH &= ~(1 << DDH3);
        else DDRH |= (1 << DDH3);
        this->_pin = &PINH;
        this->_port = &PORTH;
        this->_pin_mask = (1 << PINH3);
        this->_port_mask = (1 << PH3);
        break;

    case 7:
        if (this->_direction == INPUT) DDRH &= ~(1 << DDH4);
        else DDRH |= (1 << DDH4);
        this->_pin = &PINH;
        this->_port = &PORTH;
        this->_pin_mask = (1 << PINH4);
        this->_port_mask = (1 << PH4);
        break;

    case 8:
        if (this->_direction == INPUT) DDRH &= ~(1 << DDH5);
        else DDRH |= (1 << DDH5);
        this->_pin = &PINH;
        this->_port = &PORTH;
        this->_pin_mask = (1 << PINH5);
        this->_port_mask = (1 << PH5);
        break;

    case 9:
        if (this->_direction == INPUT) DDRH &= ~(1 << DDH6);
        else DDRH |= (1 << DDH6);
        this->_pin = &PINH;
        this->_port = &PORTH;
        this->_pin_mask = (1 << PINH6);
        this->_port_mask = (1 << PH6);
        break;

    case 10:
        if (this->_direction == INPUT) DDRB &= ~(1 << DDB4);
        else DDRB |= (1 << DDB4);
        this->_pin = &PINB;
        this->_port = &PORTB;
        this->_pin_mask = (1 << PINB4);
        this->_port_mask = (1 << PB4);
        break;

    case 11:
        if (this->_direction == INPUT) DDRB &= ~(1 << DDB5);
        else DDRB |= (1 << DDB5);
        this->_pin = &PINB;
        this->_port = &PORTB;
        this->_pin_mask = (1 << PINB5);
        this->_port_mask = (1 << PB5);
        break;

    case 12:
        if (this->_direction == INPUT) DDRB &= ~(1 << DDB6);
        else DDRB |= (1 << DDB6);
        this->_pin = &PINB;
        this->_port = &PORTB;
        this->_pin_mask = (1 << PINB6);
        this->_port_mask = (1 << PB6);
        break;

    case 13:
        if (this->_direction == INPUT) DDRB &= ~(1 << DDB7);
        else DDRB |= (1 << DDB7);
        this->_pin = &PINB;
        this->_port = &PORTB;
        this->_pin_mask = (1 << PINB7);
        this->_port_mask = (1 << PB7);
        break;

    default:
        break;

    }

}

GPIO::~GPIO() {
    // TODO Auto-generated destructor stub
}

bool GPIO::get() {
    return (*this->_pin & this->_pin_mask);
}

void GPIO::set(bool b) {
    if (b) *this->_port |= (this->_port_mask);
    else *this->_port &= ~(this->_port_mask);
}

void GPIO::clear() {
    this->set(0);
}

void GPIO::toggle() {
	*this->_pin |= (this->_pin_mask);
}

