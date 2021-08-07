#include "FTokenizer.h"
FTokenizer::FTokenizer(const char* fname) {
	//cout << fname;
	_f.open(fname);
	STokenizer _stk;
	//get_new_block();
}
//returns the current value of _more
bool FTokenizer::more() {
	return !_f.eof();
}
//returns the pos in the file
int FTokenizer::pos() {
	return _pos;
}
//returns the value of _blockPos
int FTokenizer::block_pos() {
	return _blockPos;
}
//gets the new block from the file
bool FTokenizer::get_new_block() {
	//cout << "gETTINg next block";
	char temp[MAX_BUFFER] = "";
	_f.read(temp, MAX_BUFFER-1);
	//temp[MAX_BUFFER - 1] = '\0';
	_stk.set_string(temp);
	//cout << temp << endl;
	return true;
}
SToken FTokenizer::next_token() {
	SToken t;
	_stk >> t;
	if (_stk.done()) {
		//cout << "test";
		get_new_block();
	}
	return t;
}
FTokenizer& operator >> (FTokenizer& f, SToken& t) {
	t = f.next_token();
	return f;
}
