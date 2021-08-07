#include "Parser.h"
Parser::Parser(const char toparse[]) {
	createKeywordMap();
	make_table();
	get_tokens(toparse);
	setParseTree();
}
void Parser::make_table() {
	init_table(_table);
	//Commands
	mark_cell(0, _table, SELECT, 1);
	//If star or symbol is given 
	mark_cell(1, _table, STAR, 2);
	mark_cell(1, _table, SYMBOL, 2);
	
	//If from a coma or a symbol is selected
	mark_cell(2, _table, COMMA, 1);
	mark_cell(3, _table, SYMBOL, 4);
	mark_cell(2, _table, FROM, 3);
	mark_success(_table, 4);

	mark_cell(4, _table, WHERE, 5);
	mark_cell(5, _table, SYMBOL, 5);
	mark_success(_table, 5);

	mark_cell(0, _table, MAKE, 7);
	mark_cell(0, _table, CREATE, 7);
	mark_cell(7, _table, TABLE, 8);
	mark_cell(8, _table, SYMBOL, 9);
	mark_cell(9, _table, FIELD, 10);
	mark_cell(10, _table, SYMBOL, 11);
	mark_cell(11, _table, COMMA, 10);
	mark_success(_table, 11);
	//Inserting
	mark_cell(0, _table, INSERT, 12);
	mark_cell(12, _table, INTO, 13);
	mark_cell(13, _table, SYMBOL, 14);
	mark_cell(14, _table, VALUES, 15);
	mark_cell(15, _table, SYMBOL, 16);
	mark_cell(16, _table, COMMA, 15);
	mark_success(_table, 16);

	//Batch
	mark_cell(0, _table, BATCH, 20);
	mark_cell(20, _table, SYMBOL, 21);
	//THIS IS BECAUSE YOU PUT SELECT AS A FILE NAME!
	mark_cell(20, _table, SELECT, 21);
	//Dot for batch file
	mark_cell(21, _table, SYMBOL, 21);
	mark_cell(21, _table, DOT, 22);
	mark_cell(22, _table, SYMBOL, 23);
	mark_success(_table, 23);
}
void Parser::createKeywordMap() {
	_keywords.insert("select", SELECT);
	_keywords.insert("from", FROM);
	_keywords.insert("where", WHERE);
	_keywords.insert("*", STAR);
	_keywords.insert("insert", INSERT);
	_keywords.insert(",", COMMA);
	_keywords.insert("batch", BATCH);
	_keywords.insert("into", INTO);
	_keywords.insert("make", MAKE);
	_keywords.insert("create", CREATE);
	_keywords.insert("table", TABLE);
	_keywords.insert("fields", FIELD);
	_keywords.insert(".", DOT);
	_keywords.insert("values", VALUES);
	_keywords.insert("\"", QUOTE);
}
void Parser::get_tokens(const char toparse[]) {
	_stok.set_string(toparse);
	SToken temp;
	while (!_stok.done()) {
		_stok >> temp;
		//only spaces
		if (temp.type() == ALPHA || temp.type() == PUNC || temp.type() == NUM) {
			//Keep going if you see quotes until you see more quotes
			if (temp.token_str() == "\"") {
				_stok >> temp;
				string combined = "";
				while (temp.token_str() != "\"") {
					combined += temp.token_str();
					_stok >> temp;
				}
				_input.Push(SToken(combined,ALPHA));
				//If no quote is found then our parser will know 
			}
			else {
				_input.Push(temp);

			}
		}
	}
}
//Gets which Column of the adjacency matrix 
int Parser::getColumn(SToken t){
	if (_keywords.contains(Pair<string, int>(t.token_str()))) {
		return _keywords[t.token_str()];
	}
	else {
		return SYMBOL;
	}
}
//Sets the prase tree
void Parser::setParseTree() {
	SToken temp;
	int state = 0;
	while (!_input.Empty() && state != -1) {
		temp = _input.Pop();
		switch (state) {
			//All first words are commands
		case 0:
			_ptree.insert("command",temp.token_str());
			break;
		case 1:
			_ptree.insert("field", temp.token_str());
			break;
		case 3:
		case 13:
		case 8:
			_ptree.insert("table", temp.token_str());
			break;
		case 4:
			_ptree.insert("where", temp.token_str());
			break;
		case 5:
			_ptree.insert("condition", temp.token_str());
			break;
		case 20:
		case 21:
		case 22:
		case 10:
		case 15:
			_ptree.insert("values", temp.token_str());
			break;
		//All "helper" keywords go in trash
		default:
			_ptree.insert("trash", temp.token_str());
			break;
		}
		state = _table[state][getColumn(temp)];
	}
}
MMap<string, string>& Parser::parseTree() {
	return _ptree;
}
void Parser::set_string(const char toparse[]) {
	_ptree.clear();
	get_tokens(toparse);
	setParseTree();
}
Parser::Parser() {
	_ptree.clear();
	createKeywordMap();
	make_table();
}