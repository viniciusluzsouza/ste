/*
 * GPIO.h
 *
 *  Created on: 22 de set de 2018
 *      Author: vini
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

class GPIO {
public:
    enum direction_t { INPUT=0, OUTPUT=1 };

    GPIO(int id, direction_t direction);
    ~GPIO();

    bool get();
    void set(bool b);
    void clear();
    void toggle();
    direction_t _direction;

private:
    int _id, _pin_mask, _port_mask;
    volatile uint8_t *_pin, *_port;
};

#endif /* GPIO_H_ */
