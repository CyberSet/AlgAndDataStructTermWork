#include <fstream>
#include "strl.h"
#include "postfix.h"


using namespace std;

int main(){
	fstream input, output;
	input.open("input.txt",ios::in);
	output.open("output.txt", ios::out);
	strl infix;
	infix.input(input);
	infix.output(output);
	if (infix.isCorrectInfix(output)) {
		postfix pf(infix);
		output << "\nPostfix form: ";
		pf.getStream().output(output);
		output << "= " << pf.calculate();
	}
	output.close();
	input.close();
	return 0;
}