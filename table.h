#pragma once
#include "record.h"
#include "../../B+Tree/B+Tree/Multimap.h"
#include "../../B+Tree/B+Tree/Map.h"
#include "../../SQL Shuntingy Yard RPN/SQL Shuntingy Yard RPN/RPN.h"
#include "../../SQL Shuntingy Yard RPN/SQL Shuntingy Yard RPN/Shunting_Yard.h"
#include <iomanip>
class Table{
public:
    //Table CTOR takes name and vector of fields (new table)
    Table(const string& name, const vector<string> fields);
    //Loads a table with just name 
    Table(const string& name);
    //Empty table CTOR for passing into a MMap
    Table(); 
    //Inserts to Table
    void insert_into(vector<string> values);
    //Selects records with recordnumbers 
    Table select_records(vector<long> records);
    //Selects all records
    Table select_all();
    //Selects fields and recordnumbers (general select)
    Table select(vector<string> fields, vector<long> recordNumbers = vector<long>());
    //Selects with conditions (uses RPN and SHunting Yard)
    Table select_conditions(vector<string> conditions);
    void set_fields(vector<string> fields);
    vector<string> get_fields();
    void reindex();
    //Prints the Table
    friend ostream& operator<<(ostream& outs, const Table& print_me) {
        cout << "Table: " << print_me._name 
            << " Total Records: " << print_me._last_record+1 << endl << endl;
        cout << "Record";
        for (int i = 0; i < print_me._field_names.size(); i++) {
            cout << right << setw(16) <<  print_me._field_names[i];
        }
        cout << endl << endl;
        fstream output;
        open_fileRW(output, (print_me._name + ".bin").c_str());
        Record r(print_me._field_names.size());
        int numrecord = 0;
        r.read(output, numrecord);
        while (!output.eof()) {
            cout << setw(6) << right << numrecord;
            cout << r << endl;
            numrecord++;
            r.read(output, numrecord);
        }
        return outs;
    }

private:
    string _name;
    vector<string> _field_names;
    Map<string, int> _fields_map;
    int _serial;
    vector<MMap<string, long> > _indices;
    long _last_record;
};

