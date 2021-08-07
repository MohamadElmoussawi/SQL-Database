#pragma once
#include <iostream>
#include "../../B+Tree/B+Tree//Map.h"
#include "../../B+Tree/B+Tree//MultiMap.h"
#include "../../String Tokenizer/String Tokenizer/Stokenizer.h"
#include "../../!includes/Stack And Queue/Stack And Queue/Queue.h"
using namespace std;
//Enum key words 
const enum {
	SELECT,STAR,FROM,SYMBOL,WHERE,TABLE,LAST,
	FIRST,CREATE,MAKE,FIELD,QUOTE,COMMA,VALUES,INTO,
	INSERT,BATCH,DOT
};

class Parser{
public:
	Parser(const char toparse[]);
	Parser();
	void get_tokens(const char input[]);
	int getColumn(SToken t);
	MMap<string, string>& parseTree();
	void createKeywordMap();
	void set_string(const char toparse[]);
private:
	STokenizer _stok;
	Queue<SToken> _input;
	int _table[MAX_ROWS][MAX_COLUMNS];
	MMap<string, string> _ptree;
	Map<string, int> _keywords;
	void make_table();
	void setParseTree();
};
