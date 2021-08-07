#pragma once
#include "Operator.h"
class RParen : public Operator
{
public:
	RParen();
	void print() {
		cout << ")";
	}
	int typeOf() { return RPAREN; }
private:
};

