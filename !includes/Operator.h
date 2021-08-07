#pragma once
#include "Token.h"
class Operator : public Token{
public:
	Operator(string type);
	void print() {
		cout << _type;
	}
	int typeOf() { return OPERATOR; }
	int getPrecedence();
	string getOperatorType();
private:
	string _type;
	int _prec;
};

