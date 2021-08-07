#pragma once
#include "Operator.h"
class LParen : public Operator
{
public:
	LParen();
	void print() {
		cout << "(";
	}
	int typeOf() { return LPAREN; }
private:
};

