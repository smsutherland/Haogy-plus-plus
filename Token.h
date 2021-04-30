#pragma once

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
	
	Token();
	Token(const Token& other);
	Token& operator=(const Token& rhs);
	~Token();

	TokenType getType();
	void* getData();
	unsigned int getDataLength();
};
