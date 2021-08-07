#pragma once
#include <iostream>
#include <fstream>
#include "../../String Tokenizer/String Tokenizer/SToken.h"
#include "../../String Tokenizer/String Tokenizer/constants.h"
#include "../../String Tokenizer/String Tokenizer/Stokenizer.h"
using namespace std;
class FTokenizer
{
public:
    const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(const char* fname);
    SToken next_token();
    bool more();        //returns the current value of _more
    int pos();          //returns the value of _pos
    int block_pos();     //returns the value of _blockPos
    friend FTokenizer& operator >> (FTokenizer& f, SToken& t);
private:
    bool get_new_block(); //gets the new block from the file
    std::ifstream _f;       //file being tokenized
    STokenizer _stk;     //The STokenizer object to tokenize current block
    int _pos;           //Current position in the file
    int _blockPos;      //Current position in the current block
    bool _more;         //false if last token of the last block
                        //  has been processed and now we are at
                        //  the end of the last block.
};