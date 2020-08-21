#include "CodeTree.h"

CodeTree::Node::Node(std::string line_) {
	line = line_;
	child = nullptr;
}

CodeTree::Node::Node(const Node& other) {
	line = other.line;
	child = new CodeTree(*other.child);
}

CodeTree::Node& CodeTree::Node::operator=(const Node& rhs) {
	delete child;
	line = rhs.line;
	if (rhs.child != nullptr)
		child = new CodeTree(*rhs.child);
	else
		child = nullptr;
	return *this;
}

CodeTree::Node::~Node() {
	if (child != nullptr) {
		if (child->getHeader() == this)
			delete child;
	}
}

void CodeTree::Node::giveChild() {
	child = new CodeTree;
}

void CodeTree::Node::resetChildsHeader() {
	if(child != nullptr)
		child->setHeader(this);
}