#include <avr/io.h>
#include "Singleton.h"

#ifndef UART_H_
#define UART_H_

class UART : public Singleton<UART> {

  private:
    bool new_data;
    uint8_t rx_buff;
    uint8_t tx_buff;

  public:

    enum DoubleSpeed_t {
      disable = 0,
      enable = 2
    };
    enum DataBits_t {
      five_bits = 0,
      six_bits = 2,
      seven_bits = 4,
      eight_bits = 6
    };

    enum Parity_t {
      none = 0,
      even = 32,
      odd = 48
    };

    enum StopBit_t {
      one = 0,
      two = 8
    };

    UART(int baud, DoubleSpeed_t speed, DataBits_t data, Parity_t parity, StopBit_t stop);
    ~UART();

    void put(unsigned char data);
    void puts(const char * str);
    unsigned char get();
    bool has_data();
    static void rx_ISR();
    static void tx_ISR();
};


#endif /* UART_H_ */
