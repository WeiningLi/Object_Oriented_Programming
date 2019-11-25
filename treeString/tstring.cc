#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "tnode.h"
#include "tstring.h"
using namespace std;

TString::TString(const std::string &str) {
	length = str.length();
	root = new TNode{ str, length, nullptr, nullptr };
}

TString::TString(const TString &other) {
	length = other.length;
	root = new TNode{ "", 0, nullptr, nullptr };
	*root = *(other.root);
}

void getLen(TNode *root, size_t *len) {
	*len += root->size;
	if (root->right) {
		getLen(root->right, len);
	}
}

TString::TString(TNode *r) {
	size_t len = 0;
	getLen(r, &len);
	length = len;
	root = new TNode{ "", 0, nullptr, nullptr };
	*root = *r;
}

TString::~TString() {
	delete root;
}

TNode *popRight(TNode * n) {
	TNode *prevn = n;
	while (n->right) {
		prevn = n;
		n = n->right;
	}
	prevn->right = n->left;
	n->left = nullptr;
	return n;
}

TString TString::operator+(const TString &other) const {
	TNode* myRoot = new TNode{ *root };
	if (other.length == 0) {
		TString news = myRoot;
		delete myRoot;
		return news;
	}
	if (myRoot->right) {
		TNode *newRoot = popRight(myRoot);
		TNode right = *(other.root);
		newRoot->right = &right;
		newRoot->left = myRoot;
		newRoot->size = length;
		TString news = newRoot;
		newRoot->right = nullptr;
		delete newRoot;
		return news;
	}
	else {
		TNode* right = new TNode{ *(other.root) };
		myRoot->right = right;
		TString news = myRoot;
		delete myRoot;
		return news;
	}
}

char & TString::operator[] (const unsigned int index) {
	TNode *curr = root;
	size_t cumIndex = index;
	int notFound = 1;
	while (notFound) {
		if (cumIndex < (curr->size - (curr->data).length())) {
			curr = curr->left;
		}
		else if (cumIndex > curr->size - 1) {
			cumIndex -= curr->size;
			curr = curr->right;
		}
		else notFound = 0;
	}
	if (!curr->left) {
		char &c = curr->data[cumIndex];
		return c;
	}
	else {
		char &c = curr->data[cumIndex - (curr->size - (curr->data).length())];
		return c;
	}
}

void TString::insert(const std::string &str, const unsigned int index) {
	if (str == "") return;
	// originally empty
	if (length == 0) {
		root->data = str;
		root->size = str.length();
		length = str.length();
		return;
	}
	TNode *curr = root;
	size_t cumIndex = index;
	size_t len = str.length();
	size_t newSize;

	// index is greater than string length
	if (index >= length) {
		TNode *curr = root;
		while (curr->right) {
			curr = curr->right;
		}
		TNode *newN = new TNode{ str, len, nullptr, nullptr };
		curr->right = newN;
		length += len;
		return;
	}
	int notFound = 1;
	// find node N to insert
	while (notFound) {
		// move left
		if (cumIndex < (curr->size - (curr->data).length())) {
			curr->size += len;
			curr = curr->left;
		}
		// move right
		else if (cumIndex > curr->size + 1) {
			cumIndex -= curr->size;
			if(curr->right) curr = curr->right;
		}
		else notFound = 0;
	}
	// before
	if (cumIndex == curr->size - (curr->data).length()) {
		size_t leftSize = 0;
		if (curr->left) getLen(curr->left, &leftSize);
		newSize = (curr->data).length() + leftSize;
		TNode *newN = new TNode{ str, newSize, curr->left, nullptr };
		curr->left = newN;
		length += len;
	}
	// after
	else if (cumIndex == (curr->size + 1)) {
		TNode *newN = new TNode{ str, len, nullptr, curr->right };
		curr->right = newN;
		length += len;
	}
	// middle
	else if (cumIndex > curr->size - (curr->data).length() && cumIndex < (curr->size + 1)) {
		string ls = curr->data.substr(0, cumIndex - (curr->size - (curr->data).length()));
		string rs = curr->data.substr(cumIndex - (curr->size - (curr->data).length()));
		size_t leftSize;
		size_t temp = 0;
		if (curr->left) {
			getLen(curr->left, &temp);
			leftSize = temp + cumIndex - (curr->size - (curr->data).length());
		}
		else {
			leftSize = cumIndex - (curr->size - (curr->data).length());
		}
		if (ls != "") {
			TNode *newL = new TNode{ ls, leftSize, curr->left, nullptr };
			getLen(newL, &temp);
			curr->left = newL;
		}
		if (rs != "") {
			TNode *newR = new TNode{ rs, rs.length(), nullptr, curr->right };
			if (rs != "") curr->right = newR;
		}
		newSize = len + temp;
		curr->data = str;
		curr->size = newSize;
		length += len;
	}
}

void print(std::ostream& out, const TNode *n) {
	if (n->left) print(out, n->left);
	out << n->data;
	if (n->right) print(out, n->right);
}

std::ostream& operator<<(std::ostream& out, const TString &t) {
	print(out, t.root);
	return out;
}


