#include "CodeTree.h"

//CodeTree functions

CodeTree::CodeTree(){
    endList = startList = new LinkedList();
    size = 0;
}

CodeTree::CodeTree(const CodeTree& other){
    copyVars(other);
}

CodeTree& CodeTree::operator=(const CodeTree& rhs){
    delete startList;
    copyVars(rhs);
    return *this;
}

void CodeTree::copyVars(const CodeTree& other){
    size = other.size;
    startList = new LinkedList(*other.startList);
    updateEnd();
}

CodeTree::~CodeTree(){
    delete startList;
}

CodeTree::LinkedList& CodeTree::getStartList() const{
    return *startList;
}

unsigned int CodeTree::getSize() const{
    return size;
}

std::string CodeTree::addLine(std::string line){
    int lineType = getLineType(line);
    if(lineType == 0){
        endList->AddTail(line);
        size++;
    }else if(lineType > 0){
        endList->AddTail(line);
        endList->getTail()->giveChildren();
        endList = endList->getTail()->getChildren();
        size++;
    }else{
        for(int i = 0; i > lineType; i--){
            if(endList == startList)
                return "Too many closing brackets";
            endList = endList->getParent()->getContainer();
        }
    }
    return "";
}

void CodeTree::print(){
    startList->print(0);
}

//0= regular line
//1= start of an indent
//-1=end of an indent
//-n=end of n indents
int CodeTree::getLineType(std::string& line){
    if(line.find('{') == line.length() - 1)
        return 1;
    
    bool isDecriment = true;
    for(unsigned int i = 0; i < line.length(); i++){
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
        return endList = nullptr;
    
    endList = startList;
    while(true){
        if(endList->getTail() != nullptr){
            if(endList->getTail()->getChildren() != nullptr){
                endList = endList->getTail()->getChildren();
            }else{
                break;
            }
        }else{
            break;
        }
    }
    return endList;
}

CodeTree* CodeTree::createProgram(std::ifstream& progFile){
    CodeTree* program = new CodeTree();
    if(progFile.is_open()){
        std::string line;
        while(std::getline(progFile, line)){
            //TODO: remove comments
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

void CodeTree::trim(std::string& str){
    if (str == "")
        return;

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

CodeTree::Iterator CodeTree::begin() {
    return Iterator(startList->getHead());
}

CodeTree::Iterator CodeTree::end() {
    return Iterator();
}

//LinkedList functions

CodeTree::LinkedList::LinkedList(){
    head = tail = parent = nullptr;
    size = 0;
}

CodeTree::LinkedList::LinkedList(const LinkedList& other){
    copyVars(other);
}

CodeTree::LinkedList::LinkedList(Node* parent_){
    head = tail = nullptr;
    parent = parent_;
    size = 0;
}

CodeTree::LinkedList& CodeTree::LinkedList::operator=(const LinkedList& rhs){
    clear();

    copyVars(rhs);
    return *this;
}

void CodeTree::LinkedList::copyVars(const LinkedList& other){
    size = other.size;
    if(size > 0){
        head = new Node(*other.head);

        tail = head;
        Node* otherCurrentNode = other.head;
        for(int i = 0; i < size; i++){
            tail->updateNext(new Node(*otherCurrentNode->getNext()));
            tail = tail->getNext();
            otherCurrentNode = otherCurrentNode->getNext();
        }
    }else{
        tail = head = nullptr;
    }
    parent = other.parent;
}

CodeTree::LinkedList::~LinkedList(){
    clear();
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::getHead(){
    return head;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getHead() const{
    return head;
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::getTail(){
    return tail;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getTail() const{
    return tail;
}

CodeTree::LinkedList::Node* CodeTree::LinkedList::getParent(){
    return parent;
}

const CodeTree::LinkedList::Node* CodeTree::LinkedList::getParent() const{
    return parent;
}

void CodeTree::LinkedList::AddTail(const std::string& line){
    if(size > 0){
        tail->updateNext(new Node(line, this));
        tail = tail->getNext();
    }else{
        tail = head = new Node(line, this);
    }
    size++;
}

void CodeTree::LinkedList::clear(){
    delete head;
    size = 0;
    tail = head = parent = nullptr;
}

const std::string& CodeTree::LinkedList::operator[](unsigned int index) const{
    if(index >= size)
        throw std::out_of_range("This index is out of range for this code block");
    
    Node* currentNode = head;
    for(int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    return currentNode->getLine();
}

std::string CodeTree::LinkedList::operator[](unsigned int index){
    if(index >= size)
        throw std::out_of_range("This index is out of range for this code block");
    
    Node* currentNode = head;
    for(unsigned int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    return currentNode->getLine();
}

void CodeTree::LinkedList::print(unsigned int indent){
    Node* currentNode = head;
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
    for(unsigned int i = 0; i < indent; i++)
        std::cout << '\t';
    std::cout << line << std::endl;
    if(children != nullptr){
        children->print(indent + 1);
        for(int i = 0; i < indent; i++)
            std::cout << '\t';
        std::cout << '}' << std::endl;
    }
}

//Iterator functions

CodeTree::Iterator::Iterator(CodeTree::LinkedList::Node* startingNode) {
    currentNode = startingNode;
}

bool CodeTree::Iterator::moveForward() {
    if (currentNode->getNext() != nullptr) {
        currentNode = currentNode->getNext();
        return true;
    }
    return false;
}

bool CodeTree::Iterator::moveUp() {
    if (currentNode->getContainer()->getParent() != nullptr) {
        currentNode = currentNode->getContainer()->getParent();
        return true;
    }
    return false;
}

bool CodeTree::Iterator::moveDown() {
    if (currentNode->getChildren() != nullptr) {
        currentNode = currentNode->getChildren()->getHead();
        return true;
    }
    return false;
}

bool CodeTree::Iterator::nextLine() {
    if (currentNode->getLine() == "hii()") {
        std::cout << "";
    }
    if (moveDown()) {
        return true;
    }
    while (true) {
        if (moveForward()) {
            return true;
        }
        if (!moveUp()) {
            currentNode = nullptr;
            return false;
        }
    }
}

bool CodeTree::Iterator::blockHead() {
    return moveUp();
}

const std::string& CodeTree::Iterator::operator*() {
    return currentNode->getLine();
}