#include "Symbol.h"
int Symbol::typeOf() {
	return WORD;
}

Symbol::Symbol(string val) {
	_val = val;
}
string Symbol::val() {
	return _val;
}