#pragma once
#ifndef POSTFIX_H
#include "stack.h"
#include "strl.h"
#define POSTFIX_H
class postfix {
private:
	stack<strl> operations;
	strl outstream;
public:
	postfix(strl infix) { //convert correct infix form to postfix
		strl cur;
		int curOperationWeight = 0;
		bool flag = false;
		for (int i = 0; i <= infix.getSize(); i++) {
			if (infix[i] != ' ' && i != infix.getSize()) cur += infix[i];
			else {
				if (cur == "(") 
					operations.push(cur);
				else if (cur.isDigit())
					outstream += cur;
				else if (cur == ")") {
					while (!operations.isEmpty() && operations.getTop()->getValue() != "(")
						addOperationToStream();
					operations.pop();
				}
				else {
					if (cur != " ") {
						curOperationWeight = cur.getOperationWeight();
						while (!operations.isEmpty() && operations.getTop()->getWeight() >= curOperationWeight)
							addOperationToStream();
						operations.push(cur);
					}
				}
				cur = "";
			}
		}
		while (!operations.isEmpty())
			addOperationToStream();
	}

	strl calculate() { //calculating expression in postfix form
		double res = 0;
		strl cur;
		for (int i = 0; i < outstream.getSize(); i++) {
			if (outstream[i] != ' ') cur += outstream[i];
			else {
				if (cur.isDigit()) {
					if (cur == "pi") cur = 3.1415926535;
					else if (cur == "e") cur = 2.71828182846;
					operations.push(cur);
				}
				else if (cur.getOperationWeight() == 4) {
					res = cur.perform(operations.getTop()->getValue());
					operations.pop();
					operations.push(res);
				}
				else {
					res = cur.perform(operations.getTop()->getValue(), operations.getTop()->getNext()->getValue());
					operations.pop();
					operations.pop();
					operations.push(res);
				}
				cur = "";
			}
		}
		return operations.getTop()->getValue();
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

