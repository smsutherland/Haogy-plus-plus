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
        Node* tail;
        Node* head;
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
        Node* getTail();
        const Node* getTail() const;
        Node* getHead();
        const Node* getHead() const;
        Node* getParent();
        const Node* getParent() const;

        //Insertion
        void Addhead(const std::string& line);

        //Removal
        void Clear();

        //Operators
        const std::string& operator[](unsigned int intex) const;
        std::string operator[](unsigned int index);

        void print(unsigned int indent);
    };

private:
    LinkedList* start;
    LinkedList* end;
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

    LinkedList& startList() const;
    unsigned int getSize() const;


    void print();
    static CodeTree* createProgram(std::ifstream& progFile);
};