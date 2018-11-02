/*
 * ExtInt.h
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#ifndef EXTINT_H_
#define EXTINT_H_

#include <stdint.h>

namespace EXT_INT {

typedef void (*CALLBACK_t)(void);

class ExtInt {
public:
    enum ISC_t {
        LOW = 0,
        ANY = 1,
        FALLING = 2,
        RISING = 3
    };

    enum INT_ID_t {
        INT_0 = 0,
        INT_1 = 1,
        INT_2 = 2,
        INT_3 = 3,
        INT_4 = 4,
        INT_5 = 5,
        INT_6 = 6,
        INT_7 = 7
    };

    ExtInt(uint8_t id, uint8_t int_config, CALLBACK_t pcallback);
    ~ExtInt();
    void enable();
    void disable();
    void callback();
    static void vect_handler(uint8_t vect){ (ExtInt::_pcallback[vect])(); }

private:
    uint8_t _id;
    static CALLBACK_t _pcallback[8];
};

}

#endif /* EXTINT_H_ */
