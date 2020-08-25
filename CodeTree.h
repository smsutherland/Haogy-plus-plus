#pragma	once
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include "utility.h"

class CodeTree {
private:
	struct Node {
		std::string line;
		CodeTree* child;


		Node(std::string line_ = "");
		Node(const Node& other);
		Node& operator=(const Node& rhs);
		~Node();

		void giveChild();
		void resetChildsHeader();
	};

	class ArrayBlock {
	private:
		Node* nodeArray;
		unsigned int size;
		unsigned int capacity;

		void resetNodeChildrensHeaders();

		void setCapacity(unsigned int newCapacity);
		void doubleCapacity() { setCapacity(capacity * 2); }

	public:
		ArrayBlock();
		ArrayBlock(const ArrayBlock& other);
		ArrayBlock& operator=(const ArrayBlock& rhs);
		~ArrayBlock();

		void shrinkToFit() { setCapacity(size); }

		unsigned int getSize();

		Node& operator[](unsigned int index);
		void pushBack(std::string line);
		Node& back();
	};

public:
	class Iterator {
	private:
		std::stack<std::pair<CodeTree*, unsigned int>> history = std::stack<std::pair<CodeTree*, unsigned int>>();

	public:
		Iterator() {};
		Iterator(CodeTree* start);

		bool stepOut();
		bool stepOver();
		bool stepInto();

		std::string& operator*();
		unsigned int depth();

		bool operator==(const Iterator& rhs) { return history == rhs.history; };
		bool operator!=(const Iterator& rhs) { return history != rhs.history; };
	};
private:

	Node* header;
	ArrayBlock body;

	void setHeader(Node* newParent);
	Node* getHeader();
	void addLine(std::string line, std::stack<CodeTree*>& bottom);

public:
	CodeTree(Node* header_ = nullptr);

	static CodeTree* createTree(std::ifstream& progFile);

	void print(unsigned int indent = 0);

	Iterator begin();
	Iterator end();
};

