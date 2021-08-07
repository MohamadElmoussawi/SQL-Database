#include "record.h"
#include <iomanip>
//Write to a record
long Record::write(fstream& outs) {
    outs.seekg(0, outs.end);
    long pos = outs.tellp();  
    outs.write(&_record[0][0], sizeof(_record));
    return pos / sizeof(_record);  
}
//Read a record
long Record::read(fstream& ins, long _numrecord) {
    long pos = _numrecord * sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    ins.read(&_record[0][0], sizeof(_record));
    return ins.gcount();
}
//Print record
ostream& operator<<(ostream& outs, const Record& r){
    for (int i = 0; i < r._num_fields; i++){
        outs << right << setw(16) << r._record[i];
    }
    return outs;
}
Record::Record() {
    _record[0][0] = '\0';
    _num_fields = 0;
}
//Replacement for empy CTOR
Record::Record(int numfield = 0) {
    _record[0][0] = '\0';
    _num_fields = numfield;
}
Record::Record(const vector<string>& v) {
    //Initiate the rows to null
    for (int i = 0; i < MAX_ROWS; i++) {
        _record[i][0] = '\0';
    }
    //Insert the fields 1 by 1 
    for (int i = 0; i < v.size(); i++) {
        strcpy_s(_record[i], v[i].c_str());
    }
    _num_fields = v.size();
}

