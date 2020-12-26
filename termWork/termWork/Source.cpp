#include <fstream>
#include <iostream>
#include "strl.h"
#include "postfix.h"


using namespace std;

int main(){
	fstream input, output;
	input.open("input.txt",ios::in);
	output.open("output.txt", ios::out);
	strl infix;
	infix.input(input);
	postfix pf(infix);
	pf.getStream().output(output);
	output.close();
	input.close();
	return 0;
}