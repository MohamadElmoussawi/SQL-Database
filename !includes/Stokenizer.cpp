#include "Stokenizer.h"
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];
STokenizer::STokenizer() {
	make_table(_table);
	_pos = 0;
}
STokenizer::STokenizer(const char str[]) {
	make_table(_table);
	strncpy_s(_buffer, str, MAX_BUFFER - 1);
	//_buffer[MAX_BUFFER] = '\0';
	_pos = 0;
}
void STokenizer::set_string(const char str[]) {
	strncpy_s(_buffer, str,MAX_BUFFER-1);
	//_buffer[MAX_BUFFER] = '\0';
	_pos = 0;
}
//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int start_state, string& token) {
	int lastSuccess = -1;
	bool failed = false;
	int col = _buffer[_pos];
	int state = _table[start_state][col];
	//While loop for extracting tokens
	while (!failed) {
		if (col < 0 || col  > MAX_COLUMNS) {
			//cout << "Stuck here";
			failed = true;
			_current = UNKNOWN;
			_pos++;
		}
		else if (is_success(_table, state)) {
			token += _buffer[_pos];
			_pos++;
			col = _buffer[_pos];
			lastSuccess = state;
			state = _table[state][col];
		}
		else if (state != -1) {
			int nextThing = _buffer[_pos + 1];
			int newState = _table[state][nextThing];
			if (is_success(_table,newState)) {
				token += _buffer[_pos];
				state = newState;
			}
			else {
				failed = true;
			}
		}
		if (_buffer[_pos] == '\0') {
			failed = true;
		}
		if (state == -1) {
			failed = true;
		}
	}
	//Match the success states correctly 
	if (col < 0) {
		_current = UNKNOWN;
	}
	else if (lastSuccess <= 10) {
		_current = ALPHA;
	}
	else if (lastSuccess <= 20) {
		_current = NUM;
	}
	else if (lastSuccess <= 30) {
		_current = PUNC;
	}
	else if (lastSuccess <= 40) {
		_current = SPACE;
	}
	return true;
}
void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
	init_table(_table);
	//Success States go here
	mark_success(_table, 0);
	mark_success(_table, 1);
	mark_success(_table, 11);
	mark_success(_table, 13);
	mark_success(_table, 21);
	mark_success(_table, 31);
	//States 1 - 10 alpha
	mark_cells(0, _table, 'a', 'z', 1);
	mark_cells(0, _table, 'A', 'Z', 1);
	mark_cells(1, _table, 'a', 'z', 1);
	mark_cells(1, _table, 'A', 'Z', 1);
	//States 11 - 20 numbers 
	mark_cells(0, _table, 48, 57, 11);
	mark_cells(11, _table, 48, 57, 11);
	mark_cells(11, _table, 46,46, 12);
	mark_cells(12, _table, 48, 57, 13);
	mark_cells(13, _table, 48, 57, 13);
	//States 21 - 30 punc 
	mark_cells(0, _table, 33, 47, 21);
	mark_cells(0, _table, 58, 64, 21);
	mark_cells(21, _table, 33, 47, 21);
	mark_cells(21, _table, 58, 64, 21);
	//States 31 - 40 spaces
	mark_cells(0, _table, 32, 32, 31);
	mark_cells(0, _table, 9, 11, 31);
	mark_cells(31, _table, 32, 32, 31);
	mark_cells(31, _table, 9, 11, 31);

	mark_cell(0, _table, ',', 23);
	mark_cell(0, _table, '"', 23);
	mark_cell(0, _table, '.', 23);
	mark_cell(0, _table, '_', 23);
	mark_success(_table, 23);
}
bool STokenizer::done() {
	return _buffer[_pos] == '\0';
}            
bool STokenizer::more() {
	return (_buffer[_pos-1] != '\0');
}
STokenizer& operator >> (STokenizer& s, SToken& t) {
	string theToken = "";
	s.get_token(0, theToken);
	int type = s._current;
	t = SToken(theToken,type);
	return s;
}