#pragma once

#include <string>

enum TokenType {
	None,
	Integer,
	Float,
	String,
	OperatorPlus,
	OperatorMinus,
	OperatorTimes,
	OperatorDivide,
	LParen,
	RParen,
	Symbol
};

class Token {
private:
	TokenType type;
	void* data;
	unsigned int dataLength;

	void copyVars(const Token& other);
	void clear();

public:
	
	Token(TokenType type_ = None, unsigned int dataLength_ = 0, void* data_ = nullptr);
	Token(const Token& other);
	Token& operator=(const Token& rhs);
	~Token();

	TokenType getType();
	void* getData();
	unsigned int getDataLength();

	void setType(TokenType type_);
	void setData(void* data_, unsigned int dataLength_);

	std::string toString();
};
