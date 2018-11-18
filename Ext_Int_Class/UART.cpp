#define F_CPU 16000000

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

UART::UART(int baud, DoubleSpeed_t speed,DataBits_t data, Parity_t parity, StopBit_t stop) {
  // Equation for Calculating UBRR Value:
  uint16_t UBRRn = (F_CPU/16/baud-1);

  self()->new_data = false;

  UBRR0 = UBRRn;
  UCSR0A |= speed;
  UCSR0B |=  (1<<RXCIE0)|(1<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0);
  UCSR0C = data | parity | stop;
}

UART::~UART() {}

bool UART::has_data(){
  return self()->new_data;
}

ISR(USART0_RX_vect){
  UART::rx_ISR();
}

ISR(USART0_UDRE_vect){
  UART::tx_ISR();
}

void UART::tx_ISR(){
  UDR0 = self()->tx_buff;
  UCSR0B &=  ~(1<<UDRIE0);
}

void UART::rx_ISR(){
  self()->rx_buff = UDR0;
  self()->new_data = true;
}

void UART::put(unsigned char data) {
  self()->tx_buff = data;
  UCSR0B |=  (1<<UDRIE0);
}

void UART::puts(const char * str) {
  int pos = 0;
  for(pos = 0; *(str+pos) != 0; pos++) put((unsigned char)*(str+pos));

}

unsigned char UART::get() {
  self()->new_data = false;
  return self()->rx_buff;
}
