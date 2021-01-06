#pragma once
#include "strl.h"
#ifndef ELEM_H
#define ELEM_H
template <class T>
class elem {
private:
	T value;
	elem* next;
public:
	elem(T elem_value, elem<T>* elem_next) {
		value = elem_value;
		next = elem_next;
	}

	~elem() {

	}

	elem* getNext() {
		return next;
	}


	T getValue() {
		return value;
	}
};
#endif // !ELEM_H
