#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR_VALUE F_CPU/16/BAUD-1

int dig_to_analog(float dig){
  return dig*(1024.0/5.0);

}

int analog_to_dig(float analog){
  return analog*(1024.0/5.0);
}

void uart_init() {
	// Set baud rate
    UBRR0 = MYUBRR_VALUE;

    // Set TX and RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data, 1 stop bit (00000110)
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void adc_init() {
	ADMUX = 0x00;
	ADCSRA = (1 << ADEN);
}

int analog_read() {
	int val;
	ADCSRA |= (1 << ADSC);
	val = ADC;
	ADCSRA &= ~(1 << ADSC);
	return val;
}

int main(void) {
	uart_init();
	adc_init();

	while (1) {
		_delay_ms(5000);
		int analog = analog_read();
	}

}
