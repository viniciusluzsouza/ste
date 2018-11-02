/*
 * Queue.h
 *
 *  Created on: 2 de nov de 2018
 *      Author: vini
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>

template <typename T> class Queue {
public:
	Queue(unsigned int N);
    ~Queue();
    void put(const T & obj);
    T get();
    bool is_empty() const {return _items == 0; }
    bool is_full() const { return _items == _capacity;}
    int items() const { return _items; }

private:
    int _capacity;
    int _items, _begin, _end;
    T* _buf;
};

template <typename T> Queue<T>::Queue(unsigned int N) {
	_capacity = N;
	_begin = 0;
	_end = 0;
	_items = 0;

	_buf = (T*) malloc(sizeof(Queue)*_capacity);
}

template <typename T> Queue<T>::~Queue() {
}

template <typename T> void Queue<T>::put(const T& obj) {
  if ( _items == _capacity ) return;

  _buf[_end] = obj;
  _items++;
  _end++;
  if (_end == _capacity )_end = 0;
}

template <typename T> T Queue<T>::get() {
  T val = _buf[_begin];
  _begin++;
  _items--;
  if ( _begin == _capacity ) _begin = 0;
  return val;
}

#endif /* QUEUE_H_ */
