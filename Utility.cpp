#include "utility.h"

bool isWhitespace(char test) {
    std::string whitespace = " \t\n\v\f\r";
    return whitespace.find(test) != std::string::npos;
}

void trim(std::string& str) {
    if (str == "")
        return;

    unsigned int startPos = 0;
    for (; isWhitespace(str[startPos]) && startPos < str.length(); startPos++) {}

    unsigned int endPos = str.length() - 1;
    for (; isWhitespace(str[endPos]) && endPos >= 0; endPos--) {}
    
    int length = endPos - startPos + 1;
    if (length <= 0)
        str = "";
    else
        str = str.substr(startPos, length);
}

int getLineType(const std::string& line) {
    if (line.find('{') == line.length() - 1)
        return 1;

    bool isDecriment = line.find('}') != std::string::npos;
    if (isDecriment)
        return -1 * (int)line.length();
    return 0;
}