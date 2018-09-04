#include <avr/io.h>

#define BAUD 9600
#define MYUBRR_VALUE F_CPU/16/BAUD-1

void uart_init() {
	// Set baud rate
    UBRR0 = MYUBRR_VALUE;

    // Set TX and RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data, 1 stop bit (00000110)
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);


void uart_tx(unsigned char data) {

	/* Wait for empty transmit buffer.
	 * This method is bloking.*/

	// Verify 5th bit of UCSR0A Register (USART Data register empty)
	while ( !(UCSR0A & (1 << UDRE0)) );

	UDR0 = data;
}

unsigned char uart_rx(void) {
	while ( !(UCSR0A & (1 << RXC0)) );
	return UDR0;
}

int main(void) {
	unsigned char input;

	uart_init();
	while(true) {
		input = uart_rx();
		uart_tx(input);
	}

}
