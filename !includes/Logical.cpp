#include "Logical.h"
Logical::Logical(string name) : Operator(name) {
	_name = name;
}
string Logical::getName() {
	return _name;
}
vector<long> Logical::get_recs() {
	return _recs;
}
Logical::Logical(vector<long>& recs) : Operator("records") {
	_recs = recs;
}