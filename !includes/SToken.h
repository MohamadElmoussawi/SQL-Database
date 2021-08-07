#pragma once
#include <iostream>
using namespace std;
class SToken{
public:
    SToken();
    SToken(string str, int type);
    friend ostream& operator <<(ostream& outs, const SToken& t);
    int type();
    string type_string();
    string token_str();
private:
    string _token;
    int _type;
};
