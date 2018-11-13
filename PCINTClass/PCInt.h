/*
 * PCInt.h
 *
 *  Created on: 3 de nov de 2018
 *      Author: vini
 */

#ifndef PCINT_H_
#define PCINT_H_

#include <stdint.h>
#include "Singleton.h"

namespace PCINT {

typedef void (*CALLBACK_t)(void);

class PCInt : public Singleton<PCInt> {
public:
    enum PCINT_ID_t {
        PCINT_0 = 0, PCINT_1, PCINT_2, PCINT_3, PCINT_4, PCINT_5, PCINT_6, PCINT_7,
		PCINT_8, PCINT_9, PCINT_10, PCINT_11, PCINT_12, PCINT_13, PCINT_14, PCINT_15,
		PCINT_16, PCINT_17, PCINT_18, PCINT_19, PCINT_20, PCINT_21, PCINT_22, PCINT_23
    };

    PCInt();
    ~PCInt();
    void enable(uint8_t id, CALLBACK_t callback);
    void disable(uint8_t id);
    void check_interrupts();
    static void vect_handler(uint8_t id){ (self()->PCInt::_event[id]) = true; }

private:
    bool _event[24];
    bool _enabled_interrupts[24];
    CALLBACK_t _callbacks[24];
    uint8_t _pcint_counter[3];
};

}

#endif /* PCINT_H_ */
