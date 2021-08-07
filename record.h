#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Record{
public:
    Record();
    Record(int numfield);
    Record(const vector<string>& v);

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long _numrecord);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file
    vector<string> get_record() {
        vector<string> v;
        for (int i = 0; i < _num_fields; i++) {
            v.push_back(string(_record[i]));
        }
        return v;
    }
    friend ostream& operator<<(ostream& outs, const Record& r);

private:
    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 50;
    char _record[MAX_ROWS][MAX_COLS];
    int _num_fields;
    long record_number;
};
//utility functions
bool file_exists(const char filename[]);
void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);

inline bool file_exists(const char filename[]) {
    const bool debug = false;
    fstream ff;
    ff.open(filename,
        std::fstream::in | std::fstream::binary);
    if (ff.fail()) {
        if (debug) cout << "file_exists(): File does NOT exist: " << filename << endl;
        return false;
    }
    if (debug) cout << "file_exists(): File DOES exist: " << filename << endl;
    ff.close();
    return true;
}

inline void open_fileRW(fstream& f, const char filename[]) throw(char*) {
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)) {
        //create the file
        f.open(filename, std::fstream::out | std::fstream::binary);
        if (f.fail()) {
            cout << "file open (RW) failed: with out|" << filename << "]" << endl;
            throw("file RW failed  ");
        }
        else {
            if (debug) cout << "open_fileRW: file created successfully: " << filename << endl;
        }
    }
    else {
        f.open(filename,
            std::fstream::in | std::fstream::out | std::fstream::binary);
        if (f.fail()) {
            cout << "file open (RW) failed. [" << filename << "]" << endl;
            throw("file failed to open.");
        }
    }
}
inline void open_fileW(fstream& f, const char filename[]) {
    f.open(filename,
        std::fstream::out | std::fstream::binary);
    if (f.fail()) {
        cout << "file open failed: " << filename << endl;
        throw("file failed to open.");
    }
}