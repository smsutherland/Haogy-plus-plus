#include "CodeTree.h"

CodeTree::Iterator::Iterator(CodeTree* start) {
	history.push(std::make_pair(start, (unsigned int)0));
}

bool CodeTree::Iterator::stepOut() {
	if (history.size() <= 0)
		return false;
	history.pop();
	return stepOver();
}

bool CodeTree::Iterator::stepOver() {
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

bool CodeTree::Iterator::stepInto() {
	if (history.size() <= 0)
		return false;
	CodeTree* child = history.top().first->body[history.top().second].child;
	if (child != nullptr) {
		history.push(std::make_pair(child, (unsigned int)0));
		return true;
	}
	return stepOver();
}

std::string& CodeTree::Iterator::operator*() {
	return history.top().first->body[history.top().second].line;
}

unsigned int CodeTree::Iterator::depth() {
	return history.size() - 1;
}