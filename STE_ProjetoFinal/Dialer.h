/*
 * Dialer.h
 *
 *  Created on: 6 de dez de 2018
 *      Author: vini
 */

#ifndef DIALER_H_
#define DIALER_H_

#include "UART.h"
#include "GPIO.h"

class Dialer {
public:
	Dialer();
	~Dialer();

	void execute();
	void dial();
	void program();

	char sequency[16];
	static bool cancel;

private:
	UART _uart;
	GPIO _line[4];
	GPIO _column[4];
	GPIO _hks;
	GPIO _start;
	GPIO _program;
};

#endif /* DIALER_H_ */
