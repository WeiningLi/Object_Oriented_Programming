#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "tnode.h"
#include "tstring.h"
using namespace std;

TNode::TNode(string data, size_t size, TNode *left, TNode *right) : data{ data }, size{ size }, left{ left }, right{ right } {}

TNode::TNode(const TNode & other) : data{ other.data }, size{ other.size }, left{ other.left ? new TNode{*other.left} : nullptr }, right{ other.right ? new TNode{*other.right} : nullptr } {}

TNode::~TNode() {
	delete left;
	delete right;
}

TNode & TNode::operator= (const TNode & other) {
	if (this == &other) return *this;
	TNode *tmpl = other.left;
	TNode *tmpr = other.right;
	left = other.left ? new TNode{ *other.left } : nullptr;
	right = other.right ? new TNode{ *other.right } : nullptr;
	data = other.data;
	size = other.size;
	return *this;
}


