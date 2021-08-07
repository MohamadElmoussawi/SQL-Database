#include "Operator.h"
Operator::Operator(string type) : Token(){
	_type = type;
	//Checks for the operator presedence
	if (type == ">" || type == "<" || type == "=" 
		|| type == ">=" || type == "<=") {
		_prec = 3;
	}
	else if (type == "and") {
		_prec = 2;
	}
	else if (type == "or") {
		_prec = 1;
	}
	else if (type == "(") {
		_prec = 0;
	}
	else if (type == ")") {
		_prec = 4;
	}
}
int Operator::getPrecedence() {
	return _prec;
}
string Operator::getOperatorType() {
	return _type;
}