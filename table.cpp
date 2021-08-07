#include "table.h"
Table::Table(const string& name, const vector<string> fields){
    //Open the file
    _name = name;
    string file_name = _name + ".bin";
    set_fields(fields);
    fstream output;
    //This is supposed to truncate the file if it already exists
    //Prevents files from overlapping if you have tables of the same name 
    output.open(_name + ".bin", std::ofstream::out | std::ofstream::trunc);
    output.close();
    open_fileRW(output, file_name.c_str());
    fstream field_names;
    //Fileds stored seperately = no risk of overloading the buffer
    string field_file = name + "_fields.txt";
    open_fileRW(field_names,field_file.c_str());
    //Get field names
    for (int i = 0; i < fields.size(); i++) {
        field_names << fields[i] << endl;
    }
    output.close();
    _serial = 0;
    _last_record = -1;
}
Table::Table(const string& name) {
    _name = name;
    fstream file;
    string tempField;
    vector<string> temp;
    open_fileRW(file, (_name + "_fields.txt").c_str());   
    //Grab all the field names 
    while (!file.eof()) {
        getline(file, tempField);
        temp.push_back(tempField);
    }
    //sets fields map
    //Also sets the fields vector of strings in that function
    set_fields(temp);   
    //Sets the indexes
    reindex();
    file.close();
    _serial = 0;
    _last_record = -1;
}
void Table::insert_into(vector<string> values){
    //OPen the file 
    fstream output;
    open_fileRW(output, (_name + ".bin").c_str());
    Record rec(values);
    _last_record = rec.write(output);
    //Deal with indicies here
    for (int i = 0; i < _indices.size(); i++) {
        //inserts into the indices 
        _indices[i][values[i]] += _last_record;   
    }
    output.close();
}
Table Table::select_records(vector<long> recordNumbers){
    fstream tempFile;
    Record r(_field_names.size());
    string tempName = _name + "_" + to_string(_serial++);
    open_fileRW(tempFile, (_name + ".bin").c_str());
    Table tempTable(tempName, _field_names);
    vector<string> tempRecord;
    //Goes through and selects all the records that are in the vector of recordnums
    for (int i = 0; i < recordNumbers.size(); i++) {
        r.read(tempFile, recordNumbers[i]);
        for (int j = 0; j < _field_names.size(); j++) {
            tempRecord.push_back(r.get_record()[_fields_map[_field_names[j]]]);
        }
        tempTable.insert_into(tempRecord);
        tempRecord.clear();
    }
    tempFile.close();
    return tempTable;
}

Table Table::select_all(){
    //Preparing to Read
    fstream f;
    open_fileRW(f, (_name + ".bin").c_str());
    //Create Temp Parameters
    string temp_name = _name;
    temp_name += "_";
    _serial++;
    temp_name += to_string(_serial);
    vector<string> temp_fields; 
    for (int i = 0; i < _field_names.size(); i++){
        temp_fields.push_back(_field_names[i]);
    }
    //Creates a temp table
    Table table(temp_name, temp_fields);
    Record r(_field_names.size());
    int record_num = 0;
    r.read(f, record_num);
    //Read from this table to the other table
    while (!f.eof()){
        record_num++;
        Record temp = r;
        r.read(f, record_num);
        table.insert_into(temp.get_record());
    }
    //Return the table 
    return table;
}
//Sets both the field names and the fields map 
//Also fills the indicies with blank Maps
void Table::set_fields(vector<string> fields){
    for (unsigned int i = 0; i < fields.size(); i++){
        _field_names.push_back(fields[i]);
        _fields_map[fields[i]] = i;
        //Fill with blank indices 
        _indices.push_back(MMap<string, long>());
    }
}
vector<string> Table::get_fields(){
    return _field_names;
}
void Table::reindex() {
    fstream file;
    Record r(_field_names.size());
    vector<string> temp;
    int recnumber = 0;
    open_fileRW(file, (_name + ".bin").c_str());
    r.read(file, recnumber);  
    while (!file.eof()) {
        temp = r.get_record();  
        for (int i = 0; i < _indices.size(); i++) {
            //Inserts the record into each index 
            _indices[i][temp[i]] += recnumber;
        }
        recnumber++;
        r.read(file, recnumber);   
    }
}
//SELECTS with conditions 
Table Table::select_conditions(vector<string> conditions) {
    bool debug = false;
    ShuntingYard s(conditions); 
    if (debug) printTokens(s.get_postfix());
    RPN r(s.get_postfix());
    vector<long> records = r.get_records(_fields_map, _indices);
    return select_records(records);
}
Table::Table() {
    //Left empty for map / multimap
}
//Combined Select Function 
Table Table::select(vector<string> fields, vector<long> recordNumbers){
    fstream file;
    Record r(fields.size());
    string tempName = _name + "_" + to_string(_serial++);
    vector<string> tempFieldNames = fields;
    open_fileRW(file, (_name + ".bin").c_str());
    Table tempTable(tempName, tempFieldNames);
    vector<string> tempRecords;
    //If no record numbers are specified 
    if (recordNumbers.empty()) {
        long recordnum = 0;
        r.read(file, recordnum);
        recordnum++;
        while (!file.eof()) {
            for (int j = 0; j < fields.size(); j++) {
                tempRecords.push_back(r.get_record()[_fields_map[fields[j]]]);
            }
            tempTable.insert_into(tempRecords);
            tempRecords.clear();
            r.read(file, recordnum++);
        }
    }
    //This can be replaced by my helper function get_records
    else {
        //If the recordNumbers are specified then go through and pick records
        for (int i = 0; i < recordNumbers.size(); i++) {
            r.read(file, recordNumbers[i]);
            for (int j = 0; j < fields.size(); j++) {
                tempRecords.push_back(r.get_record()[_fields_map[fields[j]]]);
            }
            tempTable.insert_into(tempRecords);
            tempRecords.clear();
        }
    }
    file.close();
    return tempTable;
}