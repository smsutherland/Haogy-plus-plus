#pragma once
#include <string>

bool isWhitespace(char test);

bool isSymbol(char test);

void trim(std::string& str);

int getLineType(const std::string& line);