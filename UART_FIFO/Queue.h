/*
 * Queue.h
 *
 *  Created on: 2 de nov de 2018
 *      Author: vini
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T, int N> class Queue {
public:
	Queue() {
		clear();
	}

	~Queue() {};
	void put(const T & obj) {
	  if ( _items == N ) return;

	  _buf[_end] = obj;
	  _items++;
	  _end++;
	  if (_end == N ) _end = 0;
	}

	T get() {
	  T val = _buf[_begin];
	  _begin++;
	  _items--;
	  if ( _begin == N ) _begin = 0;
	  return val;
	}

	void clear() {
		_begin=0;
		_end=0;
		_items=0;
		memset((void*) _buf, 0, N * sizeof(T));
	}

	bool is_empty() const {return _items == 0; }
	bool is_full() const { return _items == N;}
	int items() const { return _items; }

private:
    int _items, _begin, _end;
    T _buf[N];
};

#endif /* QUEUE_H_ */
