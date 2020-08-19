#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

class CodeTree{
public:

    //block of code
    class LinkedList{
    public:

        //line of code
        class Node{
        private:
            std::string line;
            Node* next;
            LinkedList* children;
            LinkedList* container;

        public:
            //Constructor + Big 3
            Node();
            Node(const std::string& line_);
            Node(const std::string& line_, Node* next_);
            Node(const std::string& line_, LinkedList* container_);
            Node(const Node& other);
            Node& operator=(const Node& rhs);
            ~Node();

            //updating functions
            void updateNext(Node* newPointer);
            void updateLine(const std::string newLine);
            void setContainer(LinkedList* container_);
            bool giveChildren();

            //accessors
            const std::string& getLine() const;
            Node* getNext() const;
            LinkedList* getChildren() const;
            LinkedList* getContainer() const;

            void print(unsigned int indent);
        };

    private:
        Node* head;
        Node* tail;
        Node* parent;
        unsigned int size;

        void copyVars(const LinkedList& other);

    public:
        //Constructor + Big 3
        LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList(Node* parent_);
        LinkedList& operator=(const LinkedList& rhs);
        ~LinkedList();

        //Accessors
        Node* getHead();
        const Node* getHead() const;
        Node* getTail();
        const Node* getTail() const;
        Node* getParent();
        const Node* getParent() const;

        //Insertion
        void AddTail(const std::string& line);

        //Removal
        void clear();

        //Operators
        const std::string& operator[](unsigned int intex) const;
        std::string operator[](unsigned int index);

        void print(unsigned int indent);
    };

    class Iterator {
    private:
        LinkedList::Node* currentNode;

        bool moveForward();
        bool moveUp();
        bool moveDown();
    public:
        Iterator(LinkedList::Node* startingNode = nullptr);
        
        bool nextLine(); // Goes to the next line. Moves up a level if at the end of a block.
        bool blockHead(); //Goes to the head of the code block.

        const std::string& operator*();
        bool operator==(const Iterator other) { return currentNode == other.currentNode; }
        bool operator!=(const Iterator other) { return currentNode != other.currentNode; }
    };

private:
    LinkedList* startList;
    LinkedList* endList;
    unsigned int size;

    void copyVars(const CodeTree& other);
    static int getLineType(std::string& line);
    LinkedList* updateEnd();
    static void trim(std::string& str);

    //returns error messages with creating the CodeTree
    std::string addLine(std::string line);

public:
    CodeTree();
    CodeTree(const CodeTree& other);
    CodeTree& operator=(const CodeTree& rhs);
    ~CodeTree();

    LinkedList& getStartList() const;
    unsigned int getSize() const;


    void print();
    static CodeTree* createProgram(std::ifstream& progFile);

    Iterator begin();
    Iterator end();
};