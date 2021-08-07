#pragma once
#include <iostream>
#include "Parser.h"
#include "table.h"
const bool DEBUG = false;
using namespace std;
class SQL{
public:
	SQL();
	~SQL();
	void run();
private:
	int _query_number;
	vector<string> _tables;
	Map<string, Table> _tables_map;
	Parser _parser;
	void run_batch(string filename);
	void run_command(string& command);
};

