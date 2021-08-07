#pragma once
#include "Operator.h"
class Relational : public Operator{
public:
	Relational(string name);
	string getName();	
	int typeOf() { return RELATIONAL; }
private:
	string _name;
};