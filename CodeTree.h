#pragma once
#include <string>

class CodeTree{
public:

    //block of code
    class LinkedList{
    public:

        //line of code
        class Node{
            std::string line;
            Node* next;
            LinkedList* children;

            //Constructor + Big 3
            Node();
            Node(const std::string& line_);
            Node(const std::string& line_, Node* next_);
            Node(const Node& other);
            Node& operator=(const Node& rhs);
            ~Node();

            //updating functions
            void updateNext(Node* newPointer);
            void updateLine(std::string newLine);

            //accessors
            std::string getLine() const;
            Node* getNext() const;
            LinkedList* getChildren() const;
        };
    private:
        Node* head;
        unsigned int size;

    public:
        //Constructor + Big 3
        LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& rhs);
        ~LinkedList();

        //Accessors
        Node* head();
        const Node* Head() const;

        //Insertion
        void Addhead(const std::string& line);

        //Removal
        void Clear();

        //Operators
        const std::string& operator[](unsigned int intex) const;
        std::string operator[](unsigned int index);
    };

private:
    LinkedList* start;
    unsigned int size;

public:
    CodeTree();
    CodeTree(std::string code);
    CodeTree(const CodeTree& other);
    CodeTree& operator=(const CodeTree& rhs);
    ~CodeTree();

    LinkedList& startList() const;
    unsigned int getSize() const;
};