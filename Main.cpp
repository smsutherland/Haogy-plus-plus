#include "CodeTree.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

CodeTree* createProgram(std::ifstream& file);
void trim(std::string& str);
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
    CodeTree* program = createProgram(progFile);
    progFile.close();

    std::cout << "Program:" << std::endl;
    program->print();
    delete program;
    //executeProgram(*program);
    return 0;
}

CodeTree* createProgram(std::ifstream& progFile){
    CodeTree* program = new CodeTree();
    if(progFile.is_open()){
        std::string line;
        while(std::getline(progFile, line)){
            //TODO: renove comments
            trim(line);
            if(line != ""){ //it's not all whitespace
                std::string errorMsg = program->addLine(line);
                if(errorMsg != ""){
                    std::cout << errorMsg << std::endl;
                    delete program;
                    program = nullptr;
                    break;
                }
            }
        }
    }
    return program;
}

void trim(std::string& str){
    std::string whitespace = " \t\n\v\f\r";
    int startPos = 0;
    for(; whitespace.find(str[startPos]) != std::string::npos && startPos < str.length(); startPos++){}
    int endPos = str.length() - 1;
    for(; whitespace.find(str[endPos]) != std::string::npos && endPos >= 0; endPos--){}
    int length = endPos - startPos + 1;
    if(length <= 0)
        str = "";
    else
        str = str.substr(startPos, length);
}

void executeProgram(CodeTree& program){
    std::vector<std::string> types;
    types.push_back("boolean");
    types.push_back("int");
    types.push_back("float");
    types.push_back("char");
    types.push_back("string");
}