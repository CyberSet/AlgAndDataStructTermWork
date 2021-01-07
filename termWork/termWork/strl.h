#pragma once
#include <fstream>
#include <cmath>
#ifndef STRL_H
#define STRL_H
const int N = 128;
const double PI = 2 * acos(0.0);
const double E = exp(1.0);
enum operationWeight {notOperationWeight = -1, bracketsOperationWeight, sumOperationWeight, mulOperationWeight, powOperationWeight, oneArgumentOperationWeight};
using namespace std;
class strl {
private:
	char p[N];
	int weight;
	size_t size;
public:
	strl() {
		size = 0;
		weight = -1;
	}

	strl(const char arr[N]) {
		size = 0;
		while (size < N && arr[size] != '\0') p[size] = arr[size++];
		weight = -1;
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

	strl& operator+= (strl added) { //adding another string to string`s end
		for (size_t i = 0; i < added.getSize(); i++)
			p[size + i] = added.p[i];
		size += added.getSize() + 1;
		p[size - 1] = ' '; //paste space to end
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
	}

	size_t getSize() {
		return size;
	}

	const char* getStream() {
		return p;
	}

	int getOperationWeight() { // getting weight to solve example with correct order
		if (*this == "(" || *this == ")") weight = bracketsOperationWeight;
		else if (*this == "+" || *this == "-") weight = sumOperationWeight;
		else if (*this == "*" || *this == "/" || *this == "%") weight = mulOperationWeight;
		else if (*this == "^") weight = powOperationWeight;
		else if (*this == "cos" || *this == "sin" || *this == "tg" || *this == "ctg" || *this == "ln" || *this == "log" || *this == "sqrt") weight = oneArgumentOperationWeight;
		else weight = notOperationWeight;
		return weight;
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
		bool flag = true;
		int i = 0;
		if (*this == "pi" || *this == "e") return true;
		else {
			if (p[0] == '-') {
				if (size == 1 || p[1] == '.') return false;
				i++;
			}
			else {
				if (p[0] == '.') return false;
			}
			while (i < size) {
				if (p[i] >= '0' && p[i] <= '9') {
					i++;
				}
				else {
					if (p[i] == '.' && flag) {
						flag = false;
						i++;
					}
					else return false;
				}
			}
			return true;
		}
		return true;
	}

	bool isOperation() {
		if (getOperationWeight() == notOperationWeight) return false;
		else return true;
	}

	double perform(double first_operand) { //carrying out operations with single operand
		if (*this == "cos") return cos(first_operand);
		if (*this == "sin") return sin(first_operand);
		if (*this == "tg") return tan(first_operand);
		if (*this == "ctg") return 1 / tan(first_operand);
		if (*this == "ln") return log(first_operand);
		if (*this == "log") return log10(first_operand);
		if (*this == "sqrt") return sqrt(first_operand);
	}

	double perform(double first_operand, double second_operand) { //carrying out operations with 2 operands
		// in case we are taking two operands they already swapped in stack
		// we need to swap them again
		if (*this == "+") return first_operand + second_operand;
		if (*this == "-") return second_operand - first_operand;
		if (*this == "*") return first_operand * second_operand;
		if (*this == "/") return second_operand / first_operand;
		if (*this == "%") return fmod(second_operand, first_operand);
		if (*this == "^") return pow(second_operand, first_operand);
	}

	bool isCorrectInfix(fstream &toOut) {
		int bracketsCount = 0;
		strl cur;
		for (int i = 0; i <= size; i++) {
			if (p[i] != ' ' && i != size) cur += p[i];
			else {
				if (!cur.isOperation() && !cur.isDigit()) { // if current string isn`t operation or digit throw position of unkown string 
					toOut << "\nUnknown character detected at " << i - cur.getSize() << " position is ";
					cur.output(toOut);
					return false;
				}
				else { // if current string is operation or digit check brackets positions
					if (cur == "(") bracketsCount += 1; // if current character is left parentheses increase brackets counter by 1
					else if (cur == ")") {
						if (bracketsCount > 0) bracketsCount -= 1; // if current character is end parentheses and exist previous left parentheses decrease brackets count by 1
						else {
							toOut << "\nIncorrect placement of brackets"; // else throw that we have brackets placement mistake
							return false;
						}
					}
				}
				cur = "";
			}
		}
		if (!bracketsCount) return true; // if we have got left parenthese without pair throw brackets placement mistake
		else {
			toOut << "\nIncorrect placement of brackets";
			return false;
		}
	}

};
#endif // !STRL_H