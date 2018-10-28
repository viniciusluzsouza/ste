/*
 * ExtInt.h
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#ifndef EXTINT_H_
#define EXTINT_H_

#include "Singleton.h"
#include <stdint.h>

namespace ExtInt {

typedef void (*CALLBACK_t)(void);

class ExtInt : Singleton<ExtInt> {
public:
    enum ISC_t {
        LOW = 0,
        ANY = 1,
        FALLING = 2,
        RISING = 3
    };

    enum INT_ID_t {
        INT0 = 0,
        INT1 = 1,
        INT2 = 2,
        INT3 = 3,
        INT4 = 4,
        INT5 = 5,
        INT6 = 6,
        INT7 = 7
    };

    ExtInt(INT_ID_t id, ISC_t int_config, CALLBACK_t pcallback);
    ~ExtInt();
    void enable();
    void disable();
    void callback();
    static ExtInt ExtInt_singletons[8];

private:
    uint8_t _id;
    CALLBACK_t _pcallback;
};

}

#endif /* EXTINT_H_ */
