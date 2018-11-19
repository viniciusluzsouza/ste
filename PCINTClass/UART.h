/*
 * UART.h
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000

#include <stdint.h>
#include "Singleton.h"
#include "Queue.h"

typedef Queue<uint8_t, 30> QUEUE_t;

class UART : public Singleton<UART> {
public:
    enum DataBits_t {
        FIVE_DB = 0,
        SIX_DB = 2,
        SEVEN_DB = 4,
        EIGHT_DB = 6
    };

    enum Parity_t {
        NONE_PAR = 0,
        EVEN_PAR = 32,
        ODD_PAR = 48
    };

    enum StopBit_t {
        ONE_SB = 0,
        TWO_SB = 8
    };

    enum DoubleSpeed_t {
    	DS_ENABLE = 1,
		DS_DISABLE = 0
    };

    UART(uint16_t baud, DataBits_t db, Parity_t par, StopBit_t sb, uint8_t double_speed=0);
    ~UART();
    void put(uint8_t data);
    void puts(const char* data);
    uint8_t get();
    bool has_data();

    // Interrupt handlers
    static void rxc_isr_handler();
    static void udre_isr_handler();

private:
    QUEUE_t _rx_buffer;
    QUEUE_t _tx_buffer;
};

#endif /* UART_H_ */
