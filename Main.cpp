#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> createProgram(std::ifstream& file);
void executeProgram(std::vector<std::string>& program);
void findFunctions(std::vector<std::string>& program, std::vector<function>& functionsOut);

int main(int argc, char** argv){
    std::string filename = "";
    if (argc == 1){
        std::cout << "__LANGUAGENAME__ interpreter by Sagan Sutherland" << std::endl;
        return 0;
    }

    filename = argv[1];
    std::ifstream progFile;
    progFile.open(filename);
    if(progFile.fail()){
        std::cout << "bad filename" << std::endl;
        return 0;
    }
    std::vector<std::string> program = createProgram(progFile);
    progFile.close();

    executeProgram(program);
    return 0;
}

std::vector<std::string> createProgram(std::ifstream& progFile){
    std::vector<std::string> program;
    if(progFile.is_open()){
        std::string line;
        while(std::getline(progFile, line)){
            if(line != "")
                program.push_back(line);
        }
    }
    return program;
}

void executeProgram(std::vector<std::string>& program){
    std::vector<std::string> types;
    types.push_back("boolean");
    types.push_back("int");
    types.push_back("float");
    types.push_back("char");
    types.push_back("string");

    std::vector<function> functions;
    findFunctions(program, functions);

    
}

void findFunctions(std::vector<std::string>& program, std::vector<function>& functionsOut){
    for(std::string line : program){
        if(!(line.rfind(" ", 0) || line.rfind("\t"))){
            
        }
    }
}