#include "CodeTree.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void executeProgram(CodeTree& program);

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
    CodeTree* program = CodeTree::createProgram(progFile);
    progFile.close();

    if(program != nullptr){
        std::cout << "Program:" << std::endl;
        program->print();
        delete program;
    }
    //executeProgram(*program);
    return 0;
}

void executeProgram(CodeTree& program){
    std::vector<std::string> types;
    types.push_back("boolean");
    types.push_back("int");
    types.push_back("float");
    types.push_back("char");
    types.push_back("string");
}