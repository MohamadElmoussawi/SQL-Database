#include "Shunting_Yard.h"
void popUntilLeft(Stack<Operator*>& ops, Queue<Token*>& output);
ShuntingYard::ShuntingYard(Queue<Token*> infix) {
	_infix = infix;
	_postfix = postfix();
}
Queue<Token*>& ShuntingYard::postfix() {
	Stack<Operator*> operatorStack;
	//Go until the infix is empty 
	while (!_infix.Empty()) {
		//Store the front
		Token* temp = _infix.Front();
		//Pop the infix could be at the end
		_infix.Pop();
		//Number just push 
		if (temp->typeOf() == WORD) {
			_postfix.Push(temp);
		}
		//Operator then check precedence
		else if (temp->typeOf() == OPERATOR 
			|| temp->typeOf() == RELATIONAL 
			|| temp->typeOf() == LOGICAL) {
			Operator* theOperator = static_cast<Operator*>(temp);
			//theOperator->print();
			//If > precedence push on top
			if (operatorStack.Empty() || theOperator->getPrecedence() >
				operatorStack.Top()->getPrecedence()) {
				operatorStack.Push(theOperator);
			}
			//If less then or equal precedence pop then push to stack
			else {
				while (!operatorStack.Empty()
					&& theOperator->getPrecedence()
					<= operatorStack.Top()->getPrecedence()) {
					Token* temp2 = operatorStack.Top();
					operatorStack.Pop();
					_postfix.Push(temp2);
				}
				operatorStack.Push(static_cast<Operator*>(temp));
			}
		}
		//Left paren just push to stack
		else if (temp->typeOf() == LPAREN) {
			//cout << "Pushed left";
			operatorStack.Push(static_cast<LParen*>(temp));
		}
		//Right paren just pop until you get to the left paren then discard
		else if (temp->typeOf() == RPAREN) {
			popUntilLeft(operatorStack, _postfix);
		}
	}
	//Push all operators stil left in stack
	while (!operatorStack.Empty()) {
		Operator* op = operatorStack.Top();
		operatorStack.Pop();
		_postfix.Push(op);
	}
	//printTokens(_postfix);
	return _postfix;
}
void printTokens(Queue<Token*> toPrint) {
	while (!toPrint.Empty()) {
		toPrint.Front()->print();
		cout << " ";
		toPrint.Pop();
	}
}
void popUntilLeft(Stack<Operator*>& ops, Queue<Token*>& output) {
	bool done = false;
	while (!done) {
		if (ops.Top()->getOperatorType() == "(") {
			done = true;
			ops.Pop();
		}
		else {
			Operator* op = ops.Top();
			output.Push(op);
			ops.Pop();
			//cout << "Pushed ";
		}
	}
}
Queue<Token*> ShuntingYard::get_postfix() {
	return _postfix;
}
//Converts from vector of conditions to queue 
ShuntingYard::ShuntingYard(vector<string> conditions) {
	
	for (int i = 0; i < conditions.size(); i++) {
		if (conditions[i] == "<" || conditions[i] == ">" ||
			conditions[i] == "=" || conditions[i] == "<=" ||
			conditions[i] == ">=") {
			_infix.Push(new Relational(conditions[i]));
		}
		else if (conditions[i] == "and" || conditions[i] == "or") {
			_infix.Push(new Logical(conditions[i]));
		}
		else if (conditions[i] == "(") {
			_infix.Push(new LParen());

		}
		else if (conditions[i] == ")") {
			_infix.Push(new RParen());
		}
		else {
			_infix.Push(new Symbol(conditions[i]));
		}
	}
	_postfix = postfix();
}