#pragma once
#include "Operator.h"
#include <vector>
class Logical : public Operator {
public:
	Logical(string name);
	Logical(vector<long>& recs);
	string getName();
	vector<long> get_recs();
	int typeOf() { return LOGICAL; }
private:
	string _name;
	vector<long> _recs;
};