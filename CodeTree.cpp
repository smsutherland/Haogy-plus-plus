#include "CodeTree.h"

//CodeTree functions

CodeTree::CodeTree(){
    start = new LinkedList();
    size = 0;
}

CodeTree::CodeTree(std::string code){
    //Yet To Be Implimented
}

CodeTree::CodeTree(const CodeTree& other){
    start = new LinkedList(*other.start);
    size = other.size;
}

CodeTree& CodeTree::operator=(const CodeTree& rhs){
    delete start;
    start = new LinkedList(*rhs.start);
    size = rhs.size;
    return *this;
}

CodeTree::~CodeTree(){
    delete start;
}

CodeTree::LinkedList& CodeTree::startList() const{
    return *start;
}

unsigned int CodeTree::getSize() const{
    return size;
}

//LinkedList functions

//Node functions