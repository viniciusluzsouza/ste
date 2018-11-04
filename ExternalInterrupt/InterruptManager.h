/*
 * InterruptManager.h
 *
 *  Created on: 3 de nov de 2018
 *      Author: vini
 */

#ifndef INTERRUPTMANAGER_H_
#define INTERRUPTMANAGER_H_

#include "ExtInt.h"
#include "PCInt.h"
#include <stdlib.h>

namespace INT_MANAGER {

typedef void (*callback_t)(void);

class InterruptManager {
public:
    enum ISC_t {
        LOW = 0,
        ANY = 1,
        FALLING = 2,
        RISING = 3
    };

    enum INT_ID {
        INT_0 = 0, INT_1, INT_2, INT_3, INT_4, INT_5, INT_6, INT_7
    };

    enum PCINT_ID {
        PCINT_0 = 0, PCINT_1, PCINT_2, PCINT_3, PCINT_4, PCINT_5, PCINT_6, PCINT_7,
		PCINT_8, PCINT_9, PCINT_10, PCINT_11, PCINT_12, PCINT_13, PCINT_14, PCINT_15,
		PCINT_16, PCINT_17, PCINT_18, PCINT_19, PCINT_20, PCINT_21, PCINT_22, PCINT_23
    };

	InterruptManager();
	void add_int(uint8_t id, callback_t callback, uint8_t config);
	void add_pcint(uint8_t id, callback_t callback);
	void enable_int(uint8_t id);
	void disable_int(uint8_t id);
	void enable_pcint(uint8_t id);
	void disable_pcint(uint8_t id);
	~InterruptManager();

private:
	EXT_INT::ExtInt _extint_vect[8];
	PCINT::PCInt _pcint_vect[24];
};

}

#endif /* INTERRUPTMANAGER_H_ */
