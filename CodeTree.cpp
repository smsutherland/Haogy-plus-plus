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
	for (unsigned int i = 0; i < body.getSize(); i++) {
		for (unsigned int j = 0; j < indent; j++)
			std::cout << "\t";
		Node& currentNode = body[i];
		std::cout << currentNode.line << std::endl;
		if (currentNode.child != nullptr) {
			currentNode.child->print(indent + 1);
			for (unsigned int j = 0; j < indent; j++)
				std::cout << "\t";
			std::cout << "}" << std::endl;
		}
	}
}