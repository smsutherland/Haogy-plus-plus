#include "Token.h"
#include <string.h>

Token::Token() {
	type = None;
	data = nullptr;
	dataLength = 0;
}

Token::Token(const Token& other) {
	copyVars(other);
}

Token& Token::operator=(const Token& rhs) {
	clear();
	copyVars(rhs);
	return *this;
}

Token::~Token() {
	clear();
}

void Token::copyVars(const Token& other) {
	type = other.type;
	dataLength = other.dataLength;
	data = new unsigned char[dataLength];
	memcpy(data, other.data, dataLength);
}

void Token::clear() {
	delete data;
}

TokenType Token::getType() {
	return type;
}

void* Token::getData() {
	return data;
}

unsigned int Token::getDataLength() {
	return dataLength;
}