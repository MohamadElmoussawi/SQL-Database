#pragma once
#include "..\..\!includes\Stack And Queue\Stack And Queue\Stack.h"
#include "..\..\!includes\Stack And Queue\Stack And Queue\Queue.h"
#include "Token.h"
#include "Operator.h"
#include "LParen.h"
#include "RParen.h"
#include "Symbol.h"
#include "Logical.h"
#include "Relational.h"
void printTokens(Queue<Token*> toPrint);
class ShuntingYard
{
public:
	ShuntingYard(Queue<Token*> infix);
	ShuntingYard(vector<string> conditions);
	Queue<Token*>& postfix();
	Queue<Token*> get_postfix();
private:
	Queue<Token*> _infix;
	Queue<Token*> _postfix;
};