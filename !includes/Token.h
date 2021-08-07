#pragma once
#include <iostream>
using namespace std;
enum Tokens { TOKEN, LPAREN, RPAREN, OPERATOR,WORD,RELATIONAL,LOGICAL};
class Token
{
public:
	Token();
	virtual int typeOf() { return TOKEN; }
	virtual void print();
private:
};
