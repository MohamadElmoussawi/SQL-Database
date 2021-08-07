#pragma once
#include "Token.h"
class Symbol : public Token
{
public:
	Symbol(string val);
	void print() { cout << _val; }
	string val();
	int typeOf();
private:
	string _val;
};

