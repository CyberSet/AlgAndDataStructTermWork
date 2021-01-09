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
		bool ableToUnaryMinus = true; // should we expect a unary minus, at start we are waiting for single unary minus
		for (int i = 0; i <= infix.getSize(); i++) {
			if (infix[i] != ' ' && i != infix.getSize()) cur += infix[i];
			else {
				if (cur == "(") { // if current string is left parentheses push them to stack
					operations.push(cur);
					ableToUnaryMinus = true; // be prepared for unary minus
				}
				else if (cur.isDigit()) { // if current string is number add them to stream
					outstream += cur;
					ableToUnaryMinus = false;// exclude unary minus possibility
				}
				else if (cur == ")") { // if current string is end parentheses push all operations between left and end parenthesis to stream
					while (!operations.isEmpty() && operations.getTop()->getValue() != "(")
						addOperationToStream();
					operations.pop();
					ableToUnaryMinus = false; // exclude unary minus possibility
				}
				else {
					if (cur == "-" && ableToUnaryMinus) { // if current string is minus and we are ready to unary minus push multiplying to oepration stack and -1 to stream
						operations.push("*");
						outstream += "-1";
						ableToUnaryMinus = false; // exclude unary minus possibility
					}
					else{
						curOperationWeight = cur.getOperationWeight(); // getting current operation weight to correct order
						while (!operations.isEmpty() && operations.getTop()->getValue().getOperationWeight() >= curOperationWeight)
							addOperationToStream(); // while current operation is weaker than stack top push it to stream
						operations.push(cur);
						ableToUnaryMinus = true; // be prepared for unary minus
					}
				}
				cur = "";
			}
		}
		while (!operations.isEmpty()) // push remaining operations to stream
			addOperationToStream();
	}

	double calculate() { //calculating expression in postfix form
		double res = 0;
		strl cur;
		for (int i = 0; i < outstream.getSize(); i++) {
			if (outstream[i] != ' ') cur += outstream[i];
			else {
				if (cur.isDigit()) { // if current string is number push to operand stack
					if (cur == "pi") operands.push(PI);
					else if (cur == "e") operands.push(E);
					else operands.push(atof(cur.getStream()));
				}
				else if (cur.getOperationWeight() == oneArgumentOperationWeight) { // if current string is operation with one argument carrying outh them with top number in operand`s stack
					res = cur.perform(operands.getTop()->getValue()); // calculating
					operands.pop(); // remove used number from stack
					operands.push(res);// push result to stack
				}
				else {
					res = cur.perform(operands.getTop()->getValue(), operands.getTop()->getNext()->getValue()); // if current string is operation with two arguments carrying outh them with 2 top numbers in operand`s stack
					operands.pop(); // calculating
					operands.pop(); // remove used numbers from stack
					operands.push(res); // push result to stack
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

