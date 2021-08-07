#pragma once
#include <iostream>
#include <iomanip>
#include "constants.h"
using namespace std;
//Fill all cells of the array with -1
inline void init_table(int _table[][MAX_COLUMNS]);

//Mark this state (row) with a 1 (success)
inline void mark_success(int _table[][MAX_COLUMNS], int state);

//Mark this state (row) with a 0 (fail)
inline void mark_fail(int _table[][MAX_COLUMNS], int state);

//true if state is a success state
inline bool is_success(int _table[][MAX_COLUMNS], int state);

//Mark a range of cells in the array. 
inline void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state);

//Mark columns represented by the string columns[] for this row
inline void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state);

//Mark this row and column
inline void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state);

//This can realistically be used on a small table
inline void print_table(int _table[][MAX_COLUMNS]);

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
inline void show_string(char s[], int _pos);
void init_table(int _table[][MAX_COLUMNS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLUMNS; j++) {
			_table[i][j] = -1;
		}
	}
}
void mark_success(int _table[][MAX_COLUMNS], int state) {
	_table[state][0] = 1;
}
void mark_fail(int _table[][MAX_COLUMNS], int state) {
	_table[state][0] = 0;
}
bool is_success(int _table[][MAX_COLUMNS], int state) {
	return _table[state][0] == 1;
}
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state) {
	for (int i = from; i <= to; i++) {
		_table[row][i] = state;
	}
}
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state) {
	int i = 0;
	//Maybe correct idk go back later
	while (columns[i] != '\0') {
		_table[row][i] = state;
		i++;
	}
}
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state) {
	table[row][column] = state;
}
void show_string(char s[], int _pos) {
	int i = 0;
	while (s[i] != '\0') {
		i++;
		cout << s[i] << "\tpos " << _pos;
		cout << endl << setw(_pos) << "^";
	}
}
void print_table(int _table[][MAX_COLUMNS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLUMNS; j++) {
			cout << _table[i][j];
		}
	}
	cout << endl;
}