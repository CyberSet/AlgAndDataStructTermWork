#pragma once
#ifndef POSTFIX_H
#include "stack.h"
#include "strl.h"
#define POSTFIX_H
class postfix {
private:
	stack operations;
	strl outstream;
public:
	postfix(strl infix) {
		strl cur;
		int curOperationWeight = 0;
		for (int i = 0; i <= infix.getSize(); i++) {
			if (infix[i] != ' ' && i != infix.getSize()) cur += infix[i];
			else {
				if (cur == "(") operations.push(cur);
				else if (cur.isDigit()) 
					outstream += cur;
				else if (cur == ")") {
					while (operations.getTop().getSymbol() != "(")
						addOperationToStream();
					operations.pop();
				}
				else {
					curOperationWeight = cur.getOperationWeight();
					while (!operations.isEmpty() && operations.getTop().getWeight() >= curOperationWeight)
						addOperationToStream();
					operations.push(cur);
				}
				cur = "";
			}
		}
		while (!operations.isEmpty())
			addOperationToStream();
	}

	strl getStream() {
		return outstream;
	}

	void addOperationToStream() {
		outstream += operations.getTop().getSymbol();
		operations.pop();
	}
};
#endif // !POSTFIX_H

