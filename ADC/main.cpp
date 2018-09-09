#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BAUD 9600
#define MYUBRR_VALUE F_CPU/16/BAUD-1

void adc_init() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN);
    //ADCSRA = (1 << ADIF);
}

void uart_init() {
	// Set baud rate
    UBRR0 = MYUBRR_VALUE;

    // Set TX and RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data, 1 stop bit (00000110)
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_tx(char *data) {
    for (int i=0;data[i]!=0;i++) {
        while ( !(UCSR0A & (1 << UDRE0)) );
        UDR0 = data[i];
    }
}

int dig_to_analog(float dig){
  return (dig*5)/1023;

}

int analog_to_dig(float analog){
  return (analog*1023)/5;
}

int analog_read() {
	int val;
	ADCSRA |= (1 << ADSC);
	while ( !(ADCSRA & (1 << ADIF)) );
	val = ADC;
	ADCSRA &= ~(1 << ADSC);
	return val;
}

int rms_read(int repeat) {
	float accumulated = 0;
	for(int n=0;n<repeat;n++) {
		accumulated += analog_read();
	}
	return accumulated/repeat;
}

int main(void) {
	uart_init();
	adc_init();

	while (1) {
		_delay_ms(1000);
		char dig[100];
		char anal[100];
		memset(dig, 0, sizeof(dig));
		memset(anal, 0, sizeof(anal));

		int digital = rms_read(100);
		int analog = dig_to_analog(digital);

		itoa(digital, dig, 10);
		itoa(analog, anal, 10);

		strcat(dig, "\n");
		strcat(anal, "\n");

		uart_tx(dig);
		uart_tx(anal);
		uart_tx("==========\n");

	}

}
