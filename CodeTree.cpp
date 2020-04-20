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

CodeTree::LinkedList::LinkedList(){
    tail = nullptr;
    size = 0;
}

CodeTree::LinkedList::LinkedList(const LinkedList& other){
    copyVars(other);
}

CodeTree::LinkedList& CodeTree::LinkedList::operator=(const LinkedList& rhs){
    Clear();

    copyVars(rhs);
    return *this;
}

void CodeTree::LinkedList::copyVars(const LinkedList& other){
    tail = new Node(*other.tail);
    size = other.size;

    head = tail;
    Node* otherCurrentNode = other.tail;
    for(int i = 0; i < size; i++){
        head->updateNext(new Node(*otherCurrentNode->getNext()));
        head = head->getNext();
        otherCurrentNode = otherCurrentNode->getNext();
    }
}

CodeTree::LinkedList::~LinkedList(){
    Clear();
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::getTail(){
    return tail;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getTail() const{
    return tail;
}

void CodeTree::LinkedList::Addhead(const std::string& line){
    head->updateNext(new Node(line));
    head = head->getNext();
}

void CodeTree::LinkedList::Clear(){
    Node* currentNode = tail;
    for(int i = 0; i < size; i++){
        Node* nextNode = tail->getNext();
        delete currentNode;
        currentNode = nextNode;
    }
}

const std::string& CodeTree::LinkedList::operator[](unsigned int index) const{
    if(index >= size)
        throw std::out_of_range("This index is out of range for this code block");
    
    Node* currentNode = tail;
    for(int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    return currentNode->getLine();
}

std::string CodeTree::LinkedList::operator[](unsigned int index){
    if(index >= size)
        throw std::out_of_range("This index is out of range for this code block");
    
    Node* currentNode = tail;
    for(int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    return currentNode->getLine();
}

//Node functions

CodeTree::LinkedList::Node::Node(){
    line = "";
    next = nullptr;
    children = nullptr;
}

CodeTree::LinkedList::Node::Node(const std::string& line_){
    line = line_;
    next = nullptr;
    children = nullptr;
}

CodeTree::LinkedList::Node::Node(const std::string& line_, Node* next_){
    line = line_;
    next = next_;
    children = nullptr;
}

CodeTree::LinkedList::Node::Node(const Node& other){
    line = other.line;
    next = nullptr;
    children = nullptr;
}