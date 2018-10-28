#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "UART.h"

// just a hack because avr-g++ do not suport new and delete operators...
void* operator new(size_t objsize) {
  return malloc(objsize);
}

// in IFSC the compiler want this
void operator delete(void* obj) {
  free(obj);
}
// in my home the compiler want this
void operator delete(void* obj, unsigned int unused) {
  free(obj);
}
// -----------------------------------------------------------------

int main(void) {

    UART *uart = new UART(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);
    sei();

    uint8_t input = 0x41;
    while (1) {
        if (uart->has_data()) {
            input = uart->get();
            uart->put(input);
        }
    }
}
