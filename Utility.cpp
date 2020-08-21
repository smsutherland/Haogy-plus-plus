#include "utility.h"

void trim(std::string& str) {
    if (str == "")
        return;
    std::string whitespace = " \t\n\v\f\r";

    unsigned int startPos = 0;
    for (; whitespace.find(str[startPos]) != std::string::npos && startPos < str.length(); startPos++) {}

    unsigned int endPos = str.length() - 1;
    for (; whitespace.find(str[endPos]) != std::string::npos && endPos >= 0; endPos--) {}
    
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