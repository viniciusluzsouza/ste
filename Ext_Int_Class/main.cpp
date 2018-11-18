#include <avr/interrupt.h>
#include "Ext_Int.h"
#include "UART.h"
#include <util/delay.h>
#define F_CPU 16000000
using namespace EXT_INT;

UART uart(9600, UART::disable, UART::eight_bits, UART::none, UART::one);

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
    cli();

	Ext_Int int0_obj(Ext_Int::Int0, Ext_Int::FALLING, &int0_handler);
	Ext_Int int1_obj(Ext_Int::Int1, Ext_Int::FALLING, &int1_handler);
	Ext_Int int2_obj(Ext_Int::Int2, Ext_Int::FALLING, &int2_handler);
	Ext_Int int3_obj(Ext_Int::Int3, Ext_Int::FALLING, &int3_handler);
	Ext_Int int4_obj(Ext_Int::Int4, Ext_Int::FALLING, &int4_handler);
	Ext_Int int5_obj(Ext_Int::Int5, Ext_Int::FALLING, &int5_handler);
	Ext_Int int6_obj(Ext_Int::Int6, Ext_Int::FALLING, &int6_handler);
	Ext_Int int7_obj(Ext_Int::Int7, Ext_Int::FALLING, &int7_handler);


	int0_obj.enable();
	int1_obj.enable();
	/*int2_obj.enable();
	int3_obj.enable();
	int4_obj.enable();
	int5_obj.enable();
	int6_obj.enable();
	int7_obj.enable();
	*/

	sei();
	while(1){
	                           /* forever */
		if (uart.has_data()){
			uart.put(uart.get());                 /* echo the received character */
			uart.put((EICRA));
		}
	}

	return 0;
}
