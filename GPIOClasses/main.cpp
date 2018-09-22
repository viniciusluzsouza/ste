#include <util/delay.h>
#include <stdlib.h>

#include "GPIO.h"
#include "utils.h"

int main(void) {
    int p_led = 2;
    int p_bt = 3;

    GPIO *led = new GPIO(p_led, GPIO::OUTPUT);
    GPIO *bt = new GPIO(p_bt, GPIO::INPUT);

    while (1) {
//        if (bt->get()){
//        	led->set(1);
//        } else {
//        	led->clear();
//        }
    	led->toggle();
    	_delay_ms(1000);
    }

    delete led;

}
