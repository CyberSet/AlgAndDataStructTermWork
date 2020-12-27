#pragma once
#include <fstream>
#include <cmath>
#ifndef STRL_H
#define STRL_H
const int N = 128;
using namespace std;
class strl {
private:
	char p[N];
	size_t size;
public:
	strl() {
		size = 0;
	}

	strl(const char arr[N]) {
		size = 0;
		while (size < N && arr[size] != '\0') p[size] = arr[size++];
	}

	strl(double value) { //parsing double to string using sprintf
		char temp[N];
		sprintf_s(temp, "%f", value);
		int i = 0;
		while (i < N && ((temp[i] >= '0' && temp[i]<='9') || temp[i] == '.' || temp[i] == '-'))
			p[i] = temp[i++];
		size = i;
	}

	~strl() {
		//delete[] p;
	}

	char& operator[] (int i) {
		return p[i];
	}

	strl& operator+= (char added) { //adding single char to string`s end
		p[size++] = added;
		return *this;
	}

	strl& operator+= (strl added) {
		for (size_t i = 0; i < added.getSize(); i++)
			p[size + i] = added.p[i];
		size += added.getSize() + 1;
		p[size - 1] = ' ';
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
		if ((p[0] >= '0' && p[0] <= '9') || *this == "pi" || *this == "e") return true;
		else if (p[0] == '-' && p[1] >= '0' && p[1] <= '9') return true;
		else return false;
	}

	bool isOperation() {
		if (getOperationWeight() == -1) return false;
		else return true;
	}

	int getOperationWeight() {
		if (*this == "(" || *this == ")") return 0;
		else if (*this == "+" || *this == "-") return 1;
		else if (*this == "*" || *this == "/" || *this == "%") return 2;
		else if (*this == "^") return 3;
		else if (*this == "cos" || *this == "sin" || *this == "tg" || *this == "ctg" || *this == "ln" || *this == "log" || *this == "sqrt") return 4;
		else return -1;
	}

	double perform(strl first_operand) { //carrying out operations with single operand
		double operand = atof(first_operand.p);
		if (*this == "cos") return cos(operand);
		if (*this == "sin") return sin(operand);
		if (*this == "tg") return tan(operand);
		if (*this == "ctg") return 1 / tan(operand);
		if (*this == "ln") return log(operand);
		if (*this == "log") return log10(operand);
		if (*this == "sqrt") return sqrt(operand);
	}

	double perform(strl first_operand, strl second_operand) { //carrying out operations with 2 operands
		double second = atof(first_operand.p); // in case we are taking two operands they already swapped in stack
		double first = atof(second_operand.p); // we need to swap them again
		if (*this == "+") return first + second;
		if (*this == "-") return first - second;
		if (*this == "*") return first * second;
		if (*this == "/") return first / second;
		if (*this == "%") return fmod(first, second);
		if (*this == "^") return pow(first, second);
	}

	bool isCorrectInfix(fstream &toOut) {
		int bracketsCount = 0;
		strl cur;
		for (int i = 0; i <= size; i++) {
			if (p[i] != ' ' && i != size) cur += p[i];
			else {
				if (!cur.isOperation() && !cur.isDigit()) {
					toOut << "\nUnknown character detected at " << i << " position is ";
					cur.output(toOut);
					return false;
				}
				else {
					if (cur == "(") bracketsCount += 1;
					else if (cur == ")") {
						if (bracketsCount > 0) bracketsCount -= 1;
						else {
							toOut << "\nIncorrect placement of brackets";
							return false;
						}
					}
				}
				cur = "";
			}
		}
		if (!bracketsCount) return true;
		else {
			toOut << "\nIncorrect placement of brackets";
			return false;
		}
	}

};
#endif // !STRL_H