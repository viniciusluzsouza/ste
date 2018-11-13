#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer.h"

bool led_state1 = 0;
void toogle_led1() {
	if (led_state1) PORTH &= ~(1 << PH5);
	else PORTH |= (1 << PH5);
	led_state1 = !led_state1;
}

bool led_state2 = 0;
void toogle_led2() {
	if (led_state2) PORTH &= ~(1 << PH6);
	else PORTH |= (1 << PH6);
	led_state2 = !led_state2;
}

int main(void) {

    // Set output port
    DDRH |= (1 << DDH5);				// Set 1 to DDRH5 (PH5)
    DDRH |= (1 << DDH6);				// Set 1 to DDRH6 (PH6)

	Timer timer2 = Timer(1000, Timer::TIMER16_1);
	timer2.addTimeout(500, &toogle_led2);

	Timer timer1 = Timer(1000, Timer::TIMER8_0);
	timer1.addTimeout(1000, &toogle_led1);

	sei();

    while (true) {

    	timer1.timeoutManager();
    	timer2.timeoutManager();

    }
}
