#include "CodeTree.h"
#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv){
    std::string filename = "";
    if (argc == 1){
        std::cout << "Haogy++ interpreter by Sagan Sutherland" << std::endl;
        return 0;
    }

    filename = argv[1];
    std::ifstream progFile;
    progFile.open(filename);
    if(progFile.fail()){
        std::cout << "bad filename" << std::endl;
        return 0;
    }
    CodeTree<std::string>* program = createTree(progFile);
    progFile.close();

    if(program != nullptr){
        std::cout << "Program:" << std::endl;
        program->print();
    }
    delete program;

    std::string testLine = "abcde123 + asss/ ( a + b )";
    std::vector<Token> testTokens = tokenizeLine(testLine);
    for (Token t : testTokens) {
        std::cout << t.toString() << ", ";
    }
    std::cout << std::endl;

    return 0;
}