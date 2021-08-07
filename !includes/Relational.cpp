#include "Relational.h"
Relational::Relational(string name) : Operator(name) {
	_name = name;
}
string Relational::getName() {
	return _name;
}