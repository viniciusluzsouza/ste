#include <avr/interrupt.h>
#include "ExtInt.h"
#include "UART.h"

using namespace EXT_INT;

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);

void int0_handler(void){
	uart.put('0');
	return;
}

void int1_handler(void){
	uart.put('1');
	return;
}

void int2_handler(void){
	uart.put('2');
	return;
}

void int3_handler(void){
	uart.put('3');
	return;
}

void int4_handler(void){
	uart.put('4');
	return;
}

void int5_handler(void){
	uart.put('5');
	return;
}

void int6_handler(void){
	uart.put('6');
	return;
}

void int7_handler(void){
	uart.put('7');
	return;
}

int main( void ){

	ExtInt int0_obj(ExtInt::INT_0, ExtInt::FALLING, &int0_handler);
	ExtInt int1_obj(ExtInt::INT_1, ExtInt::FALLING, &int1_handler);
	ExtInt int2_obj(ExtInt::INT_2, ExtInt::FALLING, &int2_handler);
	ExtInt int3_obj(ExtInt::INT_3, ExtInt::FALLING, &int3_handler);
	ExtInt int4_obj(ExtInt::INT_4, ExtInt::FALLING, &int4_handler);
	ExtInt int5_obj(ExtInt::INT_5, ExtInt::FALLING, &int5_handler);
	ExtInt int6_obj(ExtInt::INT_6, ExtInt::FALLING, &int6_handler);
	ExtInt int7_obj(ExtInt::INT_7, ExtInt::FALLING, &int7_handler);

	int0_obj.enable();
	int1_obj.enable();
	int2_obj.enable();
	int3_obj.enable();
	int4_obj.enable();
	int5_obj.enable();
	int6_obj.enable();
	int7_obj.enable();

	sei();
	uint8_t input = 0xFF;
	while(1){                                   /* forever */
		if (uart.has_data()){
			input = uart.get();
			uart.put(input);                 /* echo the received character */
		}
	}

return 0;

}
