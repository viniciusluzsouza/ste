/*
 * PCInt.h
 *
 *  Created on: 3 de nov de 2018
 *      Author: vini
 */

#ifndef PCINT_H_
#define PCINT_H_

namespace PCINT {

typedef void (*pcint_CALLBACK_t)(void);

class PCInt {
public:
    enum PCINT_ID_t {
        PCINT_0 = 0, PCINT_1, PCINT_2, PCINT_3, PCINT_4, PCINT_5, PCINT_6, PCINT_7,
		PCINT_8, PCINT_9, PCINT_10, PCINT_11, PCINT_12, PCINT_13, PCINT_14, PCINT_15,
		PCINT_16, PCINT_17, PCINT_18, PCINT_19, PCINT_20, PCINT_21, PCINT_22, PCINT_23
    };

    PCInt(uint8_t id, pcint_CALLBACK_t pcint_callback);
    ~PCInt();
    void enable();
    void disable();
    void callback();
    static void vect_handler(uint8_t vect){ (PCInt::_pcint_callback[vect])(); }

private:
    uint8_t _id;
    static pcint_CALLBACK_t _pcint_callback[8];
};

} /* namespace PCINT */

#endif /* PCINT_H_ */
