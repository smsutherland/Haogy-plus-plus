#include "CodeTree.h"

CodeTree::ArrayBlock::ArrayBlock() {
	nodeArray = new CodeTree::Node[4];
	size = 0;
	capacity = 4;
}

CodeTree::ArrayBlock::ArrayBlock(const ArrayBlock& other) {
	size = other.size;
	capacity = other.capacity;
	nodeArray = new Node[capacity];
	for (unsigned int i = 0; i < size; i++) {
		nodeArray[i] = other.nodeArray[i];
	}
}

CodeTree::ArrayBlock& CodeTree::ArrayBlock::operator=(const ArrayBlock& rhs) {
	delete[] nodeArray;
	size = rhs.size;
	capacity  = rhs.capacity;
	nodeArray = new Node[capacity];
	for (unsigned int i = 0; i < size; i++) {
		nodeArray[i] = rhs.nodeArray[i];
	}
	return *this;
}

CodeTree::ArrayBlock::~ArrayBlock() {
	delete[] nodeArray;
}

void CodeTree::ArrayBlock::resetNodeChildrensHeaders() {
	for (unsigned int i = 0; i < size; i++)
		nodeArray[i].resetChildsHeader();
}

void CodeTree::ArrayBlock::setCapacity(unsigned int newCapacity) {
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

unsigned int CodeTree::ArrayBlock::getSize() {
	return size;
}

CodeTree::Node& CodeTree::ArrayBlock::operator[](unsigned int index) {
	if (index < size)
		return nodeArray[index];
	else
		return nodeArray[size - 1];
}

void CodeTree::ArrayBlock::pushBack(std::string line) {
	if (size == capacity)
		doubleCapacity();
	nodeArray[size] = Node(line);
	size++;
}

CodeTree::Node& CodeTree::ArrayBlock::back() {
	return nodeArray[size - 1];
}