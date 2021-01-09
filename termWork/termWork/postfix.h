#pragma once
#ifndef POSTFIX_H
#include "stack.h"
#include "strl.h"
#define POSTFIX_H
class postfix {
private:
	stack<strl> operations;
	stack<double> operands;
	strl outstream;
public:
	postfix(strl infix) { //convert correct infix form to postfix
		strl cur;
		int curOperationWeight = 0;
		bool ableToUnaryMinus = true;
		for (int i = 0; i <= infix.getSize(); i++) {
			if (infix[i] != ' ' && i != infix.getSize()) cur += infix[i];
			else {
				if (cur == "(") {
					operations.push(cur);
					ableToUnaryMinus = true;
				}
				else if (cur.isDigit())
				{
					outstream += cur;
					ableToUnaryMinus = false;
				}
				else if (cur == ")") {
					while (!operations.isEmpty() && operations.getTop()->getValue() != "(")
						addOperationToStream();
					operations.pop();
					ableToUnaryMinus = false;
				}
				else {
					if (cur == "-" && ableToUnaryMinus) {
						operations.push("*");
						outstream += "-1";
						ableToUnaryMinus = false;
					}
					else{
						curOperationWeight = cur.getOperationWeight();
						while (!operations.isEmpty() && operations.getTop()->getValue().getOperationWeight() >= curOperationWeight)
							addOperationToStream();
						operations.push(cur);
						ableToUnaryMinus = true;
					}
				}
				cur = "";
			}
		}
		while (!operations.isEmpty())
			addOperationToStream();
	}

	double calculate() { //calculating expression in postfix form
		double res = 0;
		strl cur;
		for (int i = 0; i < outstream.getSize(); i++) {
			if (outstream[i] != ' ') cur += outstream[i];
			else {
				if (cur.isDigit()) {
					if (cur == "pi") operands.push(PI);
					else if (cur == "e") operands.push(E);
					else operands.push(atof(cur.getStream()));
				}
				else if (cur.getOperationWeight() == oneArgumentOperationWeight) {
					res = cur.perform(operands.getTop()->getValue());
					operands.pop();
					operands.push(res);
				}
				else {
					res = cur.perform(operands.getTop()->getValue(), operands.getTop()->getNext()->getValue());
					operands.pop();
					operands.pop();
					operands.push(res);
				}
				cur = "";
			}
		}
		return operands.getTop()->getValue();
	}

	strl getStream() {
		return outstream;
	}

	void addOperationToStream() { // removing current operation from stack and place to output
		outstream += operations.getTop()->getValue();
		operations.pop();
	}

	
};
#endif // !POSTFIX_H

