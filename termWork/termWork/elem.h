#pragma once
#include "strl.h"
#ifndef ELEM_H
#define ELEM_H
class elem {
private:
	strl symbol;
	int weight;
	elem* next;
public:
	elem(strl elem_symbol, elem* elem_next) {
		symbol = elem_symbol;
		next = elem_next;
		weight = elem_symbol.getOperationWeight();
	}

	elem(double value, elem* elem_next) {
		symbol = value;
		next = elem_next;
		weight = -1;
	}

	~elem() {

	}

	bool isBracket() {
		if (symbol == "(" || symbol == ")") return true;
		else return false;
	}

	bool isDigit() {
		if ((symbol[0] - '0' >= 0 && symbol[0] - '0' <= 9) || symbol == "pi" || symbol == "e") return true;
		else return false;
	}

	elem* getNext() {
		return next;
	}

	int getWeight() {
		return weight;
	}

	strl getSymbol() {
		return symbol;
	}
};
#endif // !ELEM_H
