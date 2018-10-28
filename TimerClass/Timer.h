/*
 * Timer.h
 *
 *  Created on: 28 de out de 2018
 *      Author: vini
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Singleton.h"
#include "Timeout.h"

typedef unsigned long Hertz;
typedef unsigned long long Microseconds;
typedef unsigned long long Milliseconds;

class Timer : public Singleton<Timer> {
public:
	/*
	 * Will configure timer to the closest frequency
	 * that does not produce rounding errors.
	 * Example:
	 *   freq	-	Actual Timer Frequency (Hz)
	 *   100	-	100,1602564
	 *   500	-	504,0322581
	 *   1000	-	1041,666667
	 *   2000	-	2232,142857
	 *   5000	-	5208,333333
	 *   10000	-	15625
	 */
	Timer(Hertz freq);

	Milliseconds millis();
	Microseconds micros();

	void delay(Milliseconds ms);
	void udelay(Microseconds us);
	void timeoutManager();
	bool addTimeout(uint32_t interval, CALLBACK_t callback);

	static void ovf_isr_handler();

private:
	unsigned long long _ticks;
	unsigned int _timer_base;
	Microseconds _us_per_tick;
	Timeout _timeouts[4];
	uint32_t _timeout_counter;
};

#endif /* TIMER_H_ */
