/*
 * Dialer.cpp
 *
 *  Created on: 6 de dez de 2018
 *      Author: vini
 */

#include "Dialer.h"
#include <string.h>
#include <util/delay.h>

bool Dialer::cancel;

Dialer::Dialer() :
	_uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE),
	_start(8, GPIO::INPUT), _program(9, GPIO::INPUT), _hks(50, GPIO::OUTPUT)
{
	memset(sequency, 0, sizeof(sequency));
	strcpy(sequency, "0123456789*#");	// default sequency

	for(int i=0;i<4;i++) {
		_line[i].create(i+26, GPIO::OUTPUT);
		_column[i].create(i+22, GPIO::OUTPUT);

		_line[i].set(1);
		_column[i].set(1);
	}

	cancel = false;
	_hks.set(1);
}

void Dialer::dial() {
	_hks.set(0);

	for(int i=0;sequency[i]!=0;i++) {
		if (cancel) {
			cancel = false;
			break;
		}

		int l, c;

		switch (sequency[i]) {
		case '1':
			l = 0;
			c = 0;
			break;

		case '2':
			l = 0;
			c = 1;
			break;

		case '3':
			l = 0;
			c = 2;
			break;

		case '4':
			l = 1;
			c = 0;
			break;

		case '5':
			l = 1;
			c = 1;
			break;

		case '6':
			l = 1;
			c = 2;
			break;

		case '7':
			l = 2;
			c = 0;
			break;

		case '8':
			l = 2;
			c = 1;
			break;

		case '9':
			l = 2;
			c = 2;
			break;

		case '0':
			l = 3;
			c = 1;
			break;

		case '*':
			l = 3;
			c = 0;
			break;

		case '#':
			l = 3;
			c = 2;
			break;

		default:
			l = -1;
			c = -1;
		}

		if (l<0 && c<0) continue;

		_line[l].set(0);
		_column[c].set(0);

		_uart.put((uint8_t) sequency[i]);

		// Precisamos setar de novo a linha e coluna,
		// devemos esperar algum tempo?
		_delay_ms(500);
		_line[l].set(1);
		_column[c].set(1);

	}

	_delay_ms(500);
	_hks.set(1);
	_uart.puts("\n");
}

void Dialer::program() {
	_uart.puts("Nova sequencia: \n");

	_delay_ms(200);	// debounce?

	while (!_program.get());

	if (_uart.has_data()) {
		char new_seq[16];
		memset(new_seq, 0, sizeof(new_seq));

		for(int i=0;_uart.has_data();i++) {
			if (cancel) {
				cancel = false;
				return;
			}

			if (i==16) break;
			new_seq[i] = (char) _uart.get();
		}

		strcpy(sequency, new_seq);
	}

	_uart.puts("Sequencia salva!\n");
	_delay_ms(200); // debounce?
}

void Dialer::execute() {
	if (_start.get()) dial();
	else if (_program.get()) program();
}

Dialer::~Dialer() {
	// TODO Auto-generated destructor stub
}

