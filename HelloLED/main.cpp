#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    // Set input and output ports
    DDRE &= ~(1 << DDE4);				// Set 0 to DDRE4 (PE4)
    DDRE &= ~(1 << DDE5);				// Set 0 to DDRE5 (PE5)
    DDRH |= (1 << DDH5);				// Set 1 to DDRH5 (PH5)
    DDRH |= (1 << DDH6);				// Set 1 to DDRH6 (PH6)

    while (true) {

        if (PINE & (1 << PINE4)) {
            PORTH |= (1 << PH5);
        } else {
            PORTH &= ~(1 << PH5);
        }

        if (PINE & (1 << PINE5)) {
            PORTH |= (1 << PH6);
        } else {
            PORTH &= ~(1 << PH6);
        }
    }

}
