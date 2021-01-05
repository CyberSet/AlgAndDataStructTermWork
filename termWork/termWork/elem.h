#pragma once
#include "strl.h"
#ifndef ELEM_H
#define ELEM_H
template <class T>
class elem {
private:
	T value;
	int weight;
	elem* next;
public:
	elem(T elem_value, elem<T>* elem_next) {
		value = elem_value;
		next = elem_next;
		weight = elem_value.getOperationWeight();
	}

	~elem() {

	}

	elem* getNext() {
		return next;
	}

	int getWeight() {
		return weight;
	}

	strl getValue() {
		return value;
	}
};
#endif // !ELEM_H
