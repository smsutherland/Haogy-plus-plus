#include "Token.h"

Token::Token(TokenType type_, unsigned int dataLength_, void* data_) {
	type = type_;
	data = data_;
	dataLength = dataLength_;
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
	if (data != nullptr) {
		delete[] data;
	}
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

void Token::setType(TokenType type_) {
	type = type_;
}

void Token::setData(void* data_, unsigned int dataLength_) {
	data = data_;
	dataLength = dataLength_;
}

std::string Token::toString() {
	std::string returnStr;
	switch(type) {
	//case Integer:
	//case Float:
	case String:
		returnStr = "String: ";
		returnStr.append((char*)data);
		break;
	case OperatorPlus:
		returnStr = "Plus";
		break;
	case OperatorMinus:
		returnStr = "Minus";
		break;
	case OperatorTimes:
		returnStr = "Times";
		break;
	case OperatorDivide:
		returnStr = "Divide";
		break;
	case LParen:
		returnStr = "LParen";
		break;
	case RParen:
		returnStr = "RParen";
		break;
	case Symbol:
		returnStr = "Symbol: ";
		returnStr.append((char*)data);
		break;
	default:
		returnStr = "";
		break;
	}
	return returnStr;
}