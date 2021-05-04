#include "Lexer.h"

std::vector<Token> tokenizeLine(std::string line) {
	std::vector<Token> tokens;
	std::stringstream lineStream(line);
	char currentChar;
	while (lineStream.get(currentChar)) {
		if (isWhitespace(currentChar))
			continue;

		Token nextToken;
		switch(currentChar) {
		case '+':
			nextToken = Token(OperatorPlus);
			break;
		case '-':
			nextToken = Token(OperatorMinus);
			break;
		case '*':
			nextToken = Token(OperatorTimes);
			break;
		case '/':
			nextToken = Token(OperatorDivide);
			break;
		case '(':
			nextToken = Token(LParen);
			break;
		case ')':
			nextToken = Token(RParen);
			break;
		default:
			std::string symbol = "";
			unsigned int symbolLength = 0;
			do {
				symbol += currentChar;
				symbolLength++;
				lineStream.get(currentChar);
			} while (isSymbol(currentChar));
			nextToken = Token(Symbol);
			void* newData = new char[symbolLength+1];
			memcpy(newData, symbol.c_str(), symbolLength+1);
			nextToken.setData(newData, symbolLength+1);
		}
		tokens.push_back(nextToken);
	}
	return tokens;
}
