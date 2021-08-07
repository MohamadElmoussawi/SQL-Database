#include "SQL.h"
//Runs a batch file keeps running until EOF
void SQL::run_batch(string filename) {
	string command;
	fstream file;
	file.open(filename.c_str());
	//cout << endl << "Running " << filename << endl;
	if (file.fail()) {
		cout << "FAILED TO OPEN BATCH FILE" << endl;
	}
	else {
		while (!file.eof()) {
			getline(file, command);
			if (command != "\n" && command[0] != '/' && command.size() != 0) {
				run_command(command);
			}
			else {
				//Print the command if it is a new line or starts with a /
				cout << command << endl;
			}
		}
	}
	cout << endl << "----------------END OF BATCH FILE---------------------" << endl;
}
void SQL::run_command(string& command) {
	cout << "[" << _query_number << "]" << command << endl ;
	//Create a parser with the command
	_parser.set_string(command.c_str());
	//Get the parse tree
	MMap<string, string> ptree = _parser.parseTree();
	string command_str = ptree["command"][0];
	if(DEBUG) cout << endl << ptree<< endl;
	if (command_str == "make" || command_str == "create") {
		string table_name = ptree["table"][0];
		//Push to the tables list
		_tables.push_back(table_name);
		//Push to the map of tables 
		int map_index = _tables.size() - 1;
		_tables_map[_tables[map_index]] = Table(_tables[map_index],ptree["values"]);
		cout << endl << "sql::run_command: create table " << ptree["values"]  << endl;
		cout << "Table " << table_name << " created. fields " << ptree["values"] << endl;
	}
	else if (command_str == "insert") {
		if (!ptree["table"].empty()) {
			string table_name = ptree["table"][0];
			_tables_map[table_name].insert_into(ptree["values"]);
			cout << endl <<  "Inserted into table: " << table_name << endl << endl;
		}
		else {
			cout << endl << "ERROR: Table does not EXIST" << endl;
		}
	}
	else if (command_str == "select") {
		//Check if the table exists before crashing
		string table_name = ptree["table"][0];
		if (_tables_map.contains(table_name)) {
			//We have conditions and we are not star
			if (ptree.contains("where") && ptree["field"][0] != "*") {
				//cout << "selecting conditional " << endl;
				
				cout << endl << _tables_map[table_name].select(ptree["field"]).select_conditions(ptree["condition"]);
				cout << endl;
			}
			//We are star 
			else if (ptree["field"][0] == "*") {
				//cout << "We are STAR";
				//Star with conditions
				if (ptree.contains("where")) {
					//cout << "All fields select conditional" << endl;
					cout << endl << _tables_map[table_name].select_conditions(ptree["condition"]);
					cout << endl;
				}
				//Star without conidtions = select_all
				else {
					//cout << "All fields selected" << endl;
					cout << endl << _tables_map[table_name].select_all();
					cout << endl;
				}
			}
			//Not star no conditions just fields
			else {
				//cout << "selecting non conditional" << endl;
				cout << endl <<_tables_map[table_name].select(ptree["conditions"]);
				cout << endl;
			}	
		}
		//Table DNE
		else {
			cout << endl << "Error table Does Not Exist" << endl;
		}
	}
	//If batch run the batch filee
	else if (command_str == "batch") {
		string filename = "";
		//Combine all the parts of the batch files name
		for (int i = 0; i < ptree["values"].size(); i++) {
			filename += ptree["values"][i];
		}
		run_batch(filename);
	}
	else {
		cout << "ERROR: INVALID COMMAND" << endl;
	}
	_query_number++;

}
//Very simple wwhile loop
void SQL::run() {
	string command = "";
	cout << "> ";
	getline(cin, command);
	while (command != "exit") {
		run_command(command);
		cout << "> ";
		getline(cin, command);
	}
}
//Loads tables from saved-tables
SQL::SQL() {
	_query_number = 0;
	fstream input;
	input.open("_saved-tables.txt");
	string temp;
	cout << "Available Tables: " << endl ;
	if (!input.fail()) {
		while (!input.eof()) {
			cout << temp << endl;
			getline(input, temp);
			_tables.push_back(temp);
			_tables_map.insert(temp, Table(temp));
		}
	}
}
//Saves tables 
SQL::~SQL() {
	fstream output;
	output.open("_saved-tables.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < _tables.size(); i++) {
		output << _tables[i] << endl;
	}
}