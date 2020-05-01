#include "CodeTree.h"

//CodeTree functions

CodeTree::CodeTree(){
    end = start = new LinkedList();
    size = 0;
}

CodeTree::CodeTree(const CodeTree& other){
    copyVars(other);
}

CodeTree& CodeTree::operator=(const CodeTree& rhs){
    delete start;
    copyVars(rhs);
    return *this;
}

void CodeTree::copyVars(const CodeTree& other){
    size = other.size;
    start = new LinkedList(*other.start);
    updateEnd();
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

std::string CodeTree::addLine(std::string line){
    int lineType = getLineType(line);
    if(lineType == 0){
        end->Addhead(line);
        size++;
    }else if(lineType > 0){
        end->Addhead(line);
        end->getHead()->giveChildren();
        end = end->getHead()->getChildren();
        size++;
    }else{
        for(int i = 0; i > lineType; i--){
            if(end == start)
                return "Too many closing brackets";
            end = end->getParent()->getContainer();
        }
    }
    return "";
}

void CodeTree::print(){
    start->print(0);
}

//0= regular line
//1= start of an indent
//-1=end of an indent
//-n=end of n indents
int CodeTree::getLineType(std::string& line){
    if(line.find('{') == line.length() - 1)
        return 1;
    
    bool isDecriment = true;
    for(int i = 0; i < line.length(); i++){
        isDecriment = (line[i] == '}');
        if(!isDecriment)
            break;
    }
    if(isDecriment)
        return -1*(int)line.length();
    return 0;
}

CodeTree::LinkedList* CodeTree::updateEnd(){
    if(size == 0)
        return end = nullptr;
    
    end = start;
    while(true){
        if(end->getHead() != nullptr){
            if(end->getHead()->getChildren() != nullptr){
                end = end->getHead()->getChildren();
            }else{
                break;
            }
        }else{
            break;
        }
    }
    return end;
}

//LinkedList functions

CodeTree::LinkedList::LinkedList(){
    tail = head = parent = nullptr;
    size = 0;
}

CodeTree::LinkedList::LinkedList(const LinkedList& other){
    copyVars(other);
}

CodeTree::LinkedList::LinkedList(Node* parent_){
    tail = head = nullptr;
    parent = parent_;
    size = 0;
}

CodeTree::LinkedList& CodeTree::LinkedList::operator=(const LinkedList& rhs){
    Clear();

    copyVars(rhs);
    return *this;
}

void CodeTree::LinkedList::copyVars(const LinkedList& other){
    size = other.size;
    if(size > 0){
        tail = new Node(*other.tail);

        head = tail;
        Node* otherCurrentNode = other.tail;
        for(int i = 0; i < size; i++){
            head->updateNext(new Node(*otherCurrentNode->getNext()));
            head = head->getNext();
            otherCurrentNode = otherCurrentNode->getNext();
        }
    }else{
        head = tail = nullptr;
    }
    parent = other.parent;
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

CodeTree::LinkedList::Node* CodeTree::LinkedList::getHead(){
    return head;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getHead() const{
    return head;
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::getParent(){
    return parent;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getParent() const{
    return parent;
}

void CodeTree::LinkedList::Addhead(const std::string& line){
    if(size > 0){
        head->updateNext(new Node(line, this));
        head = head->getNext();
    }else{
        head = tail = new Node(line, this);
    }
    size++;
}

void CodeTree::LinkedList::Clear(){
    Node* currentNode = tail;
    for(int i = 0; i < size; i++){
        Node* nextNode = tail->getNext();
        delete currentNode;
        currentNode = nextNode;
    }
    size = 0;
    head = tail = parent = nullptr;
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

void CodeTree::LinkedList::print(unsigned int indent){
    Node* currentNode = tail;
    while(currentNode != nullptr){
        currentNode->print(indent);
        currentNode = currentNode->getNext();
    }
}

//Node functions

CodeTree::LinkedList::Node::Node(){
    line = "";
    next = nullptr;
    children = container = nullptr;
}

CodeTree::LinkedList::Node::Node(const std::string& line_){
    line = line_;
    next = nullptr;
    children = container = nullptr;
}

CodeTree::LinkedList::Node::Node(const std::string& line_, Node* next_){
    line = line_;
    next = next_;
    children = container = nullptr;
}

CodeTree::LinkedList::Node::Node(const std::string& line_, LinkedList* container_){
    line = line_;
    next = nullptr;
    children = nullptr;
    container = container_;
}

CodeTree::LinkedList::Node::~Node(){
    delete children;
    delete next;
}

CodeTree::LinkedList::Node::Node(const Node& other){
    line = other.line;
    next = other.next;
    container = other.container;
    children = other.children;
}

void CodeTree::LinkedList::Node::updateNext(Node* newPointer){
    next = newPointer;
}

void CodeTree::LinkedList::Node::updateLine(const std::string newLine){
    line = newLine;
}

void CodeTree::LinkedList::Node::setContainer(LinkedList* container_){
    container = container_;
}

bool CodeTree::LinkedList::Node::giveChildren(){
    if(children == nullptr){
        children = new LinkedList(this);
    }else{
        return false;
    }
    return true;
}

const std::string& CodeTree::LinkedList::Node::getLine() const{
    return line;
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::Node::getNext() const{
    return next;
}

CodeTree::LinkedList* CodeTree::LinkedList::Node::getChildren() const{
    return children;
}

CodeTree::LinkedList* CodeTree::LinkedList::Node::getContainer() const{
    return container;
}

void CodeTree::LinkedList::Node::print(unsigned int indent){
    for(int i = 0; i < indent; i++)
        std::cout << '\t';
    std::cout << line << std::endl;
    if(children != nullptr){
        children->print(indent + 1);
        for(int i = 0; i < indent; i++)
            std::cout << '\t';
            std::cout << '}' << std::endl;
    }
}