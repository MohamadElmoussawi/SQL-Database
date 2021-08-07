#include "SToken.h"
#include "constants.h"
SToken::SToken() {
	_token = "";
	_type = NULL;
}
SToken::SToken(string str, int type) {
	_token = str;
	_type = type;
}
int SToken::type() {
	return _type;
}
string SToken::token_str() {
	return _token;
}
string SToken::type_string() {
	switch (_type) {
	case ALPHA:
		return "ALPHA";
		break;
	case NUM:
		return "NUM";
		break;
	case PUNC:
		return "PUNC";
		break;
	case SPACE:
		return "SPACE";
		break;
	case UNKNOWN:
		return "UNKNOWN";
		break;
	default:
		return "NULL";
	}
}
ostream& operator <<(ostream& outs, const SToken& t) {
	cout << t._token;
	return outs;
}