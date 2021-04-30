#pragma	once
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include "utility.h"

template <typename T>
class CodeTree {
private:
	struct Node {
		T line;
		CodeTree* child;


		Node(T line_ = "");
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
		void pushBack(T line);
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

		T& operator*();
		unsigned int depth();

		bool operator==(const Iterator& rhs) { return history == rhs.history; };
		bool operator!=(const Iterator& rhs) { return history != rhs.history; };
	};
private:

	Node* header;
	ArrayBlock body;

	void setHeader(Node* newParent);
	Node* getHeader();

public:
	CodeTree(Node* header_ = nullptr);

	void addLine(T line, std::stack<CodeTree*>& bottom);

	void print(unsigned int indent = 0);

	Iterator begin();
	Iterator end();
};

/*
CodeTree Functions
*/

template <typename T>
CodeTree<T>::CodeTree(Node* header_) {
	header = header_;
}

template <typename T>
void CodeTree<T>::setHeader(Node* newParent) {
	header = newParent;
}

template <typename T>
typename CodeTree<T>::Node* CodeTree<T>::getHeader() {
	return header;
}

template <typename T>
void CodeTree<T>::addLine(T line, std::stack<CodeTree<T>*>& bottom) {
	int lineType = getLineType(line);
	if (lineType == 0) {
		body.pushBack(line);
	}
	else if (lineType > 0) {
		body.pushBack(line);
		body.back().giveChild();
		bottom.push(body.back().child);
	}
	else {
		for (int i = 0; i < -lineType; i++) {
			if (!bottom.empty()) {
				bottom.top()->body.shrinkToFit();
				bottom.pop();
			}
			else
				break;
		}
	}
}

template <typename T>
void CodeTree<T>::print(unsigned int indent) {
	for (auto itr = this->begin(); itr != this->end(); itr.stepInto()) {
		for (unsigned int i = 0; i < itr.depth(); i++)
			std::cout << "\t";
		std::cout << *itr << std::endl;
	}
}

template <typename T>
typename CodeTree<T>::Iterator CodeTree<T>::begin() {
	return Iterator(this);
}

template <typename T>
typename CodeTree<T>::Iterator CodeTree<T>::end() {
	return Iterator();
}

CodeTree<std::string>* createTree(std::ifstream& progFile) {
	CodeTree<std::string>* program = new CodeTree<std::string>;
	if (progFile.is_open()) {
		std::stack<CodeTree<std::string>*> bottom;
		bottom.push(program);
		std::string line;
		while (std::getline(progFile, line)) {
			trim(line);
			if (line != "") {
				bottom.top()->addLine(line, bottom);
			}
		}
	}
	else {
		return nullptr;
	}
	return program;
}

/*
Node Functions
*/

template <typename T>
CodeTree<T>::Node::Node(T line_) {
	line = line_;
	child = nullptr;
}

template <typename T>
CodeTree<T>::Node::Node(const Node& other) {
	line = other.line;
	child = new CodeTree(*other.child);
}

template <typename T>
typename CodeTree<T>::Node& CodeTree<T>::Node::operator=(const Node& rhs) {
	delete child;
	line = rhs.line;
	if (rhs.child != nullptr)
		child = new CodeTree(*rhs.child);
	else
		child = nullptr;
	return *this;
}

template <typename T>
CodeTree<T>::Node::~Node() {
	if (child != nullptr) {
		if (child->getHeader() == this)
			delete child;
	}
}

template <typename T>
void CodeTree<T>::Node::giveChild() {
	child = new CodeTree;
}

template <typename T>
void CodeTree<T>::Node::resetChildsHeader() {
	if (child != nullptr)
		child->setHeader(this);
}

/*
ArrayBlock Functions
*/

template <typename T>
CodeTree<T>::ArrayBlock::ArrayBlock() {
	nodeArray = new CodeTree::Node[4];
	size = 0;
	capacity = 4;
}

template <typename T>
CodeTree<T>::ArrayBlock::ArrayBlock(const ArrayBlock& other) {
	size = other.size;
	capacity = other.capacity;
	nodeArray = new Node[capacity];
	for (unsigned int i = 0; i < size; i++) {
		nodeArray[i] = other.nodeArray[i];
	}
}

template <typename T>
typename CodeTree<T>::ArrayBlock& CodeTree<T>::ArrayBlock::operator=(const ArrayBlock& rhs) {
	delete[] nodeArray;
	size = rhs.size;
	capacity = rhs.capacity;
	nodeArray = new Node[capacity];
	for (unsigned int i = 0; i < size; i++) {
		nodeArray[i] = rhs.nodeArray[i];
	}
	return *this;
}

template <typename T>
CodeTree<T>::ArrayBlock::~ArrayBlock() {
	delete[] nodeArray;
}

template <typename T>
void CodeTree<T>::ArrayBlock::resetNodeChildrensHeaders() {
	for (unsigned int i = 0; i < size; i++)
		nodeArray[i].resetChildsHeader();
}

template <typename T>
void CodeTree<T>::ArrayBlock::setCapacity(unsigned int newCapacity) {
	if (newCapacity < size)
		return;

	Node* tempNodeArray = new Node[newCapacity];
	for (unsigned int i = 0; i < size; i++) {
		tempNodeArray[i].line = nodeArray[i].line;
		tempNodeArray[i].child = nodeArray[i].child;
		tempNodeArray[i].resetChildsHeader();
	}
	delete[] nodeArray;
	nodeArray = tempNodeArray;
}

template <typename T>
unsigned int CodeTree<T>::ArrayBlock::getSize() {
	return size;
}

template <typename T>
typename CodeTree<T>::Node& CodeTree<T>::ArrayBlock::operator[](unsigned int index) {
	if (index < size)
		return nodeArray[index];
	else
		return nodeArray[size - 1];
}

template <typename T>
void CodeTree<T>::ArrayBlock::pushBack(T line) {
	if (size == capacity)
		doubleCapacity();
	nodeArray[size] = Node(line);
	size++;
}

template <typename T>
typename CodeTree<T>::Node& CodeTree<T>::ArrayBlock::back() {
	return nodeArray[size - 1];
}

/*
Iterator Functions
*/

template <typename T>
CodeTree<T>::Iterator::Iterator(CodeTree<T>* start) {
	history.push(std::make_pair(start, (unsigned int)0));
}

template <typename T>
bool CodeTree<T>::Iterator::stepOut() {
	if (history.size() <= 0)
		return false;
	history.pop();
	return stepOver();
}

template <typename T>
bool CodeTree<T>::Iterator::stepOver() {
	if (history.size() <= 0)
		return false;
	unsigned int size = history.top().first->body.getSize();
	unsigned int& index = history.top().second;
	if (index + 1 < size) {
		index++;
		return true;
	}
	return stepOut();

}

template <typename T>
bool CodeTree<T>::Iterator::stepInto() {
	if (history.size() <= 0)
		return false;
	CodeTree* child = history.top().first->body[history.top().second].child;
	if (child != nullptr) {
		history.push(std::make_pair(child, (unsigned int)0));
		return true;
	}
	return stepOver();
}

template <typename T>
T& CodeTree<T>::Iterator::operator*() {
	return history.top().first->body[history.top().second].line;
}

template <typename T>
unsigned int CodeTree<T>::Iterator::depth() {
	return history.size() - 1;
}