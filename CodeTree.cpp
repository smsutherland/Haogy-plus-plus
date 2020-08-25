#include "CodeTree.h"

CodeTree::CodeTree(Node* header_) {
	header = header_;
}

void CodeTree::setHeader(Node* newParent) {
	header = newParent;
}

CodeTree::Node* CodeTree::getHeader() {
	return header;
}

void CodeTree::addLine(std::string line, std::stack<CodeTree*>& bottom) {
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
		for(int i = 0; i < -lineType; i++){
			if (!bottom.empty()) {
				bottom.top()->body.shrinkToFit();
				bottom.pop();
			}
			else
				break;
		}
	}
}

CodeTree* CodeTree::createTree(std::ifstream& progFile) {
	CodeTree* program = new CodeTree;
	if (progFile.is_open()) {
		std::stack<CodeTree*> bottom;
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

void CodeTree::print(unsigned int indent) {
	for (auto itr = this->begin(); itr != this->end(); itr.stepInto()) {
		for (unsigned int i = 0; i < itr.depth(); i++)
			std::cout << "\t";
		std::cout << *itr << std::endl;
	}
}

CodeTree::Iterator CodeTree::begin() {
	return Iterator(this);
}

CodeTree::Iterator CodeTree::end() {
	return Iterator();
}