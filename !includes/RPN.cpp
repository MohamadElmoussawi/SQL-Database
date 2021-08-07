#include "RPN.h"
#include "Shunting_Yard.h"
vector<long> RPN::get_records(Map<string, int>& fields, vector<MMap<string, long>>& indices) {
	Stack<Token*> tokens;
	while (!_postfix.Empty()) {
		//If we have a symbol here just push it to the tokens stack
		if (_postfix.Front()->typeOf() == WORD) {
			tokens.Push(_postfix.Pop());
		}
		//Relational operators
		else if (_postfix.Front()->typeOf() == RELATIONAL) {
			vector<long> recs;
			//If we have a relational operator we need to pop 2 things
			Symbol* condition = static_cast<Symbol*>(tokens.Top());
			//First popped item is the condition 
			tokens.Pop();
			//Second Popped item is the field name you are checking against
			Symbol* field_name = static_cast<Symbol*>(tokens.Top());
			tokens.Pop();
			MMap<string, long>::Iterator begin;
			MMap<string, long>::Iterator end;
			//Grab the name of the operator from the _postfix expression 
			string op = static_cast<Relational*>(_postfix.Pop())->getName();
			if (op == ">") {
				//Operatr > goes from upperbound to the end of the index
				begin = indices[fields[field_name->val()]].upper_bound(condition->val());
				end = indices[fields[field_name->val()]].end();
				while (begin != end) {
					//Iterate through and add to your vector of records
					//Using Union here saves us from having to use a for loop
					recs = getUnion(recs, (*begin).value_list);
					begin++;
				}
			}
			//Less then goes from beginning to lower bound
			else if (op == "<") {
				begin = indices[fields[field_name->val()]].begin();
				end = indices[fields[field_name->val()]].lower_bound(condition->val());
				while (begin != end) {
					recs = getUnion(recs, (*begin).value_list);
					begin++;
				}
			}
			//Operator >= goes from lower_bound of the condition (includes itself) to end
			else if (op == ">=") {
				begin = indices[fields[field_name->val()]].lower_bound(condition->val());
				end = indices[fields[field_name->val()]].end();

				while (begin != end) {
					recs = getUnion(recs, (*begin).value_list);
					begin++;
				}
			}
			//Operator <= goes from the beginning to the upper bound (icnludes itself)
			else if (op == "<=") {
				begin = indices[fields[field_name->val()]].begin();
				end = indices[fields[field_name->val()]].upper_bound(condition->val());
				while (begin != end) {
					recs = getUnion(recs, (*begin).value_list);
					begin++;
				}
			}
			//For the = comparison operator we just check if the index associated
			//With the field name contains the conditions we have 
			else if (op == "=") {
				if (indices[fields[field_name->val()]].contains(condition->val())) {
					
					recs = indices[fields[field_name->val()]][condition->val()];
				}
			}
			tokens.Push(new Logical(recs));
			//return recs;
			recs.clear();
		}
		else {
			//cout << endl << "LOGICAL operator" << endl;
			Logical* recs1 = static_cast<Logical*>(tokens.Top());
			tokens.Pop();
			//if (debug) cout << "Popping here ";
			Logical* recs2 = static_cast<Logical*>(tokens.Top());
			tokens.Pop();
			string type = static_cast<Logical*>(_postfix.Pop())->getName();
			//And do intersection
			if (type == "and") {
				vector<long> v = getIntersection(recs1->get_recs(), recs2->get_recs());
				tokens.Push(new Logical(v));
			}
			else if (type == "or") {
				//Or do union 
				vector<long> v = getUnion(recs1->get_recs(), recs2->get_recs());
				tokens.Push(new Logical(v));
			}
		}
	}
	return static_cast<Logical*>(tokens.Top())->get_recs();
}
RPN::RPN(Queue<Token*> postfix) {
	_postfix = postfix;
}