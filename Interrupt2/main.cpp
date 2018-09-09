#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define BAUD 9600
#define MYUBRR_VALUE F_CPU/16/BAUD-1

unsigned int debounce_limit = 200;
unsigned int time_last_interrupt = 0;
bool led_state = 0;

unsigned long ms = 0;
unsigned char fract = 0;
unsigned long overflow = 0;

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

void clock_init(){
	TCCR0B |= (1 << CS00);
	TCCR0B |= (1 << CS01);
	TIMSK0 |= (1 << TOIE0);
}

ISR(TIMER0_OVF_vect) {
	unsigned long m = ms;
	unsigned char f = fract;

	m += 1;
	f += 3;
	if (f >= 125) {
		f -= 125;
		m += 1;
	}
	fract = f;
	ms = m;
	overflow++;
}

unsigned long millis() {
	unsigned long m;
	m = ms;
	return m;
}

int debounce() {
  if ( (millis() - time_last_interrupt) > debounce_limit) {
    time_last_interrupt = millis();
    return 1;
  } else return 0;
}

ISR(INT4_vect) {
	uint8_t oldSREG = SREG;
	if (debounce()) {
		uart_tx("Change LED\n");
		if (!(PINE & (1 << PINE4))) led_state = 1;
		else led_state = 0;
	}
	SREG = oldSREG;
}

int main(void) {
	cli();
	uart_init();
	clock_init();

	DDRE &= ~(1 << DDE4);				// Set 0 to DDRE4 (PE4)
//	PORTE = (1 << PE4);
//	MCUCR &= ~(1 << PUD);
	DDRH |= (1 << DDH5);				// Set 1 to DDRH5 (PH5)

	EICRA &= (1 << ISC00);				// rising up and down, but doesnt work
	EIMSK |= (1 << INT4);
	sei();

	while (1) {

		if (led_state) {
			PORTH |= (1 << PH5);
		} else {
			PORTH &= ~(1 << PH5);
		}

	}

}
