#pragma once
#include <fstream>
#ifndef STRL_H
#define STRL_H
using namespace std;
class strl {
private:
	char p[128];
	size_t size;
public:
	strl() {
		size = 0;
	}

	strl(const char arr[128]) {
		size = 0;
		while (size < 128 && arr[size] != '\0') p[size] = arr[size++];
	}

	~strl() {
		delete[] p;
	}

	char& operator[] (int i) {
		return p[i];
	}

	strl& operator+= (char added) {
		p[size++] = added;
		return *this;
	}

	strl& operator+= (strl added) {
		for (size_t i = 0; i < added.getSize(); i++)
			p[size + i + 1] = added.p[i];
		size += added.getSize();
		return *this;
	}
	
	friend bool operator== (const strl& first_compared, const strl& second_compared) {
		if (first_compared.size != second_compared.size) return false;
		for (int i = 0; i < first_compared.size; i++)
			if (first_compared.p[i] != second_compared.p[i]) return false;
		return true;
	}

	friend bool operator!= (const strl& first_compared, const strl& second_compared) {
		if (first_compared.size != second_compared.size) return true;
		for (int i = 0; i < first_compared.size; i++)
			if (first_compared.p[i] != second_compared.p[i]) return true;
		return false;
		/*
		if (first_compared == second_compared) return false;
		else return true;
		*/
	}

	/*
	friend bool operator== (const strl& first_compared, const char second_compared[128]) {
		
	}
	*/

	size_t getSize() {
		return size;
	}

	void input(fstream& f){
		size = 0;
		char s = ' ';
		f >> noskipws;
		while (!f.eof()) {
			f >> s;
			if (s != '\n' && !f.eof()) p[size++] = s;
			else break;
		}
	}

	void output(fstream& f) {
		int i = 0;
		while (i < size) f << p[i++];
	}

	bool isDigit() {
		if ((p[0] - '0' >= 0 && p[0] - '0' <= 9) || *this == "pi" || *this == "e") return true;
		else return false;
	}

	int getOperationWeight() {
		strl symbol = *this;
		if (symbol == "(") return 0;
		else if (symbol == "+" || symbol == "-") return 1;
		else if (symbol == "*" || symbol == "/" || symbol == "%") return 2;
		else if (symbol == "^") return 3;
		else if (symbol == "cos" || symbol == "sin" || symbol == "tg" || symbol == "ctg" || symbol == "ln" || symbol == "log" || symbol == "ln" || symbol == "sqrt") return 4;
	}

};
#endif // !STRL_H

