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
		for (int i = 0; i < infix.getSize(); i++) {
			if (infix[i] != ' ') cur += infix[i];
			else {
				if (cur == "(") operations.push(cur);
				else if (cur.isDigit()) outstream += cur;
				else if (cur == ")") {
					while (operations.getTop().getSymbol() != "(") {
						outstream += operations.getTop().getSymbol();
						operations.pop();
					}
					operations.pop();
				}
				else {
					int curOperationWeight = cur.getOperationWeight();
					while (curOperationWeight >= operations.getTop().getWeight()) {
						outstream += operations.getTop().getSymbol();
						operations.pop();
					}
				}
				cur = "";
			}
		}
	}

	strl getStream() {
		return outstream;
	}
};
#endif // !POSTFIX_H

